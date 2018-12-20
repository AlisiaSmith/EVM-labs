#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc,char *argv[])
{ 
        clock_t time;
        clock_t time_input;
        clock_t time_transformations;
        clock_t time_show;
        
        clock_t counter_input = 0;
        clock_t counter_transformations = 0;
        clock_t counter_show = 0;
        double counter = 0;

    CvCapture *capture = cvCreateCameraCapture(0);
    if (!capture) return 0;     
        time = clock();
        
    while(1)
   {
            time_input = clock();
        IplImage *frame = cvQueryFrame(capture);
                time_input = clock() - time_input;
                counter_input+=time_input;


        if(!frame) break;

                IplImage *image = cvCloneImage(frame);

                time_transformations = clock();
                //сглаживание
               cvSmooth(frame,image,CV_BLUR,10,10);

                //обнуление синего и красного  каналов
                //for (int y=0; y<image->height; y++) 
                //{
                //        uchar *ptr = (uchar*)(image->imageData + y*image->widthStep);
                //        for (int x=0; x<image->width; x++) 
                //        {
                //                ptr[3*x] = 0;           // синий
                //                //ptr[3*x+1] = 0;       // зеленый
                //                ptr[3*x+2] = 0; // красный
                //        }
                //}

                //уменьшение изображения по ширине и высоте
                image->width = (image->width * 2) / 3;
                image->height = (image->height * 2) / 3;
                time_transformations = clock() - time_transformations;
                counter_transformations+=time_transformations;

                time_show = clock();
                cvShowImage("frames",image);
                time_show = clock() - time_show;
                counter_show+=time_show;

        //cvShowImage("test", frame);

                counter++;

        char c = cvWaitKey(33);
        if(c == 27) break;
    }
        time = clock() - time;

        double frame_per_second = counter / (((double)time/CLOCKS_PER_SEC));
        double time_input0 = ((double)counter_input/CLOCKS_PER_SEC) / counter;
        double time_transformations0 = ((double)counter_transformations/CLOCKS_PER_SEC) / counter;
        double time_show0 = ((double)counter_show/CLOCKS_PER_SEC) / counter;
        double full_time = time_input0 + time_transformations0 + time_show0;

        cout << "Frame per second: " << frame_per_second << endl;
        cout << "Time for input: " << time_input0 / full_time * 100 << "%" << endl;
        cout << "Time for transformations: " << time_transformations0 / full_time * 100 << "%" << endl;
        cout << "Time for show: " << time_show0 / full_time * 100 << "%" << endl;

    cvReleaseCapture(&capture);
    cvDestroyWindow("frames");
}

