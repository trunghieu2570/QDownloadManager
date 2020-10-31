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
    Segment(const QString &, QFile *, qint64, qint64);
    SegmentState getCurrentState();
    qint64 getReceivedSize() const;
    qint64 getTotalSize() const;
    QFile *getFile() const;

private:
    QString address;
    QFile *file;
    QNetworkAccessManager qnam;
    QNetworkReply *reply = nullptr;
    qint64 startPos, endPos, currentPos;
    qint64 received = 0, total;
    SegmentState state = SegmentState::NONE;
public slots:
    void download();
    void stop();
private slots:
    void downloadFinished();
    void downloadProgress(qint64, qint64);
    void dataReadyRead();
signals:
    void finished();
    void segmentProgressChanged(qint64, qint64);
    void stateChanged();
};

#endif // SEGMENT_H
