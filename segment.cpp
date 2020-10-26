#include "segment.h"

Segment::Segment(QObject *parent) : QObject(parent)
{

}

Segment::Segment(const QUrl &address, QFile *file, qint64 start, qint64 end)
{
    this->file = file;
    this->startPos = start;
    this->endPos = end;
    this->address = address;
    this->total = end - start + 1;
    this->received = file->size();
    QObject::connect(&qnam, SIGNAL(finished(QNetworkReply*)),this, SLOT(downloadFinished(QNetworkReply*)));
}

SegmentState Segment::getCurrentState()
{
    return state;
}

qint64 Segment::getReceivedSize() const
{
    return received;
}

qint64 Segment::getTotalSize() const
{
    return total;
}

void Segment::download()
{
    //open file to append data
    if (!file->open(QIODevice::Append))
        return;
    //clear if the file is oversized
    if(file->size() > total)
    {
        file->resize(0);
    }

    currentPos = startPos;

    //new size
    received = file->size();
    currentPos += received;
    //skip if the file is already completed
    if (currentPos >= endPos)
        return;

    //create request
    QNetworkRequest request(address);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setRawHeader("Range", QString("bytes=%1-%2").arg(QString::number(currentPos), QString::number(endPos)).toLocal8Bit());

    //start download
    reply = qnam.get(request);
    connect(reply, &QNetworkReply::downloadProgress, this, &Segment::downloadProgress);
    connect(reply, &QNetworkReply::readyRead, this, &Segment::dataReadyRead);

    //change to DOWNLOADING state
    emit stateChanged();
}

void Segment::stop()
{
    downloadFinished(reply);
}

void Segment::downloadFinished(QNetworkReply *data)
{
    state = SegmentState::FINISHED;
    //emit finished();
    emit stateChanged();
    data->deleteLater();
    file->close();
}

void Segment::downloadProgress(qint64 rev, qint64 _total)
{
    this->received = currentPos - startPos + rev;
    emit segmentProgressChanged(received, total);
}

void Segment::dataReadyRead()
{
    file->write(reply->readAll());
}
