#include <iostream>
#include <vector>
#include <fstream>       //提供文件头文件
#include <algorithm>
#include <stdlib.h>//C++输出精度控制需要
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <opencv2/videoio/videoio.hpp>
#include <atomic> 
#include <mutex> 
#include <thread> 
#include <condition_variable>

using namespace cv;using namespace std;
float PI = 3.1415926535897932384;
string fnm = "./11234/";
int frame_number=10;
ofstream file1("./11234/center.txt", ios::app);

Mat on_ThreshChange(Mat src, int num) {
	char mk;
	Mat mid, dst, rsz;		
	dst = src.clone();		
	cvtColor(dst, mid, COLOR_BGR2GRAY); // adjust the code to get proper contours
	//Ptr<CLAHE> clahe = createCLAHE(40,Size(8,8));
	//clahe->apply(mid, mid);
	//equalizeHist(mid, mid);
	rsz = mid;
	//rsz = mid(Rect(xx, yy, 260, 200));
	//GaussianBlur(rsz, rsz, Size(3, 3), 8, 1, 4);
	//Canny(rsz, rsz, 125, 350);
	//resize(rsz, rsz, Size(450, 200),0,0, INTER_NEAREST);

	//imshow("rsz", rsz);

	Mat binary_img, dst_img;
	//src_img = imread("test2.png", IMREAD_GRAYSCALE);
	threshold(rsz, binary_img, 80, 255, THRESH_BINARY);

	imshow("trs", binary_img);
	//imwrite("trs.bmp", binary_img);
//adjust the code to get proper contours
	//GaussianBlur(binary_img, binary_img, Size(11, 11), 8, 1, 4);
	//boxFilter(binary_img, binary_img,-1, Size(3, 3));
	//blur(binary_img, binary_img, Size(3, 3));
	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	//     
	/*Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	//     
	morphologyEx(binary_img, binary_img, MORPH_CLOSE, kernel, Point(-1, -1));
	//  
	kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	// 
	morphologyEx(binary_img, binary_img, MORPH_OPEN, kernel, Point(-1, -1));
	//   
	//imshow("open", dst_img);*/
	findContours(binary_img, contours, hireachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	//imshow("bf", binary_img);
	//imwrite("bf.bmp", binary_img);
	Mat result_img = rsz.clone();
	cvtColor(result_img, result_img, COLOR_GRAY2BGR);  
	int MinR = 10; int MaxR = 300;
	double radius = 1;
	for (int i = 0; i < hireachy.size(); i++)
	{
		
		double area = contourArea(contours[i]);

		cout << area << endl;
		
		if (area < 10) continue;
		if (area > 100) {
			RotatedRect rect = fitEllipse(contours[i]);
			double arc_length = arcLength(contours[i], true);
			radius = ((arc_length / (2 * PI)) + radius) / 1.4;
			if (radius < 5) continue;
			//circle(src, Point(rect.center.x + xx, rect.center.y + yy), radius, Scalar(0, 255, 0), 1, 8, 0);
			//circle(src, Point(rect.center.x, rect.center.y), 2, Scalar(0, 255, 0), -1, 8, 0);

			file1 << rect.center.x << "	" << rect.center.y << "	" << radius << endl;
			string fn = fnm + to_string(num) + ".txt";
			ofstream file2(fn, ios::app);
			vector<Point>::iterator it1;
			for (it1 = contours[i].begin(); it1 != contours[i].end(); it1++) {
				float xx = it1->x, yy = it1->y;
				file2 << i <<":"<< xx << "\t" << yy << endl;
				
			}
			file2.close();
			continue;
		}
		//if (area > 2000) continue;



		//float ratio = float(rect.size.width) / float(rect.size.height);
		//drawContours(src, contours, i, Scalar(0, 255, 0), 1, 8, hireachy,214783647,Point(xx,yy));
		//RotatedRect rect = fitEllipse(contours[i]);
		//circle(src, Point(rect.center.x + xx, rect.center.y + yy), 2, Scalar(0, 255, 0), -1, 8, 0);
		//cout << "contours:" << i << endl;
	}
	//waitKey();
	return src;
}


int main()
{
	//int contourthresh1, contourthresh2; 	
	string filename;
	bool const save_output_videofile = true;//	
	string out_videofile = "./1out_ld.avi"; //Entry!!!!!
	//Mat mode = imread("mode.png", IMREAD_GRAYSCALE);
	int num = 0;
	while (true)
	{
		num++;
		filename = fnm + to_string(num) + ".tif";
		//filename = "inner.tif";
		Mat img = imread(filename);
		on_ThreshChange(img, num);
		filename.clear();
		waitKey(0);
		if (num >= frame_number)
		break;
	}


	waitKey(27);

}


