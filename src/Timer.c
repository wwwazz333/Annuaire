#include "Timer.h"


double Clock(int what_do)
{
    static struct timeval start;

    if (what_do == START) {
        gettimeofday(&start, NULL);
    } else if (what_do == END) {
        struct timeval stop;
        gettimeofday(&stop, NULL);
		suseconds_t time_spend = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
        print(AQUA, DEFAULT_BACKGROUND_COLOR, "%.2lf milli-seconds\n", time_spend/1000.0f);
		return time_spend;
    }

	return -1;
}