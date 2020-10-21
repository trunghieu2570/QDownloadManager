#include "paralleldownload.h"

ParallelDownload::ParallelDownload(QObject *parent) : BaseDownload(parent)
{
    fileInfo = new RemoteFileInfo();
}

qint64 ParallelDownload::getSize()
{
    return fileInfo->getSize();
}

void ParallelDownload::prepare()
{
    state = DownloadState::PREPARING;
    emit stateChanged();
    fileInfo->setAddress(address);
    connect(fileInfo, &RemoteFileInfo::done, this, &ParallelDownload::getInfoFinished);
    fileInfo->startFetching();

}

void ParallelDownload::generateSegments()
{
    segmentList = new QList<Segment*>();
    segmentList->clear();

    qint64 s_size = size / max;

    for (int i = 0; i < (max-1); i++) {
        QFile *dfile = new QFile(this->getName().append(".qpart").append(QString::number(i)));
        segmentList->append(new Segment(address, dfile, i * s_size, (i + 1) * s_size - 1));
    }
    QFile *dfile = new QFile(this->getName().append(".qpart").append(QString::number(max-1)));

    segmentList->append(new Segment(address, dfile, (max-1) * s_size, size));
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
    if (segmentList->size() <= 0)
    {
        qDebug() << "There aren't have any segments!";
        return;
    }
    for (Segment *seg : *segmentList) {
        seg->download();
    }
}
