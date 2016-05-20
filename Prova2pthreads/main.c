#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS     5

struct d{
    int a;
    float b;
} dados[NUM_THREADS];

void *PrintHello(struct d *threadid)
{
    printf("%d: Iniciou!\n", threadid->a);
    int i = 0;
    while(i < 100000000){
        i++;
    }
    printf("%d: Finalizou!\n", threadid->a);
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc, t;
    for (t=0; t < NUM_THREADS; t++) {
        printf("Criando o thread %d\n", t);
        dados[t].a=t;
        dados[t].b=t*3.14;
        rc = pthread_create( &threads[t], NULL, PrintHello, &dados[t]);
        if (rc) {
            printf("Erro ao retornar do thread: %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}