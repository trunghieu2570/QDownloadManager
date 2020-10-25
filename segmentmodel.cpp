#include "segmentmodel.h"

int SegmentModel::rowCount(const QModelIndex &parent) const
{
    if(!dl)
        return 0;
    return dl->getSegmentList().size();
}

int SegmentModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant SegmentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if ( role == Qt::DisplayRole)
    {
        Segment *_seg = dl->getSegmentList().at(index.row());
        connect(_seg, &Segment::segmentProgressChanged, this, &SegmentModel::updateProgress);
        connect(_seg, &Segment::stateChanged, this, &SegmentModel::updateState);
        switch (index.column()) {
        case (int)SegmentTableColumns::ID:
            return QString::number(dl->getSegmentList().indexOf(_seg));
        case (int)SegmentTableColumns::RECEIVED:
        {
            QLocale locate = QLocale::system();
            return locate.formattedDataSize(_seg->getReceivedSize());
        }
        case (int)SegmentTableColumns::RATE:
            return "";
        case (int)SegmentTableColumns::STATUS:
            return "GET";
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant SegmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Orientation::Horizontal) {
            switch (section) {
            case (int)SegmentTableColumns::ID:
                return "N";
            case (int)SegmentTableColumns::RECEIVED:
                return "Received";
            case (int)SegmentTableColumns::RATE:
                return "Transfer rate";
            case (int)SegmentTableColumns::STATUS:
                return "Status";
            default:
                return QVariant();
            }

        }
    }
    return QVariant();
}

void SegmentModel::populate(ParallelDownload *pdl)
{
    beginResetModel();
    dl = pdl;
    endResetModel();
}

void SegmentModel::updateProgress(qint64, qint64)
{
    Segment *_seg = dynamic_cast<Segment*>(sender());
    if (!_seg)
        return;
    int _index = dl->getSegmentList().indexOf(_seg);
    emit dataChanged(createIndex(_index, (int) SegmentTableColumns::RECEIVED), createIndex(_index, (int) SegmentTableColumns::RECEIVED));
    //emit layoutChanged();
}

void SegmentModel::updateState()
{

}
