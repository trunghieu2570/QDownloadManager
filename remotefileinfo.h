#ifndef REMOTEFILEINFO_H
#define REMOTEFILEINFO_H

#include <QNetworkAccessManager>
#include <QObject>
#include <QNetworkReply>

class RemoteFileInfo : public QObject
{
    Q_OBJECT
public:
    explicit RemoteFileInfo(QObject *parent = nullptr);
    qint64 getSize();
    bool isAcceptRanges();
    void setAddress(const QUrl &value);
protected:
    QUrl address;
    qint64 size = 0;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    bool acceptRanges = false;
public slots:
    void startFetching();
private slots:
    void fetchFinished();
signals:
    void done();
};

#endif // REMOTEFILEINFO_H
