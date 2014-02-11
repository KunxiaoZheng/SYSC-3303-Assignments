#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/timer.h>
#include <rtdk.h>
#include <native/mutex.h>
RT_TASK Accelerometer;
RT_TASK gyroscope;
RT_TASK fusion;
RT_MUTEX a;

typedef struct
{
  int num;
  char c;
}t_input;

static int accQ[5];
static int qyroQ[30];
static int done;
static int result[20];
static int aPosition=0;
static int gPosition=0;
static int rPosiont=0;


void Acc()
{
  while (done!=0){
    accQ[aPosition]=rand()%100+1;
    aPosition++;
    if(aPosition==5){
      aPosition=0;
    }
    sleep(30000);
  }
}
void gyro()
{
  int temp=0;
  int flag;
  int ave=0;
  int result;
  while (done!=0){
    temp=rand()%366;
      result=result+qyroQ[flag-1];
      flag--;
      qyroQ[gPosition]=result;
    gPosition++;
    if(gPosition>=30){
      gPosition=0;
    }
    sleep(300000);    
  }
}
void fusionT(){
  int flag=0;
  int aResult=0;
  int gResult=0;
  int g_size;
  while(flag<20){
    aResult=accQ[aPosition];  
    g_size=30;
    while(g_size!=0){
      gResult=gResult+ qyroQ[g_size-1];
      g_size--;
    }  
    gResult=gResult/30;
aResult=(aResult+gResult)/2;
result[flag]=aResult;
flag++;
    sleep(60000);    
  }
}

void catch_signal(int sig)
{
}

int main(int argc, char* argv[])
{
  rt_print_auto_init(1);
  signal(SIGTERM, catch_signal);
  signal(SIGINT, catch_signal);
  mlockall(MCL_CURRENT|MCL_FUTURE);

  

  int err =rt_mutex_create(&a,"MyMutex"); 

  rt_task_create(&Accelerometer,NULL , 0, 0, T_JOINABLE);
  rt_task_create(&gyroscope, NULL, 0, 0, T_JOINABLE);
  rt_task_create(&fusion, NULL, 0, 0, T_JOINABLE);
  rt_task_start(&gyroscope, &gyro,NULL);
  rt_task_start(&Accelerometer, &Acc, NULL);
  rt_task_start(&fusion, &fusionT, NULL);

  rt_task_join(&gyroscope);
  rt_task_join(&Accelerometer);
  rt_task_join(&fusion);

  rt_task_delete(&gyroscope);
  rt_task_delete(&Accelerometer);
  rt_task_delete(&fusion);

  rt_mutex_delete(&a);
int flag=0;
while (flag<20){
rt_printf("%d",result[flag]);
flag++;
}
}
