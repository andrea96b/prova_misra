#include "header.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void InitMonitor(GestioneVoli *g)
{
	int i;
	for(i = 0; i < MAX_VOLI; i++)
	{
		g->vettore_stato[i] = LIBERO;
	}
	g->nelem = 0;
	pthread_mutex_init(&(g->mutex),NULL);
	pthread_cond_init(&(g->ok_inserisci),NULL);
}


void RemoveMonitor(GestioneVoli *g)
{
	pthread_mutex_destroy(&(g->mutex));
	pthread_cond_destroy(&(g->ok_inserisci));
}


void InserisciVolo(GestioneVoli * g, int identificativo)
{
	int index;
	Volo temp;
	temp.identificativo = identificativo;
	temp.quota = 0;
	
	pthread_mutex_lock(&(g->mutex));
	while(g->nelem == MAX_VOLI) 
	{ //non vi è spazio, sospendo il thread
		pthread_cond_wait(&(g->ok_inserisci),&(g->mutex));
	}
	
	index = get_libero(g);
	g->nelem++;
	g->vettore_stato[index] = IN_USO;
	pthread_mutex_unlock(&(g->mutex));
	
	sleep(1);
	g->vettore_voli[index].identificativo = temp.identificativo;
	g->vettore_voli[index].quota = temp.quota;
	printf("[DEBUG] Volo:%d inserito nella posizione:%d\n",identificativo,index);
	sleep(3);
	
	pthread_mutex_lock(&(g->mutex));
	g->vettore_stato[index] = OCCUPATO;
	pthread_mutex_unlock(&(g->mutex));
	
	
}
void RimuoviVolo(GestioneVoli * g, int identificativo)
{
	int index = trova_elemento(g,identificativo);
	g->vettore_stato[index] = IN_USO;
	sleep(1);
	g->vettore_stato[index] = LIBERO;
}


void AggiornaVolo(GestioneVoli * g, int identificativo, int quota)
{
	int i = 0;
	while((g->vettore_voli[i].identificativo != identificativo) && (g->vettore_stato[i] != OCCUPATO)) i++;
	g->vettore_stato[i] = IN_USO;
	sleep((rand()%3) + 1);
	g->vettore_voli[i].quota = quota;
	g->vettore_stato[i] = OCCUPATO;
}




int get_libero(GestioneVoli *g)
{
	int i = 0;
	while(g->vettore_stato[i] != LIBERO)
	{
		i++;
	}
	return i;
}

int trova_elemento(GestioneVoli *g, int id)
{
	int i = 0;
	while(g->vettore_voli[i].identificativo != id) i++;
	
	return i;
}
