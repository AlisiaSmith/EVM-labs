#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <time.h>
#include <stdio.h>
#include <fstream>

using namespace std;
 using namespace cv;
//Самым популярным методом выделения границ является детектор границ Кенни.

int main(int argc,char *argv[])
{ 

cout << "hello" << endl;

int y;int x;
int counter=0;
IplImage *frame;
IplImage *image;
IplImage *dst = 0;
IplImage *dst2= 0;
struct timespec point1, point2, point3,point4,point5,point6;

cout << "world" << endl;

 namedWindow("test", WINDOW_NORMAL);
// namedWindow("image", WINDOW_NORMAL);
// namedWindow("image2", WINDOW_NORMAL);

//Создается  поток  ввода  видеоданных  с  первой  камеры  (нумерация начинается  с  нуля).Результат 
//операции –указатель  на  дескриптор обрабатываемого потока видеоданных.
CvCapture *capture = cvCreateCameraCapture(0);
if (!capture) return 0;


 clock_gettime(CLOCK_MONOTONIC_RAW, &point1);
while(1) {

 clock_gettime(CLOCK_MONOTONIC_RAW, &point2);
//указатель на дескриптор растрового изображения, которое будет содержать один кадр из потока видеоданных
    frame = cvQueryFrame(capture);
    if(!frame) break;

cout << "lovely" << endl;

clock_gettime(CLOCK_MONOTONIC_RAW, &point3);
    image = cvCloneImage(frame);

    // для хранения картинки в градациях серого
   image= cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
   dst = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );

    
    // преобразуем в градации серого
    cvCvtColor(frame,image, CV_RGB2GRAY);

    /// получим бинарное изображение
   dst2 = cvCreateImage( cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
    //В OpenCV, детектор границ Кенни реализуется функцией cvCanny(), которая обрабатывает только одноканальные изображения.
    cvCanny(image, dst2, 50, 200);

  cvSub(image, dst2, dst2);//вычетаем контуры из изображения

    // получаем границы
   cvCanny(image, dst, 20, 100, 3);
   clock_gettime(CLOCK_MONOTONIC_RAW, &point4);
   
//cvShowImage("test",image);   Текущий  кадр выводится  в  окно  с  именем  test(при  первом  вызове создается окно с таким именем)
cvShowImage("image",dst2);
     clock_gettime(CLOCK_MONOTONIC_RAW, &point5);
//cvShowImage("image", dst);
counter++;

cout << "friend" << endl;

char c = cvWaitKey(33);
if(c == 27) break;
}
 clock_gettime(CLOCK_MONOTONIC_RAW, &point6);

//удаление потока ввода видеоданных, освобождение  занятых  им  ресурсов, а  также  удаление  окна,  в  которое 
//выводились кадры потока видеоданных

cout << "!" << endl;

cvSaveImage("Image3.png", dst2,0);
cvSaveImage("Image.png", image,0);
cvSaveImage("Image2.png", dst,0);
cvReleaseCapture(&capture);
cvDestroyWindow("test");
cvDestroyWindow("image2");
//cvDestroyWindow("image");

std::ofstream fout("output.txt");
fout <<(point3.tv_sec-point2.tv_sec)<<"  "<<0.000000001*(point3.tv_nsec-point2.tv_nsec)<<endl;  //захват кадра
fout <<(point4.tv_sec-point3.tv_sec)<<"  "<<0.000000001*(point4.tv_nsec-point3.tv_nsec)<<endl;   //обработка кадра
fout <<(point5.tv_sec-point4.tv_sec)<<"  "<<0.000000001*(point5.tv_nsec-point4.tv_nsec)<<endl;   //вывод кадра 
fout <<(point5.tv_sec-point2.tv_sec)<<"  "<<0.000000001*(point5.tv_nsec-point2.tv_nsec)<<endl;  // общее время

 fout.close();
}

