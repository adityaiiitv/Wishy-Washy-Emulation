/*	AUTHOR:	ADITYA PRAKASH	*/
// PLEASE READ THE readme FILE BEFORE RUNNING THE CODE
#include <opencv2/objdetect/objdetect.hpp>		// NECESSARY HEADER FILES
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
 
using namespace std;
using namespace cv;		// BETTER THAN USING cv:: EVERYTIME
 
int main()
{
	VideoCapture cap(0);	// START CAPTURING FROM THE DEFAULT CAMERA
	if(!cap.isOpened())		// IF NOT OPENED
	{
		return -1;
	}
	Mat frame;			// OBJECT OF Mat TO CAPTURE EVERY FRAME
	cap >> frame;		// CAPTURE THE FRAME
	int rows1=frame.rows;	// ROWS OF THE FRAME
	int cols1=frame.cols;	// COLUMNS OF THE FRAME
	Mat img(rows1,cols1,CV_8UC3,Scalar(0,0,0));	// CREATE A NEW BLACK IMAGE WITH THE SAME NUMBER OF ROWS AND COLUMNS
	cols1=cols1*3;			// DUE TO THREE COMPONENTS, TAKE THRICE THE AMOUNT OF COLUMNS
	int prev[rows1][cols1];	// CREATE A MATRIX TO KEEP TRACK
	long double sum=0;		// TO STORE THE AVERAGE INTENSTY TO SET THE THRESHOLD VALUE FOR CHANGE IN INTENSITY
	for(int i=0;i<rows1;i++)
	{
		for(int j=0;j<cols1;j++)
		{
			sum=sum+int(frame.at<uchar>(i,j));	// SUMMATION TAKEN OVER ALL THE PIXELS
		}
	}
	sum=sum/(rows1*cols1);	// AVERAGE TAKEN
//	cout<<sum;
	for(int i=0;i<rows1;i++)	// FOR EVERY PIXEL
	{
		for(int j=0;j<cols1;j++)
		{
			prev[i][j] = img.at<uchar>(i,j);	// prev[i][j] CONTAINS THE INTENSITY OF THE POINT i,j ON THE IMAGE
		}
	}
//	int thresh=(int(sum)*20)%256;	// UN-COMMENT TO USE A FUNCTION FOR SETTING THE VALUE OF thresh
//	if(thresh<=80)
//	{ thresh=80;
		int thresh=80;			// PREFERABLE THRESHOLD VALUE USED BY ME
//	}
//	cout<<thresh;
	int complete;
	while(1)				// INFINITE LOOP
	{
		complete=0;		// FLAG TO CHECK WHETHER GAME IS WON OR NOT
		cap >> frame;		// CAPTURE EVERY FRAME FROM THE WEBCAM
		flip(frame,frame,1);// TAKE MIRROR IMAGE OF EVERY FRAME

		for(int i=0;i<rows1;i++)	// CHECK CHANGE FOR EVERY PIXEL
		{
			for(int j=0;j<cols1;j++)
			{
				int intensity = frame.at<uchar>(i,j);	// GET INTENSITY AT POINT i,j
				double r = ((double) rand() / (RAND_MAX));	// CLEAN A PIXEL WITH PROBABILITY r TO UNEASE THE CLEANING
				if(r<1 && (prev[i][j]-intensity)>=thresh || (intensity-prev[i][j])>=thresh && prev[i][j]!=255)
				{	// CHECK THAT THE INTENSITY VARIES OUTSIDE THE THRESHOLD
					prev[i][j] = 255;			// SET THE PREV COLOUR TO WHITE
					img.at<uchar>(i,j)= 255;	// SET IMAGE TO WHITE COLOUR
				}

			}
		 
		}
		for(int i=0;i<rows1;i++)		// CHECK FOR EVERY PIXEL
		{
			for(int j=0;j<cols1;j++)
			{
				if(prev[i][j]==255)
				{
					complete++;			// WHETHER IT IS WHITE OR NOT AND KEEP A COUNT
				}
			}
		}

		imshow("window", img);			// KEEP DISPLAYING THE IMAGE
		imshow("webcam", frame);
		if(waitKey(30) >= 0 || complete>(rows1*cols1-2000))
		{
			break;	// RUN FOR INFINITE TIME OR TILL (N-2000) PIXELS ARE LEFT WHICH ARE NOT WHITE. N-2000 IS A VALUE SET BY ME.
		}
	}
	if(complete>(rows1*cols1-2000))
	{
		cout<<"\n You win. Hip hip Hurray.!\n";
	}
	return 0;
}
/*	END OF PROGRAM	*/
