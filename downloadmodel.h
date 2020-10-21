#ifndef DOWNLOADMODEL_H
#define DOWNLOADMODEL_H

#include "basedownload.h"

#include <QAbstractItemModel>
#include <QObject>

enum class DownloadTableColumns {
    FILE_NAME = 0,
    QUEUE_NAME = 1,
    SIZE = 2,
    STATUS = 3,
    TRANSFER_RATE = 4,
    LAST_TIME = 5,
    DESCRIPTION = 6
};

class DownloadModel : public QAbstractListModel
{
    Q_OBJECT
public:
    //explicit DownloadModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
public slots:
    void populate();
private:
    QList<BaseDownload*> list;
signals:

};

#endif // DOWNLOADMODEL_H
