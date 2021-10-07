#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sensor.h"
#include <sys/types.h>


#define BUFF_SIZE 1024

int res_sensor=0;

void sensor();
void play();


void sensor()
{
    while(res_sensor==0)
    {
        res_sensor=sensing();
        printf("Result = %d\n",res_sensor);
        sleep(0.01);
    }
}

void play()
{
    system("aplay audio/test.wav");
    res_sensor=0;
}

int main()
{
    FILE *fp_check;
    fp_check=popen("ps -ef | grep ./main","r");
    int count_check=0;
    char *b_check;
    char buff_check[BUFF_SIZE];

    while((b_check=fgets(buff_check,BUFF_SIZE,fp_check)!=NULL))
    {
        printf("%s",buff_check);
        count_check++;
    }
    printf("first count = %d\n",count_check);
    pclose(fp_check);
    if(count_check>=4)
    {
        pid_t this_pid=getpid();
        char msg[20];
        sprintf(msg,"kill %d",this_pid);
        system(msg);   
    }

    if(sensorSetup() == -1)
    {
        return -1;
    }
    while(1)
    {
        sensor();
        if(res_sensor==1)
        {
            if(isWeekend()==1) continue;
            if(isWorkHour()==0) continue;
            play();
            sleep(5);
        }
        
        
    }
    return 0;
}

