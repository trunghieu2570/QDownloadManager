#include "remotefileinfo.h"

RemoteFileInfo::RemoteFileInfo(QObject *parent) : QObject(parent)
{

}

qint64 RemoteFileInfo::getSize()
{
    return size;
}

bool RemoteFileInfo::isAcceptRanges()
{
    return acceptRanges;
}

void RemoteFileInfo::setAddress(const QString &value)
{
    address = value;
}

void RemoteFileInfo::startFetching()
{
    QUrl url = QUrl::fromEncoded(address.toLocal8Bit());
    QNetworkRequest req(url);
    reply = qnam.head(req);
    connect(reply, &QNetworkReply::finished, this, &RemoteFileInfo::fetchFinished);
}

void RemoteFileInfo::fetchFinished()
{
    acceptRanges = false;
    QList<QByteArray> list = reply->rawHeaderList();
    foreach (QByteArray header, list)
    {
        QString qsLine = QString(header) + " = " + reply->rawHeader(header);
        //addLine(qsLine);
    }

    if (reply->hasRawHeader("Accept-Ranges"))
    {
        QString acceptRangesString = reply->rawHeader("Accept-Ranges");
        acceptRanges = (acceptRangesString.compare("bytes", Qt::CaseInsensitive) == 0);
        qDebug() << "Accept-Ranges = " << acceptRangesString << acceptRanges;
    }

    size = reply->header(QNetworkRequest::ContentLengthHeader).toInt();
    qDebug() << "done";
    emit done();
    reply->deleteLater();
}
