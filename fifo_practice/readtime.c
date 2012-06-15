#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BILLION  1000000000L;
FILE *trans_fptr = NULL;


int main(int argc, char *argv[])
{
    int fp;
    char buf [ 512 ];
    int l; // read length
    int i;

    buf [ 0 ] = '\0'; // in case there is nothing to read
    buf [ 512 ] = '\0'; // garentee a end-of-line

    fp = open("/home/boris/temp/myfifo", O_RDONLY);
    if(fp == -1) {
        printf("Could not open the pipe\n");
    }

    while(1) {


        struct timespec start, stop;
        double accum;

        if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
          perror( "clock gettime" );
          return EXIT_FAILURE;
        }

        l = read(fp, buf, 511);
        if(l) // print only if the read length is greater than 0
            printf("%s", buf); //debug only

//        system( argv[1] );

        if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
          perror( "clock gettime" );
          return EXIT_FAILURE;
        }

        accum = ( stop.tv_sec - start.tv_sec )
                 + (double)( stop.tv_nsec - start.tv_nsec )
                   / (double)BILLION;
        printf( "耗時: %lf\n", accum );



        for(i=0; i<512; i++) // initialize the whole buffer again
            buf[i] = '\0';
    }

    close(fp);
    return 0;
}
