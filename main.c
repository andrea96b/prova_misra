#include "header.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N_AGGIORNAMENTI 3
#define N_THREADS 5

static GestioneVoli monitor;


void *produttore(void *arg)
{

	int identificativo = (int) arg;
	int i;
	int quota = 0;
	printf("[PRODUTTORE] Produttore creato: identificativo volo:%d\n",identificativo);
	sleep(3);
	InserisciVolo(&monitor, identificativo);
	
	for(i = 0; i < N_AGGIORNAMENTI; i++)
	{	
		if(i == 0 || i == N_AGGIORNAMENTI-1) quota = 1000;
		else quota = 2000;
		
		pthread_mutex_lock(&monitor.mutex);
		printf("[PRODUTTORE] Aggiornamento volo:%d alla quota:%d in corso...\n",identificativo,quota);
		sleep(3);
		AggiornaVolo(&monitor, identificativo, quota);
		pthread_mutex_unlock(&monitor.mutex);
	}
	
	pthread_mutex_lock(&monitor.mutex);
	printf("[PRODUTTORE] Rimozione volo:%d in corso...\n",identificativo);
	sleep(3);
	RimuoviVolo(&monitor,identificativo);
	printf("[PRODUTTORE] Volo:%d rimosso\n",identificativo);
	sleep(3);
	monitor.nelem--;
	pthread_cond_signal(&(monitor.ok_inserisci));
	pthread_mutex_unlock(&monitor.mutex);
	pthread_exit(NULL);
}


int main()
{
	int i;
	int st;
	srand(time(NULL));
	pthread_t threads[N_THREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	InitMonitor(&monitor);

	
	
	for(i = 0; i < N_THREADS; i++)
	{
		st = pthread_create(&threads[i], &attr, produttore, (void*)i);
		if(st == 0)
		{
			printf("[MAIN] produttore creato con successo\n");
		}
	}
	
	
	
	
	
	for(i = 0; i < N_THREADS; i++)
	{
		pthread_join(threads[i],NULL);
		printf("[MAIN] produttore terminato con successo\n");
		
	}
	pthread_attr_destroy(&attr);
	RemoveMonitor(&monitor);
	return 0;
	
}
