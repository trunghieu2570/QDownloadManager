#include "basedownload.h"

BaseDownload::BaseDownload(QObject *parent): QObject(parent)
{

}

void BaseDownload::setState(const DownloadState &value)
{
    state = value;
}

void BaseDownload::setSize(const qint64 &value)
{
    size = value;
}

void BaseDownload::setDescription(const QString &value)
{
    description = value;
}

void BaseDownload::setSaveLocation(const QString &value)
{
    saveLocation = value;
}

void BaseDownload::setAddress(const QString &value)
{
    address = value;
}

void BaseDownload::setName(const QString &value)
{
    name = value;
}

QString BaseDownload::getName() const
{
    return name;
}

QString BaseDownload::getAddress() const
{
    return address;
}

QString BaseDownload::getSaveLocation() const
{
    return saveLocation;
}

DownloadState BaseDownload::getCurrentState() const
{
    return state;
}

QString BaseDownload::getDescription() const
{
    return description;
}

