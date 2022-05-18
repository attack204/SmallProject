#ifndef __common_h__
#define __common_h__

#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>

double GetTime()
{ // 获取当前时间
    struct timeval t;
    int rc = gettimeofday(&t, NULL);
    assert(rc == 0);
    return (double)t.tv_sec + (double)t.tv_usec / 1e6;
}

void Spin(int howlong)
{ // 等待howlong
    double t = GetTime();
    while ((GetTime() - t) < (double)howlong)
        ;
}

#endif
