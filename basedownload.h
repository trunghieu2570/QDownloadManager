#ifndef BASEDOWNLOAD_H
#define BASEDOWNLOAD_H

#include <QObject>
#include <QUrl>
#include "downloadstate.h"

class BaseDownload : public QObject
{
    Q_OBJECT
protected:
    explicit BaseDownload(QObject *parent = nullptr);
    QString name;
    QUrl address;
    QString saveLocation;
    DownloadState state;
    QString desciption;
public:
    virtual qint64 getSize() = 0;
    virtual QString getName();
    virtual QUrl getAddress();
    virtual QString getSaveLocation();
    virtual DownloadState getCurrentState();
    virtual QString getDescription();
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    void setName(const QString &value);
    void setAddress(const QUrl &value);
    void setSaveLocation(const QString &value);
    QString getDesciption() const;
    void setDesciption(const QString &value);

signals:
    void stateChanged();

};

#endif // BASEDOWNLOAD_H
