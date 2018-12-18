#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <time.h>
#include <stdio.h>
#include <fstream>

using namespace std;
 using namespace cv;

int main(int argc,char *argv[])
{
int y;int x;
int counter=0;
IplImage *frame;
struct timespec point1, point2, point3,point4,point5,point6;

 namedWindow("test", WINDOW_NORMAL);

//Создается  поток  ввода  видеоданных  с  первой  камеры  (нумерация начинается  с  нуля). Результат
// операции  – указатель  на  дескриптор обрабатываемого потока видеоданных.
CvCapture *capture = cvCreateCameraCapture(0);
if (!capture) return 0;

 clock_gettime(CLOCK_MONOTONIC_RAW, &point1);
while(1) {
 clock_gettime(CLOCK_MONOTONIC_RAW, &point2);
//указатель на дескриптор растрового изображения, которое будет содержать один кадр из потока видеоданных
frame = cvQueryFrame(capture);
if(!frame) break;

clock_gettime(CLOCK_MONOTONIC_RAW, &point3);

 clock_gettime(CLOCK_MONOTONIC_RAW, &point4);
   
// Текущий  кадр выводится  в  окно  с  именем  test(при  первом  вызове создается окно с таким именем)
cvShowImage("image", frame); 
 clock_gettime(CLOCK_MONOTONIC_RAW, &point5);
counter++;
char c = cvWaitKey(33);
if(c == 27) break;
}
 clock_gettime(CLOCK_MONOTONIC_RAW, &point6);

//удаление потока ввода видеоданных, освобождение  занятых  им  ресурсов, а  также  удаление  окна,  в  которое выводились кадры потока видеоданных
cvSaveImage("Image.png", frame, 0);
cvReleaseCapture(&capture);
cvDestroyWindow("test");
cvDestroyWindow("image2");

std::ofstream fout("output.txt");
fout <<(point3.tv_sec-point2.tv_sec)<<"  "<<0.000000001*(point3.tv_nsec-point2.tv_nsec)<<endl;  //захват кадра
fout <<(point4.tv_sec-point3.tv_sec)<<" "<<0.000000001*(point4.tv_nsec-point3.tv_nsec)<<endl;   //обработка кадра
fout <<(point5.tv_sec-point4.tv_sec)<<"  "<<0.000000001*(point5.tv_nsec-point4.tv_nsec)<<endl;   //вывод кадра
fout <<(point5.tv_sec-point2.tv_sec)<<"  "<<0.000000001*(point5.tv_nsec-point2.tv_nsec)<<endl;  // общее время
 fout.close();
return 0;
}

