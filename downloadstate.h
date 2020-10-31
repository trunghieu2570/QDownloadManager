#ifndef DOWNLOADSTATE_H
#define DOWNLOADSTATE_H
enum class DownloadState {
    NONE,
    PREPARING,
    PAUSED,
    DOWNLOADING,
    ERROR,
    WRITING,
    FINISHED
};
#endif // DOWNLOADSTATE_H
