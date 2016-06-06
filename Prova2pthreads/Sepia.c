//
//  Sepia.c
//  Prova2pthreads
//
//  Created by leonardo albuquerque on 06/06/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//

#include "Sepia.h"


PPMImage *aplicaSepia(PPMImage *img)
{
    PPMImage *imgsepia;
    //Aloca a estrutura
    imgsepia = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgsepia->data = (PPMPixel*)malloc(img->width * img->height * sizeof(PPMPixel));
    
    if (!imgsepia | !imgsepia->data) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    imgsepia->width = img->width;
    imgsepia->height = img->height;
    
    
    // SEÇÃO PASSÍVEL DE OTIMIZAÇÃO
    fprintf(stderr, "Aplicando o filtro sepia...");
    
    runOnThread(img, imgsepia, (void *) partialSepia);
    
    fprintf(stderr, "pronto\n");
    return imgsepia;
}

void partialSepia(void *arg){
    int i, r,g,b;
    
    PartialData *data = (PartialData*) arg;
    
    for ( i = data->start; i < data->end; i++ ) {
        r = 0.393 * data->input->data[i].red + 0.769 * data->input->data[i].green + 0.189 * data->input->data[i].blue;
        data->output->data[i].red = r > 255 ? 255 : r;
        
        g = 0.349 * data->input->data[i].red + 0.686 * data->input->data[i].green + 0.168 * data->input->data[i].blue;
        data->output->data[i].green = g > 255 ? 255 : g;
        
        b = 0.272 * data->input->data[i].red + 0.534 * data->input->data[i].green + 0.131 * data->input->data[i].blue;
        data->input->data[i].blue = b > 255 ? 255 : b;
        
    }
}