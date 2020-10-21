#include "basedownload.h"

BaseDownload::BaseDownload(QObject *parent): QObject(parent)
{

}

QString BaseDownload::getDesciption() const
{
    return desciption;
}

void BaseDownload::setDesciption(const QString &value)
{
    desciption = value;
}

void BaseDownload::setSaveLocation(const QString &value)
{
    saveLocation = value;
}

void BaseDownload::setAddress(const QUrl &value)
{
    address = value;
}

void BaseDownload::setName(const QString &value)
{
    name = value;
}

QString BaseDownload::getName()
{
    return name;
}

QUrl BaseDownload::getAddress()
{
    return address;
}

QString BaseDownload::getSaveLocation()
{
    return saveLocation;
}

DownloadState BaseDownload::getCurrentState()
{
    return state;
}

QString BaseDownload::getDescription()
{
    return desciption;
}
