#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <math.h>
#include <matrix.h>
#include <otsu.h>
#include <imagen.h>

using namespace cv;

int main(){

    int **Ima_histograma,**Ima_histograma_acumulado,**imagen_matrix;
    int filas,columnas,humbral;
    int *histo,*histo_acumulado;

    double *dis_pro,*momento;
    filas = 256, columnas=256;

    Mat ima,ima_histo,ima_histo_acum,ima_humbral;
    max_min valores;

    ima = imread("barsa2.bmp",CV_LOAD_IMAGE_GRAYSCALE);

    cvNamedWindow("Imagen",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Histograma",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Histograma Acumulado",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen humbral",CV_WINDOW_AUTOSIZE);

    /*creando matrices para imagenes de histogramas*/
    Ima_histograma = crear_matrix(filas,columnas);
    Ima_histograma_acumulado =  crear_matrix(filas,columnas);
    imagen_matrix = crear_matrix(ima.rows,ima.cols);

    /*vector con valores los datos de la imagen y vector para datos del histograma*/
    imagen_matrix = convertir_vector_imagen_a_matrix(ima);
    histo = crear_vector(256);

    /*obtencion del histograma de la imagen*/
    histograma(ima,histo);

    /*obteniendo el vector de probabilidad de histigrama acumulado*/
    dis_pro = Distri_proba_his_acumulado(histo,ima.rows*ima.cols);
    obtener_maxmin(histo,&valores);

    momento = obtener_momento(histo,dis_pro,ima.rows*ima.cols);
    humbral = rb(dis_pro,momento);

    histo_acumulado = normalizar_histograma_acumulado(dis_pro);
    normalizar_histograma(histo,valores.max);

    dibujar_histograma(Ima_histograma,histo);
    dibujar_histograma(Ima_histograma_acumulado,histo_acumulado);

    ima_histo = crear_imagen(Ima_histograma,256,256);
    ima_histo_acum = crear_imagen(Ima_histograma_acumulado,256,256);
    ima_humbral = crear_imagen_humbral(humbral,ima.rows,ima.cols,imagen_matrix);

    imshow("Imagen",ima);
    imshow("Histograma",ima_histo);
    imshow("Histograma Acumulado",ima_histo_acum);
    imshow("Imagen humbral",ima_humbral);

    cvWaitKey(0);

    liberar_memoria(Ima_histograma,256);
    liberar_memoria(Ima_histograma_acumulado,256);
    liberar_memoria(imagen_matrix,ima.rows);
    free(histo);
    free(histo_acumulado);
    free(dis_pro);
    free(momento);

    return 0;
}

