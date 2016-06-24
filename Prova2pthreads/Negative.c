//
//  Negative.c
//  Prova2pthreads
//
//  Created by leonardo albuquerque on 06/06/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//
#include "Negative.h"

PPMImage *negativo (PPMImage *img)
{
    PPMImage *imgNegativo;
    imgNegativo = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgNegativo->data = (PPMPixel*)malloc(img->width * img->height * sizeof(PPMPixel));
    
    if (!imgNegativo | !imgNegativo->data) {
        fprintf(stderr, "Nao foi possivel alocar memoria\n");
        exit(1);
    }
    
    imgNegativo->width = img->width;
    imgNegativo->height = img->height;
    
    
    fprintf(stderr, "Aplicando o negativo...");
    
    
    //roda nas threads genericas, passando a função de processamento
    runOnThread(img, imgNegativo, (void *) partialNegative);
    
    fprintf(stderr, "pronto\n");
    
    return imgNegativo;
    
}

//processamento de uma tira da imagem
void partialNegative(void *arg){
    int i;
    int r,g,b;
    
    PartialData *data = (PartialData*) arg;
    
    //passa por uma tira da imagem por thread
    for ( i = data->start; i < data->end; i++ ) {
        r = 255 - data->input->data[i].red;
        data->output->data[i].red = r < 0? 0 : r;
        
        g = 255 - data->input->data[i].green;
        data->output->data[i].green = g < 0 ? 0 : g;
        
        b = 255 - data->input->data[i].blue;
        data->output->data[i].blue = b < 0 ? 0 : b;
        
    }
}
