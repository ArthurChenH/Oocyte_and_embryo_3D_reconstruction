This code is used to do the 3-D reconstruction of Oocytes and embryos. 

The origin data of oocytes and embryos should be selected and adjucted manually with the tools applied by the code. 

The RoI images of rotated oocytes and embryos can be extrated using the kcf.cpp. 

The extrated images can be processed by the edge_dectection_img.cpp to calculate the contours of target cells.

Using the 2csv.cpp, all the contours could be collected into the demo.csv.

We use matlab and point cloud library to reconstruct the 3D cloud point map of the target oocytes or embryos.

OpenCV 3, 
PCL 1.12.0, 
Matlab 2019, 
Visual studio 2017
were used in this program.

This work related to the research: 

_Zhuo Chen, Chenhao Bai, Fengyu Liu, Qiang Huang, Toshio Fukuda, Tatsuo Arai, Xiaoming Liu, "Lab on an End: Micromanipulation Using Acoustohydrodynamic Pillar Array as End-Effector"_

Code authors: Zhuo Chen.
