#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <time.h>

double calc(struct timespec start, struct timespec end) {
        return end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec -
start.tv_nsec);
}
int main(int argc, char *argv[]) {
        CvCapture *capture = cvCreateCameraCapture(0);
        if (!capture) {
	
                printf("No camera found.\n");
                return 0;
        }
        struct timespec start, cycle_start, cycle_end, proc_start,
proc_end, in_start, in_end, _start, _end;
        int frames = 0, y = 0, x = 0;
        double time = 0, timePas, fps, tpf, frameT;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        while (1) {

     printf("No camera found.\n");
                return 0;
        }
        struct timespec start, cycle_start, cycle_end, proc_start,
proc_end, in_start, in_end, _start, _end;
        int frames = 0, y = 0, x = 0;
        double time = 0, timePas, fps, tpf, frameT;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        while (1) {
                clock_gettime(CLOCK_MONOTONIC_RAW, &cycle_start);
                clock_gettime(CLOCK_MONOTONIC_RAW, &in_start);
                IplImage *frame = cvQueryFrame(capture);
                clock_gettime(CLOCK_MONOTONIC_RAW, &in_end);
                if (!frame) {
                        printf("No frame.\n");
                        break;
                        clock_gettime(CLOCK_MONOTONIC_RAW, &cycle_end);
                }
                clock_gettime(CLOCK_MONOTONIC_RAW, &proc_start);

  clock_gettime(CLOCK_MONOTONIC_RAW, &in_start);
                IplImage *frame = cvQueryFrame(capture);
                clock_gettime(CLOCK_MONOTONIC_RAW, &in_end);
                if (!frame) {
                        printf("No frame.\n");
                        break;
                        clock_gettime(CLOCK_MONOTONIC_RAW, &cycle_end);
                }
                clock_gettime(CLOCK_MONOTONIC_RAW, &proc_start);
                for (y = 0; y + 1 < frame->height; y += 2) {
                        unsigned char *ptr1 = (unsigned char*)(frame->imageData$
                                y * frame->widthStep);
                        unsigned char *ptr2 = (unsigned char*)(frame->imageData$
                                ((y + 1) * frame->widthStep));
                        for (x = 0; x + 1 < frame->width; x+=2) {
                                ptr1[3 * x] = 0;
                                ptr1[3 * x + 1] = 0;
                                ptr1[3 * x + 2] = 0;
                                ptr2[3 * x + 3] = 0;

   unsigned char *ptr1 = (unsigned char*)(frame->imageData$
                                y * frame->widthStep);
                        unsigned char *ptr2 = (unsigned char*)(frame->imageData$
                                ((y + 1) * frame->widthStep));
                        for (x = 0; x + 1 < frame->width; x+=2) {
                                ptr1[3 * x] = 0;
                                ptr1[3 * x + 1] = 0;
                                ptr1[3 * x + 2] = 0;
                                ptr2[3 * x + 3] = 0;
                                ptr2[3 * x + 4] = 0;
                                ptr2[3 * x + 5] = 0;
                        }
                }
                clock_gettime(CLOCK_MONOTONIC_RAW, &proc_end);
                clock_gettime(CLOCK_MONOTONIC_RAW, &_start);
                cvShowImage("test", frame);
                clock_gettime(CLOCK_MONOTONIC_RAW, &_end);
                clock_gettime(CLOCK_MONOTONIC_RAW, &cycle_end);

  ptr2[3 * x + 5] = 0;
                        }
                }
                clock_gettime(CLOCK_MONOTONIC_RAW, &proc_end);
                clock_gettime(CLOCK_MONOTONIC_RAW, &_start);
                cvShowImage("test", frame);
                clock_gettime(CLOCK_MONOTONIC_RAW, &_end);
                clock_gettime(CLOCK_MONOTONIC_RAW, &cycle_end);

                time += calc(cycle_start, cycle_end);
                frames++;

                char c = cvWaitKey(33);
                if (c == 27) {
                        printf("ESC pressed.\n");
                        break;
                }
        }
        cvReleaseCapture(&capture);

  frames++;

                char c = cvWaitKey(33);
                if (c == 27) {
                        printf("ESC pressed.\n");
                        break;
                }
        }
        cvReleaseCapture(&capture);
        cvDestroyWindow("test");
        printf("Input time: %f.\n", calc(in_start, in_end));
        printf("Processing time: %f.\n", calc(proc_start, proc_end));
        tpf = time / frames;
        printf("Average frame time: %f.\n", tpf);
        printf("Number of frames: %d\n", frames);
        timePas = calc(start, cycle_end);
        fps = frames / timePas;
        printf("Frames per second: %f.\n", fps);
        printf("Time: %f.\n", timePas);

   printf("Input time: %f.\n", calc(in_start, in_end));
        printf("Processing time: %f.\n", calc(proc_start, proc_end));
        tpf = time / frames;
        printf("Average frame time: %f.\n", tpf);
        printf("Number of frames: %d\n", frames);
        timePas = calc(start, cycle_end);
        fps = frames / timePas;
        printf("Frames per second: %f.\n", fps);
        printf("Time: %f.\n", timePas);
        return 0;
}
