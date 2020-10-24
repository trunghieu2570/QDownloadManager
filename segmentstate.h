#ifndef SEGMENTSTATE_H
#define SEGMENTSTATE_H
enum class SegmentState {
    NONE,
    STARTED,
    PAUSED,
    DOWNLOADING,
    ERROR,
    FINISHED
};
#endif // SEGMENTSTATE_H
