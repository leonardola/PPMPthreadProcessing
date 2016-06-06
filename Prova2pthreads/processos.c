//
//  processos.c
//  Imagem04
//
//  Created by Marcelo Cendron on 30/04/16.
//  Copyright © 2016 Marcelo Cendron. All rights reserved.
//

#include "main.h"

int MIN(int X, int Y){
    return (X < Y) ? X : Y;
}
int MAX(int X, int Y){
    return (X > Y) ? X : Y;
}


void *histograma (PPMImage *histImage)
{
    int i, *hist;
    
    //Aloca o espaço para os pixeis
    hist = (int *)malloc(256 * sizeof(int));
    
    if (!histImage->dataBW) {
        fprintf(stderr, "A imagem passada deve ser preta e branca\n");
        exit(1);
    }
    
    if (!hist) {
        fprintf(stderr, "Nao foi possivel alocar memoria\n");
        exit(1);
    }
    fprintf(stderr, "Gerando o histograma...");
    
    /* Zera todos os elementos do histograma. */
    for (i=0; i<256; i++)
        hist[i] = 0;
    
    for (i=0; i < (histImage->width * histImage->height); i++)
        hist[histImage->dataBW[i]]++;
    
    fprintf(stderr, "pronto\n");
    fprintf(stderr, "Imprimindo histograma...\n");
    
    for(i=0; i <= 255; i++)
    {
        printf("%3d%10d", i, hist[i]);
        printf("\n");
    }
    
    /*
     int *hist2 = (int *)malloc(256 * sizeof(int));
     for (i=0; i<256; i++)
     hist2[i] = 0;
     
     for (i=0; i < (histImage->width * histImage->height); i++)
     hist2[histImage->dataBW[i]]++;
     
     
     fprintf(stderr, "pronto\n");
     fprintf(stderr, "!!!!Comparando os histogramas...\n");
     
     for(i=0; i <= 255; i++)
     {
     if (hist[i] != hist2[i]){
     printf("Diferente: %3d%10d\n", i, hist[i]);
     }
     }
     
     fprintf(stderr, "pronto\n");
     */
    
    return hist;
    
}




PPMImage *aumentaBrilho(PPMImage *img, unsigned char valor)
{
    int i;
    PPMImage *imgBrilho;
    int r, g, b;
    //Aloca a estrutura
    imgBrilho = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgBrilho->data = (PPMPixel*)malloc(img->width * img->height * sizeof(PPMPixel));
    
    if (!imgBrilho | !imgBrilho->data) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    imgBrilho->width = img->width;
    imgBrilho->height = img->height;
    
    
    // SEÇÃO PASSÍVEL DE OTIMIZAÇÃO
    fprintf(stderr, "Aplicando brilho a mais...");
    for ( i = 0; i < (img->width * img->height); i++ ) {
        r = img->data[i].red + valor;
        imgBrilho->data[i].red = r > 255? 255 : r;
        
        g = img->data[i].green + valor;
        imgBrilho->data[i].green = g > 255? 255 : g;
        
        b =img->data[i].blue + valor;
        imgBrilho->data[i].blue = b > 255? 255 : b;
        
    }
    fprintf(stderr, "pronto\n");
    return imgBrilho;
}

PPMImage *aplicaThresold(PPMImage *img, unsigned char valor)
{
    int i;
    PPMImage *imgThresold;
    
    if (!img->dataBW){
        fprintf(stderr, "A imagem passada precisa ser convertida para escala de cinza\n");
        fprintf(stderr, "faça uma chamada a função converteBW(PPMImage *img) antes\n");
        return NULL;
        
    }
    //Aloca a estrutura
    imgThresold = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgThresold->dataBW = (byte*)malloc(img->width * img->height * sizeof(byte));
    
    if (!imgThresold | !imgThresold->dataBW) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    imgThresold->width = img->width;
    imgThresold->height = img->height;
    
    // SEÇÃO PASSÍVEL DE OTIMIZAÇÃO
    
    fprintf(stderr, "Aplicando o thresold...");
    for ( i = 0; i < (img->width * img->height); i++ ) {
        if(img->dataBW[i] < valor){
            imgThresold->dataBW[i] = 0;
        }else
            imgThresold->dataBW[i] = 255;
        
    }
    fprintf(stderr, "pronto\n");
    return imgThresold;
}




