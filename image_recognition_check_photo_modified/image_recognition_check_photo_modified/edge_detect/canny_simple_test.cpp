//-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
//            ����������������������ͷ�ļ�  
//			from:http://blog.csdn.net/poem_qianmo/article/details/25560901?utm_source=tuicool&utm_medium=referral
//----------------------------------------------------------------------------------------------  
#include <opencv2/opencv.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  

//-----------------------------------�������ռ��������֡�---------------------------------------  
//            ����������������ʹ�õ������ռ�  
//-----------------------------------------------------------------------------------------------  
using namespace cv;
//-----------------------------------��main( )������--------------------------------------------  
//            ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//-----------------------------------------------------------------------------------------------  
int main()
{
	//����ԭʼͼ
	string pic_path = "F:\\my_git_reposity\\image_recognition_check_photo_modified\\image_recognition_check_photo_modified\\image_recognition_check_photo_modified\\edge_detect\\canny_simple_test_pic";
	Mat src = imread(pic_path + "\\5.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  
	Mat src1 = src.clone();

	//��ʾԭʼͼ   
	imshow("��ԭʼͼ��Canny��Ե���", src);

	//----------------------------------------------------------------------------------  
	//  һ����򵥵�canny�÷����õ�ԭͼ��ֱ���á�  
	//void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize = 3, bool L2gradient = false)
		//��һ��������InputArray���͵�image������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λͼ��
		//�ڶ���������OutputArray���͵�edges������ı�Եͼ����Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
		//������������double���͵�threshold1����һ���ͺ�����ֵ��
		//���ĸ�������double���͵�threshold2���ڶ����ͺ�����ֵ��
		//�����������int���͵�apertureSize����ʾӦ��Sobel���ӵĿ׾���С������Ĭ��ֵ3��
		//������������bool���͵�L2gradient��һ������ͼ���ݶȷ�ֵ�ı�ʶ����Ĭ��ֵfalse��
	//----------------------------------------------------------------------------------  
	Canny(src, src, 3, 9, 3);
	imshow("��Ч��ͼ��Canny��Ե���", src);


	//----------------------------------------------------------------------------------  
	//  �����߽׵�canny�÷���ת�ɻҶ�ͼ�����룬��canny����󽫵õ��ı�Ե��Ϊ���룬����ԭͼ��Ч��ͼ�ϣ��õ���ɫ�ı�Եͼ  
	//----------------------------------------------------------------------------------  
	Mat dst, edge, gray;

	// ��1��������srcͬ���ͺʹ�С�ľ���(dst)  
	dst.create(src1.size(), src1.type());

	// ��2����ԭͼ��ת��Ϊ�Ҷ�ͼ��  
	cvtColor(src1, gray, CV_BGR2GRAY);

	// ��3������ʹ�� 3x3�ں�������  
	blur(gray, edge, Size(3, 3));

	// ��4������Canny����  
	Canny(edge, edge, 3, 9, 3);

	//��5����g_dstImage�ڵ�����Ԫ������Ϊ0   
	dst = Scalar::all(0);

	//��6��ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��  
	src1.copyTo(dst, edge);

	//��7����ʾЧ��ͼ   
	imshow("��Ч��ͼ��Canny��Ե���2", dst);


	waitKey(0);

	return 0;
}