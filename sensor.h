#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datetime.h"

#define SENSOR1 1
#define SENSOR2 4

int sensorSetup();
int sensing();

int sensorSetup()
{
    if(wiringPiSetup() == -1)
    {
        FILE *fp_log;
        fp_log=fopen("log/error.log","a");
        char error_log[100]="wiringPiSetup error";
        strcat(error_log,getNowTime());
        fprintf(fp_log,error_log);
        fclose(fp_log);
        return -1;
    }

    pinMode(SENSOR1,INPUT);
    pinMode(SENSOR2,INPUT);
    return 0;
}

int sensing()
{
    int res1=digitalRead(SENSOR1);
    int res2=digitalRead(SENSOR2);
    printf("%d\t%d\n",res1,res2);
    if(res1==1||res2==1)
    {
        return 1;
    }
    
    return 0;
}
