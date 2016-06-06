//
//  BlackAndWhite.c
//  Prova2pthreads
//
//  Created by leonardo albuquerque on 20/05/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//

#include "BlackAndWhite.h"


PPMImage *converteBW(PPMImage *img)
{
    PPMImage *imgBW;
    
    long numberOfCores;
    
    numberOfCores = getNumberOfCores();
    
    //Aloca a estrutura
    imgBW = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgBW->dataBW = (byte*)malloc(img->width * img->height * sizeof(byte));
    
    if (!imgBW | !imgBW->dataBW) {
        fprintf(stderr, "Nao foi possivel alocar memoria\n");
        exit(1);
    }
    
    imgBW->width = img->width;
    imgBW->height = img->height;
    
    fprintf(stderr, "Convertendo para escala de cinza...");
    
    runOnThread(img, imgBW, (void*) *partialBW);
    
    fprintf(stderr, "pronto\n");
    return imgBW;
}

void partialBW(void *arg){
    int tmp;
    int i;

    
    PartialData *data = (PartialData*) arg;
    
    for(i = data->start; i < data->end; i++){
        tmp = (int) ( data->input->data[i].red * 0.299 +
                     data->input->data[i].green * 0.587 +
                     data->input->data[i].blue * 0.114);
        
        data->output->dataBW[i] = tmp > 255? 255 : tmp;
    }
}