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
private:
    QUrl address;
    QFile *file;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    qint64 startPos, endPos;
    SegmentState state = SegmentState::NONE;
public slots:
    void download();
private slots:
    void downloadFinished(QNetworkReply*);
    void downloadProgress(qint64, qint64);
signals:
    void finished();
    void stateChanged();
};

#endif // SEGMENT_H
