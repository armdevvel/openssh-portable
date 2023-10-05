#include <sys/utime.h>

#define utimbuf _utimbuf
#define utimes w32_utimes

int usleep(unsigned int);
#define gettimeofday mingw_gettimeofday
int nanosleep(const struct timespec *, struct timespec *);
int w32_utimes(const char *, struct timeval *);