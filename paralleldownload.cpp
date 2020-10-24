#include "paralleldownload.h"

ParallelDownload::ParallelDownload(QObject *parent) : BaseDownload(parent)
{
    fileInfo = new RemoteFileInfo();
}

qint64 ParallelDownload::getSize() const
{
    return fileInfo->getSize();
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
    qint64 sum = 0;
    foreach(Segment *p_seg, segmentList) {
        sum += p_seg->getReceivedSize();
    }
    return sum;
}

void ParallelDownload::generateSegments()
{
    //segmentList = QList<Segment*>();
    segmentList.clear();

    qint64 s_size = size / max;

    for (int i = 0; i < (max-1); i++) {
        QFile *dfile = new QFile(this->getName().append(".qpart").append(QString::number(i)));
        auto _seg = new Segment(address, dfile, i * s_size, (i + 1) * s_size - 1);
        connect(_seg, &Segment::stateChanged, this, &ParallelDownload::emitDownloadProgressChange);
        segmentList.append(_seg);
    }
    QFile *dfile = new QFile(this->getName().append(".qpart").append(QString::number(max-1)));
    auto _seg = new Segment(address, dfile, (max-1) * s_size, size);
    connect(_seg, &Segment::stateChanged, this, &ParallelDownload::emitDownloadProgressChange);
    segmentList.append(_seg);
}

void ParallelDownload::start()
{
    state = DownloadState::STARTED;
    emit stateChanged();
    qDebug() << "started";
    connect(this, &ParallelDownload::prepareFinished, this, &ParallelDownload::downloadSegments);
    this->prepare();
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

void ParallelDownload::emitDownloadProgressChange()
{
    emit stateChanged();
}

void ParallelDownload::getInfoFinished()
{
    qint64 oldSize = this->size;
    this->size = fileInfo->getSize();
    if(!fileInfo->isAcceptRanges()){
        max = 1;
    }
    if (oldSize != this->size)
        generateSegments();
    emit prepareFinished();
    qDebug() << "prepared";
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
