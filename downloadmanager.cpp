#include "downloadmanager.h"

DownloadManager *DownloadManager::instance = 0;

DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
{
    downloadList = new QList<BaseDownload*>();
}

void DownloadManager::startAll()
{

}

void DownloadManager::stopAll()
{

}

void DownloadManager::pauseAll()
{

}

QList<BaseDownload *> *DownloadManager::getDownloadList() const
{
    return downloadList;
}

DownloadManager *DownloadManager::getInstance()
{
    if(!instance) {
        instance = new DownloadManager();
    }
    return instance;
}
