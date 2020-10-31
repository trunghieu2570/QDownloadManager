#ifndef BASEDOWNLOAD_H
#define BASEDOWNLOAD_H

#include <QObject>
#include <QTimer>
#include <QUrl>
#include "downloadstate.h"
#include "downloadtype.h"

class BaseDownload : public QObject
{
    Q_OBJECT
protected:
    explicit BaseDownload(QObject *parent = nullptr);
    QString name;
    QString address;
    QString saveLocation;
    DownloadState state;
    QString description;
    qint64 size = -1;
public:
    virtual qint64 getSize() const = 0;
    virtual qint64 getDownloadedSize() const = 0;
    virtual DownloadType getType() const = 0;
    virtual QString getName() const;
    virtual QString getAddress() const;
    virtual QString getSaveLocation() const;
    virtual DownloadState getCurrentState() const;
    virtual QString getDescription() const;
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void writeJson(QJsonObject &json) const = 0;
    virtual void loadInfo() = 0;
    virtual void setName(const QString &value);
    virtual void setAddress(const QString &value);
    virtual void setSaveLocation(const QString &value);
    virtual void setDescription(const QString &value);
    virtual void setSize(const qint64 &value);
    virtual void setState(const DownloadState &value);

signals:
    void stateChanged();
    void progressChanged();

};

#endif // BASEDOWNLOAD_H
