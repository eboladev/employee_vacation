#include <stdio.h>

#include <locale.h>
#include <time.h>
#include <sys/time.h>

void print_time( )
{
    struct timeval tp;
    gettimeofday( &tp, 0 );
    struct tm *ptm = 0;
    ptm = localtime( &(tp.tv_sec) );
    printf("%2.2d-%2.2d-%d\n", ptm->tm_mday, ptm->tm_mon, ptm->tm_year + 1900 );
    printf("%2.2d:%2.2d:%2.2d\n", ptm->tm_hour, ptm->tm_min, ptm->tm_sec );
    printf("Week day:%d, Year day:%d\n", ptm->tm_wday, ptm->tm_yday );
    printf("TZ:%s, gmtoff:%lu, isdst:%d\n", ptm->tm_zone, ptm->tm_gmtoff, ptm->tm_isdst );


    setlocale( LC_TIME, "ru_RU.UTF-8" );
    char tmbuf[128];
    size_t sz = strftime( tmbuf, 128, "%B", ptm );
    if( sz )
    {
        printf( "Month full name - \'%s\'\n", tmbuf );
    }
    printf( "%s\n", ctime(&(tp.tv_sec)) );

    ptm = gmtime( &(tp.tv_sec) );
    printf("GMTime\n" );
    printf("%2.2d-%2.2d-%d\n", ptm->tm_mday, ptm->tm_mon, ptm->tm_year + 1900 );
    printf("%2.2d:%2.2d:%2.2d\n", ptm->tm_hour, ptm->tm_min, ptm->tm_sec );
    printf("Week day:%d, Year day:%d\n", ptm->tm_wday, ptm->tm_yday );
    printf("TZ:%s, gmtoff:%lu, isdst:%d\n", ptm->tm_zone, ptm->tm_gmtoff, ptm->tm_isdst );
}

int main(void)
{
    print_time( );

    return 0;
}

