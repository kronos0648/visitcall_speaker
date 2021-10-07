#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

time_t timer;
struct tm* t;
char dateTime[200];

void initTime();
int isWeekend();
int isWorkHour();
char *getNowTime();

void initTime()
{
    timer=time(NULL);
    t=localtime(&timer);
}

int isWeekend()
{
    initTime();
    if(t->tm_wday==0 || t->tm_wday==6) return 1;
    return 0;
}

int isWorkHour()
{
    initTime();
    int hour=t->tm_hour;
    if(hour>=9 && hour <=18) return 1;
    else if(hour==8 && t->tm_min>=50) return 1;
    return 0;
}

char *getNowTime()
{
    initTime();
    sprintf(dateTime,"[%d.%d.%d %d:%d:%d]\n",t->tm_year+1900,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    return dateTime;
}