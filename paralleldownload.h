#ifndef PARALLELDOWNLOAD_H
#define PARALLELDOWNLOAD_H

#include "basedownload.h"
#include "remotefileinfo.h"
#include "segment.h"

#include <QObject>

class ParallelDownload : public BaseDownload
{
    Q_OBJECT
private:
    QList<Segment*> segmentList;
    QFile *file;
    int max = 8;
    //qint64 downloadedSize;
    RemoteFileInfo *fileInfo;
    void generateSegments();
    void downloadSegments();
    void prepare();
public:
    explicit ParallelDownload(QObject *parent = nullptr);
    //ParellelDownload();
    DownloadType getType() const;
    QList<Segment *> getSegmentList();
    qint64 getDownloadedSize() const;
    qint64 getSize() const;
public slots:
    void start();
    void stop();
    void pause();
    void emitDownloadProgressChange();
private slots:
    void getInfoFinished();
signals:
    void prepareFinished();
};

#endif // PARALLELDOWNLOAD_H
