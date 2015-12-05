#ifndef OTSU
#define OTSU
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <otsu.h>

using namespace cv;

typedef struct max_min_tag{
  int max;
  int min;
}max_min;

void histograma(Mat ima,int *hism){
    int i,aux;
    for(i=0;i<ima.rows*ima.cols;i++){
      aux = ima.data[i];
      hism[aux]++;
    }
}

double* Distri_proba_his_acumulado(int *his,int tam){
    int i,valor;
    double* probaH,aux;
    aux=0;
    probaH = (double*)malloc(256*sizeof(double));
    for(i=0;i<256;i++){
        valor = his[i];
        probaH[i] = (double) valor / tam;
        aux =  aux + probaH[i];
        probaH[i] = aux;
    }
    return probaH;
}


void obtener_maxmin(int *his,max_min *minmax){
    int i,max,min;
    max=his[0];
    min=10000;
    for(i=1;i<256;i++){
        if(max<his[i])
            max = his[i];
        if(his[i]!=0){
            if(his[i]<min)
                min = his[i];
        }
    }

    minmax->max = max;
    minmax->min = min;
}

double* obtener_momento(int* his,double* omg,int ta){
    int i;
    double *vec_moment,aux,proba;
    vec_moment = (double*)malloc(256*sizeof(double));
    for(i=0;i<256;i++){
        proba =  (double) his[i] / ta;
        aux = i*proba;
       vec_moment[i] = vec_moment[i] +  (aux / omg[i]);
    }
    return vec_moment;
}

int rb(double *omeg,double *momento){
    int k,*humbral,max;
    double aux,aux1,aux2;
    humbral = crear_vector(256);
    for(k=0;k<256;k++){
        aux2 = omeg[k]*momento[k] - momento[k];
        aux1 = pow(aux2,2);
        aux = omeg[k]*(1-omeg[k]);
        humbral[k] =(int) aux1/aux;
    }
    max = humbral[0];
    for(k=1;k<256;k++){
        if(humbral[k-1]<humbral[k])
            max = k;
    }
    return max;
}


void normalizar_histograma(int *his,int max){
    int i;
    float aux2,aux3;
    for(i=0;i<256;i++){
        aux2=(float) his[i] / max;
        aux3=aux2*256;
        his[i]=(int)aux3;
    }
}

int* normalizar_histograma_acumulado(double *hisA){
    int i,*hisNo;
    double aux;
    hisNo = crear_vector(256);
    for(i=0;i<256;i++){
        aux = hisA[i]*256;
        hisNo[i] = (int) aux;
    }
    return hisNo;
}

void dibujar_histograma(int **m,int *his){
    int i,k;
    for(i=0;i<256;i++){
        for(k=255;k>(255-his[i]);k--){
            m[k][i]=255;
        }
    }
}

#endif // OTSU

