#include <sched.h>
#include <stdio.h>
#include <time.h>
#ifndef SCHED_BATCH
#define SCHED_BATCH 3
#endif



int newPolicy(int policy, int priority){

	struct sched_param param;
        param.sched_priority = priority;
	


	if (sched_setscheduler(0, policy, &param) !=0){
	perror("Erro ao definir politica de escalnamento");
	return -1;
	}
	return 0;
}

void contar(){

	int contador = 0;
	for (int i = 0; i < 20*50; i++){
		contador += 1;
		printf(" ");
	}
	}

int main(void){
	struct timespec start, end;
	long elapsed_time, a, b, c, d;
	int status;
	printf("Definido FIFO\n");
	status = newPolicy(SCHED_FIFO, 10);
	if (status == 0){
		clock_gettime(CLOCK_MONOTONIC, &start);
		contar();
		clock_gettime(CLOCK_MONOTONIC, &end);
		elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
		a = elapsed_time;
		//return status;
	}
	

	printf("Definido RR\n");
	status = newPolicy(SCHED_RR, 10);
	if (status == 0){
		clock_gettime(CLOCK_MONOTONIC, &start);
		contar();
		clock_gettime(CLOCK_MONOTONIC, &end);
		elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
		
		b = elapsed_time;
		//return status;
	}

	printf("Definindo Batch\n");
	status = newPolicy(SCHED_BATCH, 0);
	if (status == 0){
		clock_gettime(CLOCK_MONOTONIC, &start);
		contar();
		clock_gettime(CLOCK_MONOTONIC, &end);
		elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
		c = elapsed_time;
		//return status;
	}
	
	

	printf("Definindo Other\n");
	status = newPolicy(SCHED_OTHER, 0);
	if (status == 0){
		clock_gettime(CLOCK_MONOTONIC, &start);
		contar();
		clock_gettime(CLOCK_MONOTONIC, &end);
		elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
		d = elapsed_time;	
		//return status;
	}
	printf("O tempo de execução de FIFO, RR, Batch e Other são, respectivamente:\n %1ld\n %1ld\n %1ld\n %1ld.\n", a,b,c,d); 
	return 0;
}


