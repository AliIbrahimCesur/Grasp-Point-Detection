#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2){
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

	Mat Object;
	Mat edges2; 


	Object = imread(argv[1], CV_LOAD_IMAGE_COLOR);	//Read the file

    if(! Object.data ){                              // Check for invalid input
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
//  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
	imshow( "Display1 Object", Object);
	
    cvtColor(Object, edges2, COLOR_BGR2GRAY);
    GaussianBlur(edges2, edges2, Size(7,7), 1.5, 1.5);
    Canny(edges2, edges2, 0, 30, 3);

	imshow( "Display Object", edges2);

	Mat	bub;
	int ar1[100] = {};
	int k=0;
	int t=0;
	int temp=0;
	int is=0;
	int ss=0;
	int a=0;
	int b=0;

	int tot_a1=0;		//cismin etrafına cizilecek dikdörtgenin sınırları
	int tot_b1=0;
	int count_ab1=0;

	int tot_a2=0;
	int tot_b2=0;
	int count_ab2=0;

	bub=edges2.clone(); // bub sınırları cizdigimiz image x ekseni

	for(int i=0; i<edges2.rows; i++){
		for(int j=0; j<edges2.cols; j++){
			bub.at<uchar>(i, j)=255;	
		}
	}

	for(int i=0; i<edges2.rows; i++){
		for(int j=0; j<edges2.cols; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar1[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar1[0];
				b=ar1[k-1];
				bub.at<uchar>(i, a)=0;
				bub.at<uchar>(i, b)=0;
				tot_a1=tot_a1+a;
				tot_b1=tot_b1+b;
				count_ab1++;
			}
			for(t=0; t<k; t++){
				ar1[t] = 0;
			}
		}
		k=0;
	}	

	int bound_x1=tot_a1/count_ab1;
	int bound_x2=tot_b1/count_ab1;

//2.kısım							sınırları cizdigimiz image y ekseni
	for(int i=0; i<edges2.rows; i++){
		for(int j=0; j<edges2.cols; j++){
			if( edges2.at<uchar>(j, i)==255){
				ar1[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar1[0];
				b=ar1[k-1];
				bub.at<uchar>(a, i)=0;
				bub.at<uchar>(b, i)=0;
				tot_a2=tot_a2+a;
				tot_b2=tot_b2+b;
				count_ab2++;
			}
			for(t=0; t<k; t++){
				ar1[t] = 0;
			}
		}
		k=0;
	}		

	int bound_x3=tot_a2/count_ab2;
	int bound_x4=tot_b2/count_ab2;

// create a rectangle
	Point pt1(tot_b1, tot_a2);
	Point pt2(tot_a1, tot_b2);
	rectangle(bub,pt1,pt2,Scalar(0, 255, 0));
	cout<<"1: "<<bound_x1 <<endl;	
	cout<<"2: "<<bound_x3 <<endl;


	Mat bub2=bub.clone();		//bub 2 siyah dolgu

	for(int i=0; i<edges2.rows; i++){
		for(int j=0; j<edges2.cols; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar1[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar1[0];
				b=ar1[k-1];
				for (int is=a; is<=b; is++){
					bub2.at<uchar>(i,is)=0;
				}
			}
			for(t=0; t<k; t++){
				ar1[t] = 0;
			}
		}
		k=0;
	}	

	int sumi=0;
	int sumj=0;
	int count=0;
	int orgin_x=0;
	int orgin_y=0;

	for(int i=0; i<bub2.rows; i++){
		for(int j=0; j<bub2.cols; j++){
			if( bub2.at<uchar>(i, j)==0){
				sumi=sumi+i;
				sumj=sumj+j;
				count++;
			}	
		}
	}

	orgin_x=(int)(sumj/count-1);
	orgin_y=(int)(sumi/count-1);

	Mat bub_eksen=bub.clone();
	int ar2[100] = {};
	k=0;

	for( int i=0; i<bub.rows; i++){
		bub_eksen.at<uchar>(i,orgin_x)=0;
	}
	for( int j=0; j<bub.cols; j++){
		bub_eksen.at<uchar>(orgin_y,j)=0;
	}

	for(int j=0; j<bub.rows; j++){
		if( bub.at<uchar>(orgin_x, j)==0){
			ar2[k]=j;
			k++;
		}
	}
	int pix_distance = ar2[k-1]-ar2[0]; 	
	double Realpix_size=0.073;
	double Real_distance = Realpix_size*pix_distance; 



//3.kısım

	Mat bub3=edges2.clone(); //yarım eksen 2.bölge

	for(int i=0; i<edges2.rows; i++){
		for(int j=0; j<edges2.cols; j++){
			bub3.at<uchar>(i, j)=255;	
		}
	}

	k=0;
	for(int i=0; i<orgin_y; i++){
		for(int j=0; j<orgin_x; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar1[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar1[0];
				b=ar1[k-1];
				bub3.at<uchar>(i, a)=0;
				bub3.at<uchar>(i, b)=0;
			}
			for(t=0; t<k; t++){
				ar1[t] = 0;
			}
		}
		k=0;
	}

	k=0;
	for(int i=orgin_y; i<edges2.rows; i++){   //yarım eksen 4.bölge
		for(int j=orgin_x; j<edges2.cols; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar1[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar1[0];
				b=ar1[k-1];
				bub3.at<uchar>(i, a)=0;
				bub3.at<uchar>(i, b)=0;
			}
			for(t=0; t<k; t++){
				ar1[t] = 0;
			}
		}
		k=0;
	}

	k=0;
	for(int i=orgin_y; i<edges2.rows; i++){ //3.bölge
		for(int j=0; j<orgin_x; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar1[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar1[0];
				b=ar1[k-1];
				bub3.at<uchar>(i, a)=0;
				bub3.at<uchar>(i, b)=0;
			}
			for(t=0; t<k; t++){
				ar1[t] = 0;
			}
		}
		k=0;
	}

	k=0;

	for(int i=0; i<orgin_y; i++){		//1.bölge
		for(int j=orgin_x; j<edges2.cols; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar1[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar1[0];
				b=ar1[k-1];
				bub3.at<uchar>(i, a)=0;
				bub3.at<uchar>(i, b)=0;
			}
			for(t=0; t<k; t++){
				ar1[t] = 0;
			}
		}
		k=0;
	}

	k=0;
//3.kısımson
//4.kısım doldurma

	Mat bub4=bub3.clone(); //yarım eksen 2.bölge
	int	ar5[100]={};
	k=0;

	for(int i=0; i<orgin_y; i++){	//1
		for(int j=0; j<orgin_x; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar5[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar5[0];
				b=ar5[k-1];
				for (int is=a; is<=b; is++){
					bub4.at<uchar>(i,is)=0;
				}
			}
			for(t=0; t<k; t++){
				ar5[t] = 0;
			}
		}
		k=0;
	}

	for(int i=orgin_y; i<edges2.rows; i++){	//2
		for(int j=0; j<orgin_x; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar5[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar5[0];
				b=ar5[k-1];
				for (int is=a; is<=b; is++){
					bub4.at<uchar>(i,is)=0;
				}
			}
			for(t=0; t<k; t++){
				ar5[t] = 0;
			}
		}
		k=0;
	}

	for(int i=0; i<orgin_y; i++){	//3
		for(int j=orgin_x; j<edges2.cols; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar5[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar5[0];
				b=ar5[k-1];
				for (int is=a; is<=b; is++){
					bub4.at<uchar>(i,is)=0;
				}
			}
			for(t=0; t<k; t++){
				ar5[t] = 0;
			}
		}
		k=0;
	}

	for(int i=orgin_y; i<edges2.rows; i++){	//4
		for(int j=orgin_x; j<edges2.cols; j++){
			if( edges2.at<uchar>(i, j)==255){
				ar5[k]=j;
				k++;
			}			
			else{			
			}				
		}
		if( k>0 ){
			for(int es=0; es<k; es++){
				a=ar5[0];
				b=ar5[k-1];
				for (int is=a; is<=b; is++){
					bub4.at<uchar>(i,is)=0;
				}
			}
			for(t=0; t<k; t++){
				ar5[t] = 0;
			}
		}
		k=0;
	}

//6.kısımson
	cout<<"orgin_x: "<<orgin_x <<"\torgin_y: "<< orgin_y <<endl;
	cout<<"Distance in pixels: "<<pix_distance <<endl;	
	cout<<"Actual distance in cm: "<<Real_distance <<endl;	

	if(Real_distance>20){
		cout<<"Object can not catch!"<<endl;
	}
	else{
		cout<<"Object can catch"<<endl;	
	}

	imshow("bub", bub);
	imshow("bub2", bub2);
	imshow("bub3", bub3);
	imshow("bub4", bub4);
	imshow("bub_eksen", bub_eksen);
                                    
    waitKey(0);		 

    return 0;
}





