#include "paralleldownload.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>


ParallelDownload::ParallelDownload(QObject *parent) : BaseDownload(parent)
{
    fileInfo = new RemoteFileInfo();
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &ParallelDownload::calculateProgress);
}

qint64 ParallelDownload::getSize() const
{
    return fileInfo->getSize();
}

void ParallelDownload::loadInfo()
{
    size = 108007440;
    if(size >= 0) {
        generateSegments();
    }
}

DownloadType ParallelDownload::getType() const
{
    return DownloadType::PARALLEL_DOWNLOAD;
}

void ParallelDownload::prepare()
{
    state = DownloadState::PREPARING;
    emit stateChanged();
    fileInfo->setAddress(address);
    connect(fileInfo, &RemoteFileInfo::done, this, &ParallelDownload::getInfoFinished);
    fileInfo->startFetching();
}

QList<Segment *> ParallelDownload::getSegmentList()
{
    return this->segmentList;
}

qint64 ParallelDownload::getDownloadedSize() const
{
    return downloadedSize;
}

QJsonObject ParallelDownload::toJson() const
{
    //return {"je":name};
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
    state = DownloadState::STARTED;
    emit stateChanged();
    qDebug() << "started";
    connect(this, &ParallelDownload::prepareFinished, this, &ParallelDownload::downloadSegments);
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
//TODO
    emit stateChanged();
}

void ParallelDownload::getInfoFinished()
{
    //qint64 oldSize = this->size;
    this->size = fileInfo->getSize();
    if(!fileInfo->isAcceptRanges()){
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
    if (downloadedSize > 0 && downloadedSize >= size)
        timer->stop();
    emit progressChanged();
}

void ParallelDownload::downloadSegments()
{
    state = DownloadState::DOWNLOADING;
    //emit stateChanged();
    if (segmentList.size() <= 0)
    {
        qDebug() << "There aren't have any segments!";
        return;
    }
    for (Segment *seg : segmentList) {
        seg->download();
    }
}
