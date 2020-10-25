#ifndef SEGMENTMODEL_H
#define SEGMENTMODEL_H

#include "paralleldownload.h"

#include <QAbstractItemModel>
#include <QObject>

enum class SegmentTableColumns {
    ID = 0,
    RECEIVED = 1,
    RATE = 2,
    STATUS = 3,
};

class SegmentModel : public QAbstractListModel
{
    Q_OBJECT
public:
    //explicit SegmentModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
public slots:
    void populate(ParallelDownload *);
    void updateProgress(qint64, qint64);
    void updateState();
private:
    ParallelDownload * dl = nullptr;
signals:

};

#endif // SEGMENTMODEL_H
