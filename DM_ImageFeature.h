#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
#include <cstring>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/core/types.hpp>

using namespace cv::xfeatures2d;
//using namespace cv;
//using namespace std;



//=======================================================================================================================================
//�������ƣ�����SIFT��ģ��ƥ�亯��
//��������˵����
//  @tempImg_��ģ��ͼƬ
//  @trainImg_�������ͼƬ
//	@roiVertices��ģ��ͼƬ���ĸ������Ӧ��trainImg��λ�ã�0-���ϣ�1-���ϣ�2-���£�3-���µ�
//  @grabPoints:�����ͼƬ��
//  @templateGrabP:ģ���ץȡλ��
//	@imgScale:Ϊ�����ƥ��������ٶȣ����Ե���ͼ��Ľ�άϵ����ϵ��Խ������Խ�죬����ƥ��ľ���Ҳ��Խ��
//	@tempfeatures:ģ��������ĸ�����Ĭ��Ϊ0��ȫ������
//	@trainfeatures��:���ͼƬ������ĸ�����Ĭ��Ϊ0��ȫ������
//����ֵ��������ɷ���true������ʧ�ܷ���fasle��
//����˵����
//	�ٸ�ƥ��Ψһ��ȱ��������Ƚ�����������һ������ƥ���㷨���߱���ת�����ԣ��߶Ȳ����ԣ�λ�Ʋ����Ե����õ�����
//  �ڱ��㷨���ǵ�ͼ�����б��ϵ�������������4�����㲢��һ���Ǿ��Σ����������Σ�����Ƕ�άƽ��仯����Ҫ����minAreaRect���������Ӿ���
//=======================================================================================================================================
bool DM_matchTemplateFast_SIFT(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<std::vector<cv::Point2d>> &roiVertices, std::vector<cv::Point2d> &grabPoints,
                               cv::Point2d templateGrabP = cv::Point2d(-1,-1),double imgScale = 1.0,  int tempfeatures = 0, int trainfeatures = 0);

//=======================================================================================================================================
//�������ƣ�����SURF��ģ��ƥ�亯��
//��������˵����
//  @tempImg_��ģ��ͼƬ
//  @trainImg_�������ͼƬ
//	@roiVertices��ģ��ͼƬ���ĸ������Ӧ��trainImg��λ�ã�0-���ϣ�1-���ϣ�2-���£�3-���µ�
//	@imgScale:Ϊ�����ƥ��������ٶȣ����Ե���ͼ��Ľ�άϵ����ϵ��Խ������Խ�죬����ƥ��ľ���Ҳ��Խ��
//	@tempHessianThreshold:ģ���������Hessian��ֵ��ֵԽ��������ԽС
//	@trainHessianThreshold:���ͼƬ�������Hessian��ֵ��ֵԽ��������ԽС
//����ֵ��������ɷ���true������ʧ�ܷ���fasle��
//����˵����
//	�ٸ�ƥ��Ψһ��ȱ��������Ƚ�����������һ������ƥ���㷨���߱���ת�����ԣ��߶Ȳ����ԣ�λ�Ʋ����Ե����õ�����
//  �ڱ��㷨���ǵ�ͼ�����б��ϵ�������������4�����㲢��һ���Ǿ��Σ����������Σ�����Ƕ�άƽ��仯����Ҫ����minAreaRect���������Ӿ���
//=======================================================================================================================================
bool DM_matchTemplateFast_SURF(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<cv::Point2d> &roiVertices, double imgScale = 2.0,
	double tempHessianThreshold = 500, double trainHessianThreshold = 500);


//=======================================================================================================================================
//�������ƣ�����opencvģ��ƥ�亯��
//��������˵����
//  @tempImg_��ģ��ͼƬ
//  @trainImg_�������ͼƬ
//	@pos: x,y�ֱ��ʾƥ����λ�ã�z��ʾƥ���ĵ÷�ϵ��
//	@imgScale:Ϊ�����ƥ��������ٶȣ����Ե���ͼ��Ľ�άϵ����ϵ��Խ������Խ�죬����ƥ��ľ���Ҳ��Խ��
//	@maskImg��ƥ����Ĥ
//����ֵ��������ɷ���true������ʧ�ܷ���fasle��
//����˵����
//	�ٸ�ƥ���㷨ֻʹ���ڹ����ж�λ��ͼƬֻ������ͨ��ƽͨ״̬��ʵ�ø��㷨������ڸ������£�ƥ���㷨�ľ��ȡ�Ч�ʾ�Զ����������ƥ�䣬��
//=======================================================================================================================================

bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, cv::Point3d &pos, double imgScale = 2, cv::Mat maskImg = cv::Mat());

//=======================================================================================================================================
//�������ƣ�����opencvģ��ƥ�亯��
//��������˵����
//  @tempImg_��ģ��ͼƬ
//  @trainImg_�������ͼƬ
//	@roiVertices��ģ��ͼƬ���ĸ������Ӧ��trainImg��λ�ã�0-���ϣ�1-���ϣ�2-���£�3-���µ�
//	@imgScale:Ϊ�����ƥ��������ٶȣ����Ե���ͼ��Ľ�άϵ����ϵ��Խ������Խ�죬����ƥ��ľ���Ҳ��Խ��
//	@startAngle:ģ��������ĸ�������λ���ȣ���Ĭ��Ϊ0������ת
//	@endtAngle��:���ͼƬ������ĸ�������λ���ȣ���Ĭ��Ϊ0������ת
//	@AnglePrecision���Ƕ�ϸ�־��ȣ�Ĭ��0.0087���ȣ�ת���ɽǶȾ���0.5��
//����ֵ��������ɷ���true������ʧ�ܷ���fasle��
//����˵����
//	�ٸ�ƥ���㷨�����������ת��������������ʷǳ��ͣ�������ʹ�á����ģ��ͱ���ͼ��֮��ֻ��ƽ�ƹ�ϵ���ø��㷨�����������ƥ����Ӿ�׼��Ч�ʸ��ߡ����ֻ��ƽ����
//    ֱ�ӵ���bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, cv::Point3d &pos, double imgScale = 2,cv::Mat maskImg = cv::Mat());
//=======================================================================================================================================

bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<cv::Point2d> &roiVertices,double imgScale = 2,
							  double startAngle = 0, double endtAngle = 0,double anglePrecision = 0.00877);