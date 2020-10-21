#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include "basedownload.h"

class DownloadManager : public QObject
{
    Q_OBJECT
public: 
    QList<BaseDownload *> *getDownloadList() const;
    static DownloadManager *getInstance();
private:
    explicit DownloadManager(QObject *parent = nullptr);
    QList<BaseDownload *> *downloadList;
    static DownloadManager *instance;
public slots:
    void startAll();
    void stopAll();
    void pauseAll();
signals:

};

#endif // DOWNLOADMANAGER_H
