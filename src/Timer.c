#include "Timer.h"


suseconds_t Clock(int what_do)
{
    static struct timeval stop, start;

    if (what_do == START) {
        gettimeofday(&start, NULL);
    } else if (what_do == END) {
        gettimeofday(&stop, NULL);
		suseconds_t time_spend = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
        print(AQUA, DEFAULT_BACKGROUND_COLOR, "%lu micro-seconds\n", time_spend);
		return time_spend;
    }

	return 0;
}