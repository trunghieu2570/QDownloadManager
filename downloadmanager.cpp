#include "downloadmanager.h"

DownloadManager *DownloadManager::instance = 0;

DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
{
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

QList<BaseDownload *> DownloadManager::getDownloadList()
{
    return instance->downloadList;
}

DownloadManager *DownloadManager::getInstance()
{
    if(!instance) {
        instance = new DownloadManager;
    }
    return instance;
}

void DownloadManager::addDownload(BaseDownload *dl)
{
    downloadList.append(dl);
}
