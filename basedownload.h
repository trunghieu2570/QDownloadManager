#ifndef BASEDOWNLOAD_H
#define BASEDOWNLOAD_H

#include <QObject>
#include <QUrl>
#include "downloadstate.h"
#include "downloadtype.h"

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
    qint64 size;
public:
    virtual qint64 getSize() const = 0;
    virtual qint64 getDownloadedSize() const = 0;
    virtual DownloadType getType() const = 0;
    virtual QString getName() const;
    virtual QUrl getAddress() const;
    virtual QString getSaveLocation() const;
    virtual DownloadState getCurrentState() const;
    virtual QString getDescription() const;
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
