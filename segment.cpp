#include "segment.h"

Segment::Segment(QObject *parent) : QObject(parent)
{

}

Segment::Segment(const QString &address, QFile *file, qint64 start, qint64 end)
{
    this->file = file;
    this->startPos = start;
    this->endPos = end;
    this->address = address;
    this->total = end - start + 1;
    this->received = file->size();
//    QObject::connect(&qnam, SIGNAL(finished(QNetworkReply*)),this, SLOT(downloadFinished(QNetworkReply*)));
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

QFile *Segment::getFile() const
{
    return file;
}

void Segment::download()
{
    //open file to append data
    if (!file->open(QIODevice::Append))
        return;
    qDebug() << "open" << file->fileName();
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
    if (currentPos >= endPos) {
        downloadFinished();
        return;
    }

    //create request
    QUrl url = QUrl::fromEncoded(address.toLocal8Bit());
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setRawHeader("Range", QString("bytes=%1-%2").arg(QString::number(currentPos), QString::number(endPos)).toLocal8Bit());

    //start download
    reply = qnam.get(request);
    //change to DOWNLOADING state
    state = SegmentState::DOWNLOADING;
    emit stateChanged();

    connect(reply, &QNetworkReply::finished, this, &Segment::downloadFinished);
    connect(reply, &QNetworkReply::downloadProgress, this, &Segment::downloadProgress);
    connect(reply, &QNetworkReply::readyRead, this, &Segment::dataReadyRead);


}

void Segment::stop()
{
    if (reply) {
        reply->abort();
    }
    //downloadFinished(reply);
}

void Segment::downloadFinished()
{
    if (currentPos >= endPos)
        state = SegmentState::FINISHED;
    else
        state = SegmentState::PAUSED;
    //emit finished();
    emit stateChanged();

    if (reply) {
        reply->deleteLater();
        reply = nullptr;
    }

    if (file->isOpen()) {
        file->close();
    }

    qDebug() << "close" << file->fileName();
}

void Segment::downloadProgress(qint64 rev, qint64 _total)
{
    this->received = currentPos - startPos + rev;
    emit segmentProgressChanged(received, total);
}

void Segment::dataReadyRead()
{
    qDebug() << reply->size();
    file->write(reply->readAll());
}
