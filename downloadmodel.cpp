#include "downloadmanager.h"
#include "downloadmodel.h"



int DownloadModel::rowCount(const QModelIndex &parent) const
{
    list.size();
}

int DownloadModel::columnCount(const QModelIndex &parent) const
{
    return 7;
}

QVariant DownloadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if ( role == Qt::DisplayRole)
    {
        if ( index.column() == (int)DownloadTableColumns::FILE_NAME)
            return list.at(index.row())->getName();
        if ( index.column() == (int)DownloadTableColumns::QUEUE_NAME)
            return "";
        if ( index.column() == (int)DownloadTableColumns::SIZE)
            return list.at(index.row())->getSize();
        if ( index.column() == (int)DownloadTableColumns::STATUS)
            return "";
        if ( index.column() == (int)DownloadTableColumns::TRANSFER_RATE)
            return "";
        if ( index.column() == (int)DownloadTableColumns::LAST_TIME)
            return "";
        if ( index.column() == (int)DownloadTableColumns::DESCRIPTION)
            return "getName()";
    }
    return QVariant();
}

void DownloadModel::populate()
{
    beginResetModel();
    list.clear();
    auto dm = DownloadManager::getInstance();
    list.append(*dm->getDownloadList());
    endResetModel();
}
