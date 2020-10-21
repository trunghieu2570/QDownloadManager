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
    QList<Segment*> * segmentList;
    QFile *file;
    qint64 size;
    int max = 8;
    RemoteFileInfo *fileInfo;
    void generateSegments();
    void downloadSegments();
    void prepare();
public:
    explicit ParallelDownload(QObject *parent = nullptr);
    qint64 getSize();
    //ParellelDownload();
public slots:
    void start();
    void stop();
    void pause();
private slots:
    void getInfoFinished();
signals:
    void prepareFinished();
};

#endif // PARALLELDOWNLOAD_H
