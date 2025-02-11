//
// Created by zhch on 2022/4/18.
//

#ifndef KCF_IMG2VIDEO_HPP
#define KCF_IMG2VIDEO_HPP
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <cstring>
#include <cstdio>
#include <fstream>       
#include <algorithm>
#include <stdlib.h>
#include <atomic>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;
using namespace cv;

class img2video {
public:
    Mat out;
    string path_save;
    void func();
    int para[3];
    int endcap();
    int iscol;
private:
    Mat img;
    int flag=1;
    VideoWriter writer;
    int isColor = 1;
    void start();

};


void img2video::start() {
    cout << "frame_width is " << para[1] << endl;
    cout << "frame_height is " << para[2] << endl;
    cout << "frame_fps is " << para[0] << endl;
    writer = VideoWriter(path_save, VideoWriter::fourcc('X', 'V', 'I', 'D'), para[0], Size(para[1], para[2]), iscol);
    namedWindow("image to video", 0);
}

void img2video::func(){
    if(flag==1){
        start();
        flag=0;
        cout<<"Output has been finished."<<endl;
    }

    img = out;//input
    if (!img.data)//judge
    {
        cout << "Could not load image file...\n" << endl;
    }
    imshow("image to video", img);

    writer.write(img);
}

int img2video::endcap() {
    return 1;
}
#endif //KCF_IMG2VIDEO_HPP
