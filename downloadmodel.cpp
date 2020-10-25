#include "downloadmanager.h"
#include "downloadmodel.h"
#include "paralleldownload.h"



int DownloadModel::rowCount(const QModelIndex &parent) const
{
    return dm->getDownloadList().size();
}

int DownloadModel::columnCount(const QModelIndex &parent) const
{
    return 8;
}

QVariant DownloadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if ( role == Qt::DisplayRole)
    {
        auto base = dm->getDownloadList().at(index.row());
        connect(base, &BaseDownload::progressChanged, this, &DownloadModel::progressUpdate);
        connect(base, &BaseDownload::stateChanged, this, &DownloadModel::stateUpdate);
        if ( index.column() == (int)DownloadTableColumns::FILE_NAME)
            return base->getName();
        if ( index.column() == (int)DownloadTableColumns::QUEUE_NAME)
            return "";
        if ( index.column() == (int)DownloadTableColumns::SIZE) {
            QLocale locale = QLocale::system();
            return locale.formattedDataSize(base->getSize());
        }
        if ( index.column() == (int)DownloadTableColumns::STATUS) {
            if (base->getType() == DownloadType::PARALLEL_DOWNLOAD) {
                auto para = dynamic_cast<ParallelDownload*>(base);
                if (para->getDownloadedSize() <= 0 || para->getDownloadedSize() > para->getSize())
                    return "0%";
                if (para->getDownloadedSize() == para->getSize())
                    return "Finished";
                return QString("%1\%").arg(QString::number(para->getDownloadedSize() * 100 / (para->getSize())));
            }
            return "";
        }
        if ( index.column() == (int)DownloadTableColumns::DOWNLOADED) {
            QLocale locale = QLocale::system();
            //return "";
            return locale.formattedDataSize(base->getDownloadedSize());
        }

        if ( index.column() == (int)DownloadTableColumns::TRANSFER_RATE)
            return "";
        if ( index.column() == (int)DownloadTableColumns::LAST_TIME)
            return "";
        if ( index.column() == (int)DownloadTableColumns::DESCRIPTION)
            return "description";
    }
    return QVariant();
}

QVariant DownloadModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Orientation::Horizontal) {
            switch (section) {
            case (int)DownloadTableColumns::FILE_NAME:
                return "File Name";
            case (int)DownloadTableColumns::SIZE:
                return "Size";
            case (int)DownloadTableColumns::QUEUE_NAME:
                return "Q";
            case (int)DownloadTableColumns::STATUS:
                return "Status";
            case (int)DownloadTableColumns::TRANSFER_RATE:
                return "Transfer rate";
            case (int)DownloadTableColumns::DOWNLOADED:
                return "Downloaded";
            case (int)DownloadTableColumns::LAST_TIME:
                return "Last try";
            case (int)DownloadTableColumns::DESCRIPTION:
                return "Description";
            default:
                return QVariant();
            }

        }
    }
    return QVariant();
}

void DownloadModel::populate()
{
    beginResetModel();
    dm = DownloadManager::getInstance();
    endResetModel();
}

void DownloadModel::progressUpdate()
{
    BaseDownload *dl = dynamic_cast<BaseDownload*>(sender());
    if (!dl)
        return;
    int _index = dm->getDownloadList().indexOf(dl);
    emit dataChanged(createIndex(_index, (int) DownloadTableColumns::STATUS), createIndex(_index, (int) DownloadTableColumns::DOWNLOADED));
        //emit dataChanged(createIndex(0, 0), createIndex(dm->getDownloadList().size(), columnCount()));
}

void DownloadModel::stateUpdate()
{
    BaseDownload *dl = dynamic_cast<BaseDownload*>(sender());
    if (!dl)
        return;
    int _index = dm->getDownloadList().indexOf(dl);
    emit dataChanged(createIndex(_index, 0), createIndex(_index, columnCount()));
}
