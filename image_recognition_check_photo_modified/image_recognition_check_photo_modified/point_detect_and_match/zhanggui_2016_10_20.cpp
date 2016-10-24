//OpenCV 3.1 header
#include <opencv2\highgui.hpp>
#include <opencv2\opencv.hpp>//imread��cv::�ĺ���//C�Ŀⶼ��cv_��ͷ
#include <opencv2\xfeatures2d\nonfree.hpp>
//#include "opencv2\features2d.hpp"
#include <iostream>
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

//OpenCV 2.4.13 header
//#include <cv.h>
//#include "highgui/highgui.hpp"    
//#include "opencv2/nonfree/nonfree.hpp"    
//#include "opencv2/legacy/legacy.hpp"   
//#include "calib3d.hpp"
//#include <iostream>  
//
//using namespace cv;
//using namespace std;

void my_edge_detect(Mat src,Mat& dst)
{
	//----------------------------------------------------------------------------------  
	//  �����߽׵�canny�÷���ת�ɻҶ�ͼ�����룬��canny����󽫵õ��ı�Ե��Ϊ���룬����ԭͼ��Ч��ͼ�ϣ��õ���ɫ�ı�Եͼ  
	//----------------------------------------------------------------------------------  
	Mat edge, gray;

	// ��1��������srcͬ���ͺʹ�С�ľ���(dst)  
	dst.create(src.size(), src.type());

	// ��2����ԭͼ��ת��Ϊ�Ҷ�ͼ��  
	cvtColor(src, gray, CV_BGR2GRAY);

	// ��3������ʹ�� 5x5�ں�������
	blur(gray, edge, Size(2, 2));

	// ��4������Canny����  
	int g_cannyLowThreshold = 30;
	Canny(edge, edge, g_cannyLowThreshold, g_cannyLowThreshold*2, 3);

	//��5����g_dstImage�ڵ�����Ԫ������Ϊ0   
	dst = Scalar::all(0);

	//��6��ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��  
	src.copyTo(dst, edge);

	return;
}

int main(int argc, char *argv[])
{
	string pic_path = "F:\\my_git_reposity\\image_recognition_check_photo_modified\\image_recognition_check_photo_modified\\image_recognition_check_photo_modified\\point_detect_and_match\\zhanggui_pic";
	Mat image01 = imread(pic_path + "\\post.jpg", ImreadModes::IMREAD_COLOR);
	Mat image02 = imread(pic_path + "\\post1.jpg", ImreadModes::IMREAD_COLOR);
	Mat image1, image2;
	//image1 = image01.clone();
	//image2 = image02.clone();

	//LZM ʵ�飺�ñ�Ե�����ͼ���ԭͼ��������ʶ���ƥ��
	my_edge_detect(image01, image1);
	my_edge_detect(image02, image2);


	//��ȡ������    
	//SurfFeatureDetector surfDetector(4000);  //hessianThreshold,����������ֵ���������޶�������ĸ���   //OpenCV 2.4.13 
	Ptr<SURF> surfDetector = SurfFeatureDetector::create(4000);//OpenCV 3.1 
	vector<KeyPoint> keyPoint1, keyPoint2;
	//surfDetector.detect(image1, keyPoint1);//OpenCV 2.4.13 
	//surfDetector.detect(image2, keyPoint2);//OpenCV 2.4.13 
	surfDetector->detect(image1, keyPoint1);//OpenCV 3.1 
	surfDetector->detect(image2, keyPoint2);//OpenCV 3.1 

	//����������    
	drawKeypoints(image1, keyPoint1, image1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(image2, keyPoint2, image2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("KeyPoints of image1", image1);
	imshow("KeyPoints of image2", image2);


	Mat image3, image4;
	image3 = image1.clone();
	image4 = image2.clone();
	Ptr<SIFT> detector = SiftFeatureDetector::create();

	vector<KeyPoint> keyPoint3, keyPoint4;

	detector->detect(image3, keyPoint3);
	detector->detect(image4, keyPoint4);

	drawKeypoints(image3, keyPoint3, image3, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(image4, keyPoint4, image4, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("KeyPoints of image3", image3);
	imshow("KeyPoints of image4", image4);



	////������������Ϊ�±ߵ�������ƥ����׼��    
	////SurfDescriptorExtractor SurfDescriptor;//OpenCV 2.4.13 
	//Ptr<SURF> SurfDescriptor = SurfDescriptorExtractor::create();//OpenCV 3.1 
	//Mat imageDesc1, imageDesc2;
	////SurfDescriptor.compute(image1, keyPoint1, imageDesc1);//OpenCV 2.4.13 
	////SurfDescriptor.compute(image2, keyPoint2, imageDesc2);//OpenCV 2.4.13 
	//SurfDescriptor->compute(image1, keyPoint1, imageDesc1);//OpenCV 3.1 
	//SurfDescriptor->compute(image2, keyPoint2, imageDesc2);//OpenCV 3.1 
	////������ƥ�䲢��ʾƥ����    
	////	BruteForceMatcher<L2<float>> matcher;    
	//FlannBasedMatcher matcher;
	//vector<DMatch > matchePoints;
	//matcher.match(imageDesc1, imageDesc2, matchePoints, Mat());


	//vector<vector<DMatch >> MyPoints;
	//matcher.knnMatch(imageDesc1, imageDesc2, MyPoints, 2, Mat());
	//vector<DMatch> MyGoodPoints;
	//for (unsigned int i = 0; i<MyPoints.size(); i++)
	//{
	//	if (MyPoints[i][0].distance / MyPoints[i][1].distance<(1.f / 1.5f))
	//	{
	//		MyGoodPoints.push_back(MyPoints[i][0]);
	//	}
	//}
	//Mat imageOutput;
	//drawMatches(image01, keyPoint1, image02, keyPoint2, MyGoodPoints, imageOutput, Scalar::all(-1),
	//	Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//imshow("Mathch Points", imageOutput);

	//vector<Point2f> src;
	//vector<Point2f> des;
	//for (int i = 0; i < MyGoodPoints.size(); i++)
	//{
	//	src.push_back(keyPoint1[MyGoodPoints[i].queryIdx].pt);
	//	des.push_back(keyPoint2[MyGoodPoints[i].trainIdx].pt);
	//}
	/*	Mat result=findHomography(des, src, 0, 3, noArray());
	//	uchar* R = result.data;
	for (int i = 0; i < 3; i++)
	{
	for (int j = 0; j < 3; j++)
	{
	cout << (float)result.data[i*3+j]<< "   ";
	}
	cout << endl;
	}
	*/



	//��ȡǿ������  
	/*	double minMatch = 1;
	double maxMatch = 0;
	for (unsigned int i = 0; i<matchePoints.size(); i++)
	{
	//ƥ��ֵ�����Сֵ��ȡ
	minMatch = minMatch > matchePoints[i].distance ? matchePoints[i].distance : minMatch;
	maxMatch = maxMatch < matchePoints[i].distance ? matchePoints[i].distance : maxMatch;
	}
	//�����Сֵ���
	cout << "���ƥ��ֵ�ǣ� " << minMatch << endl;
	cout << "���ƥ��ֵ�ǣ� " << maxMatch << endl;

	//��ȡ����ǰ�ߵļ�������ƥ����
	vector<DMatch> goodMatchePoints;
	for (unsigned int i = 0; i<matchePoints.size(); i++)
	{
	if (matchePoints[i].distance < minMatch + (maxMatch - minMatch) / 2)
	{
	goodMatchePoints.push_back(matchePoints[i]);
	}
	}

	//��������ƥ���
	Mat imageOutput;
	drawMatches(image01, keyPoint1, image02, keyPoint2, goodMatchePoints, imageOutput, Scalar::all(-1),
	Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("Mathch Points", imageOutput);

	//ƥ�����������
	float pointbuff;
	for (unsigned int i = 0; i < matchePoints.size(); i++)
	{
	for (unsigned int j = i+1; j < matchePoints.size(); j++)
	{
	if (matchePoints[i].distance < matchePoints[j].distance)
	{
	pointbuff = matchePoints[i].distance;
	matchePoints[i].distance = matchePoints[j].distance;
	matchePoints[j].distance = pointbuff;
	}
	}
	}

	int num;
	vector<DMatch> PointsRank;
	Mat GoodPointsImage;
	while (1)
	{
	cout << "��Ҫ���Ƶ����ƥ�������";
	cin >> num;
	PointsRank.clear();
	for (int i = 0; i < num; i++)
	{
	PointsRank.push_back(matchePoints[i]);
	}
	drawMatches(image01, keyPoint1, image02, keyPoint2, PointsRank, GoodPointsImage, Scalar::all(-1),
	Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("myshow", GoodPointsImage);
	waitKey();
	destroyWindow("myshow");
	}
	*/


	waitKey();
	return 0;
}