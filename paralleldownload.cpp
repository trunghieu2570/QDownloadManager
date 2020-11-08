#include "paralleldownload.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>


ParallelDownload::ParallelDownload(QObject *parent) : BaseDownload(parent)
{
    //rfInfo = new RemoteFileInfo();
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &ParallelDownload::calculateProgress);
    connect(this, &ParallelDownload::prepareFinished, this, &ParallelDownload::downloadSegments);
}

qint64 ParallelDownload::getSize() const
{
    return size;
}

void ParallelDownload::loadInfo()
{
    size = 108007440;
    if(size >= 0) {
        generateSegments();
    }
}

void ParallelDownload::writeFile()
{
    state = DownloadState::WRITING;
    emit stateChanged();
    QFile * finalFile = new QFile(name);
    if (!finalFile->open(QIODevice::WriteOnly))
        return;
    foreach (Segment *_s, segmentList) {
        QFile * _currentFile = _s->getFile();
        if (_s->getFile()->exists()) {
            qint64 _fsize = _currentFile->size();
            if (_s->getFile()->open(QIODevice::ReadOnly)) {
                QByteArray _data;
                for (qint64 _bytes = 0; _bytes < _fsize; _bytes += _data.size()) {
                    _data = _currentFile->read(2048);
                    finalFile->write(_data);
                }
                _currentFile->close();
                _currentFile->remove();
                _currentFile->deleteLater();
            }
        }
    }
    finalFile->close();
    state = DownloadState::FINISHED;
    emit stateChanged();
}

DownloadType ParallelDownload::getType() const
{
    return DownloadType::PARALLEL_DOWNLOAD;
}

void ParallelDownload::prepare()
{
    //state = DownloadState::PREPARING;
    //emit stateChanged();
    rfInfo->setAddress(address);
    rfInfo->startFetching();
}

QList<Segment *> ParallelDownload::getSegmentList()
{
    return this->segmentList;
}

qint64 ParallelDownload::getDownloadedSize() const
{
    return downloadedSize;
}

void ParallelDownload::writeJson(QJsonObject &json) const
{
    json["name"] = name;
    json["address"] = address;
    json["saveLocation"] = saveLocation;
    json["description"] = description;
    json["size"] = size;
    json["state"] = (int) state;
    json["connections"] = max;
}

bool ParallelDownload::checkFileExist()
{
    if(QFile::exists(name)) {
        QFile _file(name);
        downloadedSize = _file.size();
        return true;
    }
    return false;
}

void ParallelDownload::setRemoteInfo(RemoteFileInfo *value)
{
    rfInfo = value;
    connect(rfInfo, &RemoteFileInfo::done, this, &ParallelDownload::getInfoFinished);
}

void ParallelDownload::generateSegments()
{
    segmentList.clear();
    //divide file size
    qint64 s_size = size / max;

    for (int i = 0; i < (max-1); i++) {
        QFile *dfile = new QFile(this->getName().append(".qpart").append(QString::number(i)));
        auto _seg = new Segment(address, dfile, i * s_size, (i + 1) * s_size - 1);
        segmentList.append(_seg);
    }
    QFile *dfile = new QFile(this->getName().append(".qpart").append(QString::number(max-1)));
    auto _seg = new Segment(address, dfile, (max-1) * s_size, size);
    segmentList.append(_seg);
}

void ParallelDownload::start()
{
    state = DownloadState::PREPARING;
    emit stateChanged();
    qDebug() << "started";
    this->prepare();
    timer->start(1000);
}

void ParallelDownload::stop()
{
    //TODO
    emit stateChanged();
}

void ParallelDownload::pause()
{
    if (segmentList.size() <= 0)
    {
        qDebug() << "There aren't have any segments!";
        return;
    }
    for (Segment *seg : segmentList) {
        seg->stop();
    }
    //emit stateChanged();
    timer->stop();
    state = DownloadState::PAUSED;
    emit stateChanged();
}

void ParallelDownload::getInfoFinished()
{
    //qint64 oldSize = this->size;
    qDebug() << "finishInfoGet";
    this->size = rfInfo->getSize();
    if(!rfInfo->isAcceptRanges()){
        max = 1;
    }
    generateSegments();
    emit prepareFinished();
    qDebug() << "prepared";
}

void ParallelDownload::calculateProgress()
{
    qint64 sum = 0;
    foreach(Segment *p_seg, segmentList) {
        sum += p_seg->getReceivedSize();
    }
    downloadedSize = sum;
    if (downloadedSize > 0 && downloadedSize >= size) {
        for (Segment *seg : segmentList) {
            seg->stop();
        }
        emit stateChanged();
        writeFile();
        timer->stop();
    }

    emit progressChanged();
}

void ParallelDownload::downloadSegments()
{
    state = DownloadState::DOWNLOADING;
    emit stateChanged();
    if (segmentList.size() <= 0)
    {
        qDebug() << "There aren't have any segments!";
        return;
    }
    for (Segment *seg : segmentList) {
        seg->download();
    }
}
