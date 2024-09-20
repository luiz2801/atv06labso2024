#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>

#define N 500 // Limite do contador

int newPolicy(int policy, int priority){
	struct sched_param param;
	param.sched_priority = priority;

	if (sched_setscheduler(0, policy, &param) != 0){
		perror("Erro ao definir política de escalonamento");
		return -1;
	}
	return 0;
}

void contar(){
	int contador = 0;
	for (int i; i <= N; i++){
		contador = i;
	}
	printf("Contador chegou a: %d\n", contador);
}

int main(void){
	struct timespec start, end;
	long elapsed_time;	
	int policies[] = {SCHED_RR, SCHED_OTHER, SCHED_FIFO, SCHED_BATCH};
	const char *policy_names[] = {"RR", "Other", "FIFO", "Batch"};












	for (int i = 0; i < 3; i++) {
		printf("Executando com a política %s\n", policy_names[i]);

		if (newPolicy(policies[i], 0) != 0){
			return -1;
		}

		clock_gettime(CLOCK_MONOTONIC, &start);
		contar();
		clock_gettime(CLOCK_MONOTONIC, &end);

		elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
		printf("Tempo de execução para %s: %1ld ns\n", policy_names[i], elapsed_time);
	}
	return 0;
}

