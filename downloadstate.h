#ifndef DOWNLOADSTATE_H
#define DOWNLOADSTATE_H
enum class DownloadState {
    NONE,
    PREPARING,
    STARTED,
    PAUSED,
    DOWNLOADING,
    ERROR,
    FINISHED
};
#endif // DOWNLOADSTATE_H
