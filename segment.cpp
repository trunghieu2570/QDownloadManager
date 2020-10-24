#include "segment.h"

#include <QEventLoop>

Segment::Segment(QObject *parent) : QObject(parent)
{

}

Segment::Segment(const QUrl &address, QFile *file, qint64 start, qint64 end)
{
    this->file = file;
    this->startPos = start;
    this->endPos = end;
    this->address = address;
    this->total = end - start;
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
    if (startPos > endPos)
        return;
    QNetworkRequest request(address);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setRawHeader("Range", QString("bytes=%1-%2").arg(QString::number(startPos), QString::number(endPos)).toLocal8Bit());
    //QEventLoop loop;
    reply = qnam.get(request);
    connect(reply, &QNetworkReply::downloadProgress, this, &Segment::downloadProgress);
    //state = SegmentState::PAUSED;
    //connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //loop.exec();
}

void Segment::downloadFinished(QNetworkReply *data)
{
    if (!file->open(QIODevice::WriteOnly))
        return;
    file->write(data->readAll());
    state = SegmentState::FINISHED;
    emit finished();
    data->deleteLater();
    file->close();
    //qDebug() << "finished:" << file->fileName();
}

void Segment::downloadProgress(qint64 rev, qint64 total)
{
    //qDebug() << "progress:" << file->fileName() << rev << total;
    this->total = total;
    this->received = rev;
    emit stateChanged();
    emit segmentProgressChanged(rev, total);
}
