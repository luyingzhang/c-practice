/*
 * time01.c
 *
 *  Created on: 2012/7/19
 *      Author: boris
 */

#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

    struct timeval old_time, new_time;
    double con_ms;

    gettimeofday(&new_time, (void *) 0);

    con_ms = new_time.tv_sec * 1000.0 + new_time.tv_usec / 1000.0;

    printf(
            "new_time.tv_sec = %f and new_time.tv_usec = %f , new_time convert to ms  = %llu\n",
            new_time.tv_sec, new_time.tv_usec, con_ms);

    return 0;
}
