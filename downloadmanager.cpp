#include "downloadmanager.h"

#include <ParallelDownload.h>


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

bool DownloadManager::saveList() const
{
    QFile saveFile(QStringLiteral("save.json"));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject _jsonObject;

    QJsonArray _dlJsonArray;
    foreach (const BaseDownload *_dl, instance->getDownloadList()) {
        QJsonObject _dlObject;
        _dl->writeJson(_dlObject);
        _dlJsonArray.append(_dlObject);
    }
    _jsonObject["downloads"] = _dlJsonArray;
    QJsonDocument saveDoc(_jsonObject);
    saveFile.write(saveDoc.toJson());
    return true;
}

bool DownloadManager::loadList()
{
    QFile loadFile(QStringLiteral("save.json"));
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonArray loadArray = loadDoc.object()["downloads"].toArray();
    for (int i = 0; i < loadArray.size(); i++) {
        QJsonObject _dlObj = loadArray.at(i).toObject();
        ParallelDownload * dl = new ParallelDownload();
        dl->setAddress(_dlObj["address"].toString());
        RemoteFileInfo *_info = new RemoteFileInfo();
        _info->setAddress(dl->getAddress());
        dl->setRemoteInfo(_info);

        dl->setName(_dlObj["name"].toString());
        dl->setSaveLocation(_dlObj["saveLocation"].toString());
        dl->setSize(_dlObj["size"].toVariant().toLongLong());
        dl->setDescription(_dlObj["description"].toString());
        dl->setState((DownloadState) _dlObj["state"].toInt());
        dl->checkFileExist();
        instance->addDownload(dl);
    }

    return true;
}
