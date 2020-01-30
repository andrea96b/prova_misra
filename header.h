#ifndef __HEADER
#define __HEADER
#include <pthread.h>

#define DEBUG 

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

#define MAX_VOLI 3

typedef struct
{
	int identificativo;
	int quota;
} Volo;



typedef struct
{
	Volo vettore_voli[3];
	int vettore_stato[3]; // LIBERO, OCCUPATO, IN USO
	int nelem;
	pthread_mutex_t mutex;
	pthread_cond_t ok_inserisci;
} GestioneVoli;

void InitMonitor(GestioneVoli *g);
void RemoveMonitor(GestioneVoli *g);
void InserisciVolo(GestioneVoli * g, int identificativo);
void RimuoviVolo(GestioneVoli * g, int identificativo);
void AggiornaVolo(GestioneVoli * g, int identificativo, int quota);


int get_libero(GestioneVoli *g);
int trova_elemento(GestioneVoli *g, int id);


#endif
