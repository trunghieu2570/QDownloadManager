#ifndef DOWNLOADMODEL_H
#define DOWNLOADMODEL_H

#include "basedownload.h"
#include "downloadmanager.h"

#include <QAbstractItemModel>
#include <QObject>
#include <QTimer>

enum class DownloadTableColumns {
    FILE_NAME = 0,
    QUEUE_NAME = 1,
    SIZE = 2,
    STATUS = 3,
    DOWNLOADED = 4,
    TRANSFER_RATE = 5,
    LAST_TIME = 6,
    DESCRIPTION = 7
};

class DownloadModel : public QAbstractListModel
{
    Q_OBJECT
public:
    //explicit DownloadModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
public slots:
    void populate();
    void progressUpdate();
    void stateUpdate();
private:
    DownloadManager *dm = nullptr;

signals:

};

#endif // DOWNLOADMODEL_H
