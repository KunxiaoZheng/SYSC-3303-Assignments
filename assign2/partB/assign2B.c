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
RT_MUTEX a,g;

static int accNum;
static int gyroNum;
static int done;
static int finalNum[100];
static int sizeQ=35;
static int sizeFinal=100;
static int gyroQ[35];


void Acc()
{
	int aPosition=0;
	while (done!=0){

		rt_mutex_acquire(&a,TM_INFINITE);
		accNum=rand()%100+1;
		rt_mutex_release(&a);

		aPosition++;
		if(aPosition==5){
			aPosition=0;
		}
		usleep(33334);
	}
}
void gyro()
{
	int tempNum=0;
	int flag=0;
	int result;
	int gPosition=0;
	while (done!=0){
		result=0;
		flag=0;
		while(flag<sizeQ){
			result+=gyroQ[flag];
			flag++;
		}
		result=result/sizeQ;
		tempNum=rand()%366;
		gyroQ[gPosition]=tempNum;
		gPosition++;
		if(gPosition>=sizeQ){
			gPosition=0;
		}

		rt_mutex_acquire(&g,TM_INFINITE);
		gyroNum=result;
		rt_mutex_release(&g);

		usleep(3334);
	}
}
void fusionT(){
	int flag=0;
	int aResult=0;
	int gResult=0;
	int g_size;
	while(flag<sizeFinal){
		usleep(16667);
		rt_mutex_acquire(&a,TM_INFINITE);
		aResult=accNum;
		rt_mutex_release(&a);
		rt_mutex_acquire(&g,TM_INFINITE);
		gResult=gyroNum;
		rt_mutex_release(&g);
		aResult=(aResult+gResult)/2;
		finalNum[flag]=aResult;
		flag++;
	}
	done= 0;
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

	done=1;

	int flag=0;
	while (flag<sizeQ){
		gyroQ[flag]=rand()%366;
		flag++;
	}

	int err =rt_mutex_create(&a,"MyMutex");
	err =rt_mutex_create(&g,NULL);

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
	rt_mutex_delete(&g);

	flag=0;
	while (flag<sizeFinal){
		rt_printf("%d\n",finalNum[flag]);
		flag++;
	}
}
