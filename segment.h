#ifndef SEGMENT_H
#define SEGMENT_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "segmentstate.h"

class Segment : public QObject
{
    Q_OBJECT
public:
    explicit Segment(QObject *parent = nullptr);
    Segment(const QUrl&, QFile *, qint64, qint64);
    SegmentState getCurrentState();
    qint64 getReceivedSize() const;
    qint64 getTotalSize() const;

private:
    QUrl address;
    QFile *file;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    qint64 startPos, endPos;
    qint64 received = 0, total;
    SegmentState state = SegmentState::NONE;
public slots:
    void download();
private slots:
    void downloadFinished(QNetworkReply*);
    void downloadProgress(qint64, qint64);
signals:
    void finished();
    void segmentProgressChanged(qint64, qint64);
    void stateChanged();
};

#endif // SEGMENT_H
