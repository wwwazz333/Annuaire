#include "Timer.h"


void Clock(int what_do)
{
    static struct timeval stop, start;

    if (what_do == START) {
        gettimeofday(&start, NULL);
    } else if (what_do == END) {
        gettimeofday(&stop, NULL);
        print(AQUA, DEFAULT_BACKGROUND_COLOR, "%lu micro-seconds\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    }
}