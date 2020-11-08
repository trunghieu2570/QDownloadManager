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
    qint64 downloadedSize = 0;
    RemoteFileInfo *rfInfo;
    QTimer *timer = nullptr;
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
    void loadInfo();
    void writeFile();
    void writeJson(QJsonObject &json) const;
    bool checkFileExist();
    void setRemoteInfo(RemoteFileInfo *value);

public slots:
    void start();
    void stop();
    void pause();
private slots:
    void getInfoFinished();
    void calculateProgress();
signals:
    void prepareFinished();
};

#endif // PARALLELDOWNLOAD_H
