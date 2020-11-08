#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "basedownload.h"

class DownloadManager : public QObject
{
    Q_OBJECT
public: 
    QList<BaseDownload *> getDownloadList();
    static DownloadManager *getInstance();
    void addDownload(BaseDownload *dl);
private:
    explicit DownloadManager(QObject *parent = nullptr);
    QList<BaseDownload *> downloadList;
    static DownloadManager *instance;
public slots:
    void startAll();
    void stopAll();
    void pauseAll();
    bool saveList() const;
    bool loadList();
signals:

};

#endif // DOWNLOADMANAGER_H
