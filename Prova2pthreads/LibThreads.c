//
//  LibThreads.c
//  Prova2pthreads
//
//  Created by leonardo albuquerque on 20/05/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//

#include "LibThreads.h"
#include <unistd.h>
#include "main.h"

long getNumberOfCores(){
    return sysconf(_SC_NPROCESSORS_ONLN) / 2;
}

//passe a imagem de entrada e de saida e a função com o processamento
//sucesso!!!
void runOnThread(PPMImage* img, PPMImage* imgBW, void (*function)(PartialData*)){
    int imageSize, chunksize, start, end, i;
    long numberOfCores = getNumberOfCores();
    
    pthread_t * thread = malloc(sizeof(pthread_t)* numberOfCores);
    
    if(!thread){
        printf("Nao foi possivel alocar memoria para as threads");
    }
    
    PartialData * data = malloc(sizeof(PartialData) * numberOfCores);
    
    if(!data){
        printf("Nao foi possivel alocar memoria para as threads");
    }
    
    //quebra a imagem em tiras
    imageSize = img->width * img->height;
    
    chunksize = imageSize / numberOfCores;
    start = 0;
    end = chunksize;
    
    //cria uma thread por nucleo
    for(i = 0; i < numberOfCores; i++){
        data[i].input = img;
        data[i].output = imgBW;
        data[i].start = start;
        data[i].end = end;
        
        createThread(&data[i], (void*)*function, &thread[i]);
        
        start = end;
        end += chunksize;
        
    }
    
    //espera o termino das threads
    for(i = 0; i < numberOfCores; i++){
        int res = pthread_join(thread[i], NULL);
        if(res == EINVAL){
            printf("Erro EINVAL\n");
        }
        if(res == ESRCH){
            printf("ESRCH\n");
        }
        
        if(res == EDEADLK){
            printf("EDADLK\n");
        }
        if(res){
            printf("Erro %d ao sincronizar thread %d\n", res, i);
        }
    }
    
    //libera memória
    free(thread);
    free(data);
    
}


//cria a thread propriamente dita
void createThread(PartialData* data, void (*function)(PartialData*), pthread_t* thread ){
    int rc;
    
    rc = pthread_create( thread, NULL, (void*) *function, data);
    if (rc) {
        printf("Erro ao retornar do thread: %d\n", rc);
        exit(-1);
    }
}