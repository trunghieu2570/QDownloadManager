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
    void setAddress(const QString &value);

    QString getAddress() const;
    QString getFinalAddress() const;
protected:
    QString address;
    QString finalAddress;
    qint64 size;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    bool acceptRanges;
public slots:
    void startFetching();
private slots:
    void fetchFinished();
signals:
    void done();
};

#endif // REMOTEFILEINFO_H
