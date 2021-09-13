#include "DM_ImageFeature.h"
#include <iostream>

#define DM_PI        3.1415926535897932384626433832795 //  PI
#define DM_PI_4 	 0.78539816339744828               //  PI/4     0.25PI     45°
#define DM_PI_2 	 1.5707963267948966                //  PI/2     0.5PI      90°
#define DM_3PI_4 	 2.3561944901923448                //  3PI/4    0.75PI     135°
#define DM_3PI_2 	 4.7123889803846897                //  3PI/2    1.5PI      270°
#define DM_2PI       6.283185307179586476925286766559  //  2PI                 360°
#define DM_180_PI 	 57.295779513082323   //  180/PI  弧度转角度  直接乘上去就行
#define DM_PI_180 	 0.017453292519943295    //  PI/180  角度转弧度  直接乘上去就行
#define DM_1_2PI 	 0.15915494309189535    //  1/2PI
#define DM_1_PI 	 0.31830988618379069    //  1/PI
#define DM_2_PI 	 0.63661977236758138    //  2/PI


#define DM_Dubeg_Mode

bool comperDmatch(const cv::DMatch &m1, const cv::DMatch &m2)
{
	if (m1.distance >= m2.distance)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

//删除mat的指定行
bool  delMatRow(cv::Mat src, cv::Mat &dst, std::vector<int> index)
{
	if (src.empty())
	{
		return false;
	}
	else if (index.empty())
	{
		src.copyTo(dst);
		return true;
	}
	cv::Mat dst_;
	sort(index.begin(), index.end());
	for (int i = 0, j = 0;i < src.rows;i++)
	{
		if (i != index[j]) //第i行不是需要删除的
		{
			dst_.push_back(src.row(i)); //把message的第i行加到dst矩阵的后面
		}
		else
		{
			j++;
			if (j == index.size())
			{
				j--;
			}
		}
	}
	dst_.copyTo(dst);
	return false;
}
bool DM_matchTemplateD_SURF(cv::Mat tempImg, cv::Mat trainImg, cv::Mat &matchImg, cv::Mat &perspectiveMatrix, cv::Rect roi, double hessianThreshold)
{
	perspectiveMatrix = cv::Mat();
	matchImg = cv::Mat();

    cv::Ptr<SURF> detector = SURF::create(hessianThreshold);

    std::vector<cv::KeyPoint> keypointsTemp;
    cv::Mat descriptorsTemp;
    detector->detectAndCompute(tempImg, cv::Mat(), keypointsTemp, descriptorsTemp);
	//detector->detectAndCompute(trainImg, Mat(), keypointsTrain, descriptorsTrain);

    std::vector<cv::KeyPoint>  keypointsTrain;
        cv::Mat descriptorsTrain;
        detector->detectAndCompute(trainImg, cv::Mat(), keypointsTrain, descriptorsTrain);

	while (true)
	{
		
		
		
        cv::Mat XX;
        cv::drawKeypoints(trainImg, keypointsTrain,XX);

        std::vector<cv::DMatch> matches;
        cv::BFMatcher matcher;
        std::vector<std::vector<cv::DMatch>> knnMatches;
		matcher.knnMatch(descriptorsTemp, descriptorsTrain, knnMatches, 2);
		double  RatioThreshold = 1 / 1.5;
		for (size_t i = 0; i < knnMatches.size(); i++)
		{
            const cv::DMatch& bestMatch = knnMatches[i][0];
            const cv::DMatch& betterMatch = knnMatches[i][1];

			if (bestMatch.distance <= betterMatch.distance * RatioThreshold)
			{
				matches.push_back(bestMatch);
			}
		}
		if (matches.size() < 4)
		{
			return false;
		}
		

		//最佳匹配点
        std::sort(matches.begin(), matches.end(), comperDmatch);
		double distanceThreshold = 0.2;
			/*matches[0].distance > 0 ? matches[0].distance * 4 : 0.2;
			distanceThreshold = distanceThreshold > 0.2 ? 0.2 : distanceThreshold;*/
        std::vector<cv::DMatch> matchVec;
		for (int i = 0; i < matches.size(); i++)
		{
			if (matches[i].distance <= distanceThreshold)
			{
				matchVec.push_back(matches[i]);     //push_back 将满足条件的值赋值给matchVec数组
			}
		}
		if (matchVec.empty())
		{
			return false;
		}
		//单应性滤波
		//特征点一致性检测
        std::vector<cv::Point2d> obj, scene;
		for (int i = 0; i < matchVec.size(); i++)
		{
			obj.push_back(keypointsTemp[matchVec[i].queryIdx].pt);   //为前图进行特征点索引  pt代表point(pt.x,pt.y);
			scene.push_back(keypointsTrain[matchVec[i].trainIdx].pt);  //为模板进行特征点索引
		}


		std::vector<unsigned char> inliersMask(obj.size());
        perspectiveMatrix = cv::findHomography(obj, scene, CV_RANSAC, 3, inliersMask);  //随机点匹配

		bool flag = false;
		for (size_t i = 0; i < inliersMask.size(); )
		{
			if (!inliersMask[i])
			{
				matchVec.erase(matchVec.begin() + i);
				inliersMask.erase(inliersMask.begin() + i);
				obj.erase(obj.begin() + i);
				scene.erase(scene.begin() + i);
				flag = true;
			}
			else
			{
				i++;
			}
		}
		if (obj.size() < 4 || scene.size() < 4)
		{
			return false;
		}
		if (flag)//重新生成单应性矩阵
		{
			perspectiveMatrix = findHomography(obj, scene, CV_RANSAC);  //随机点匹配
		}
		if (perspectiveMatrix.empty())
		{
			return false;
		}
        cv::drawMatches(tempImg, keypointsTemp, trainImg, keypointsTrain, matchVec, matchImg, cv::Scalar::all(-1),
            cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        std::vector<cv::Point2d> objCorner(4), sceneCors(4);
        objCorner[0] = cv::Point(0, 0);
        objCorner[1] = cv::Point(tempImg.cols - 1, 0);
        objCorner[2] = cv::Point(tempImg.cols - 1, tempImg.rows - 1);
        objCorner[3] = cv::Point(0, tempImg.rows - 1);
        cv::perspectiveTransform(objCorner, sceneCors, perspectiveMatrix);  //映射矩阵

        std::vector<cv::Point> pts;
		pts.push_back(sceneCors[0]);
		pts.push_back(sceneCors[1]);
		pts.push_back(sceneCors[2]);
		pts.push_back(sceneCors[3]);
		roi = cv::boundingRect(pts);

        cv::line(matchImg, cv::Point(sceneCors[0].x + tempImg.cols, sceneCors[0].y), cv::Point(sceneCors[1].x + tempImg.cols, sceneCors[1].y), cv::Scalar(0, 0, 255), 2);
        cv::line(matchImg, cv::Point(sceneCors[1].x + tempImg.cols, sceneCors[1].y), cv::Point(sceneCors[2].x + tempImg.cols, sceneCors[2].y), cv::Scalar(0, 0, 255), 2);
        cv::line(matchImg, cv::Point(sceneCors[2].x + tempImg.cols, sceneCors[2].y), cv::Point(sceneCors[3].x + tempImg.cols, sceneCors[3].y), cv::Scalar(0, 0, 255), 2);
        cv::line(matchImg, cv::Point(sceneCors[3].x + tempImg.cols, sceneCors[3].y), cv::Point(sceneCors[0].x + tempImg.cols, sceneCors[0].y), cv::Scalar(0, 0, 255), 2);

		//删除已经匹配过的特诊点
		/*Mat roiMat = cv::Mat::zeros(roi.size(),CV_8UC1);
		roiMat.copyTo(trainImg(roi));*/

        std::vector<int> delIndex;
		for (int i = 0; i < keypointsTrain.size(); i++)
		{
            if (!(cv::pointPolygonTest(pts, keypointsTrain[i].pt,0) == -1))
			{
				delIndex.push_back(i);
				//keypointsTrain.erase(keypointsTrain.begin() + i);
			}
			
		}
		if (delIndex.empty())
		{
			return true;
		}
		delMatRow(descriptorsTrain, descriptorsTrain, delIndex);
		sort(delIndex.begin(), delIndex.end());
		for (int i = 0; i < delIndex.size();i++)
		{
			keypointsTrain.erase(keypointsTrain.begin() + (delIndex[i]-i));
		}
	}
	return true;
}

bool DM_matchTemplate_ORB(cv::Mat tempImg, cv::Mat trainImg, cv::Mat &matchImg, cv::Mat &perspectiveMatrix,
	int tempfeatures = 500, int trainfeatures = 1000)
{
	perspectiveMatrix = cv::Mat();
	matchImg = cv::Mat();

    std::vector<cv::KeyPoint> keypointsTemp(tempfeatures), keypointsTrain(trainfeatures);
    cv::Mat descriptorsTemp, descriptorsTrain;
    cv::Ptr<cv::ORB> detectorTemp = cv::ORB::create(tempfeatures);
    detectorTemp->detectAndCompute(tempImg, cv::Mat(), keypointsTemp, descriptorsTemp);
    cv::Ptr<cv::ORB> detectorTrain = cv::ORB::create(trainfeatures);
    detectorTrain->detectAndCompute(trainImg, cv::Mat(), keypointsTrain, descriptorsTrain);

    std::vector<cv::DMatch> matches;
    cv::BFMatcher matcher;
    std::vector<std::vector<cv::DMatch>> knnMatches;
    matcher.knnMatch(descriptorsTemp, descriptorsTrain, knnMatches, 2);
	double  RatioThreshold = 0.9;
	for (size_t i = 0; i < knnMatches.size(); i++)
	{
        const cv::DMatch& bestMatch = knnMatches[i][0];
        const cv::DMatch& betterMatch = knnMatches[i][1];

		if (bestMatch.distance <= betterMatch.distance * RatioThreshold)
		{
			matches.push_back(bestMatch);
		}
	}

	if (matches.size() < 4)
	{
		return false;
	}
	//最佳匹配点
	sort(matches.begin(), matches.end(), comperDmatch);
    std::vector<cv::DMatch> matchVec;
	if (matches[0].distance > 0)
	{
		double distanceThreshold = matches[0].distance * 3;
		for (int i = 0; i < matches.size(); i++)
		{
			if (matches[i].distance <= distanceThreshold)
			{
				matchVec.push_back(matches[i]);     //push_back 将满足条件的值赋值给matchVec数组
			}
		}
	}
	else
	{
		matchVec = matches;
	}
	if (matchVec.empty())
	{
		return false;
	}
	//单应性滤波
	//特征点一致性检测
    std::vector<cv::Point2d> obj, scene;
	for (int i = 0; i < matchVec.size(); i++)
	{
		obj.push_back(keypointsTemp[matchVec[i].queryIdx].pt);   //为前图进行特征点索引  pt代表point(pt.x,pt.y);
		scene.push_back(keypointsTrain[matchVec[i].trainIdx].pt);  //为模板进行特征点索引
	}
	std::vector<unsigned char> inliersMask(obj.size());
    perspectiveMatrix = cv::findHomography(obj, scene, CV_RANSAC, 3, inliersMask);  //随机点匹配

	bool flag = false;
	for (size_t i = 0; i < inliersMask.size(); )
	{
		if (!inliersMask[i])
		{
			matchVec.erase(matchVec.begin() + i);
			inliersMask.erase(inliersMask.begin() + i);
			obj.erase(obj.begin() + i);
			scene.erase(scene.begin() + i);
			flag = true;
		}
		else
		{
			i++;
		}
	}
	if (obj.size() < 4 || scene.size() < 4)
	{
		return false;
	}
	if (flag)//重新生成单应性矩阵
	{
		perspectiveMatrix = findHomography(obj, scene, CV_RANSAC);  //随机点匹配
	}
	if (perspectiveMatrix.empty())
	{
		return false;
	}
    cv::drawMatches(tempImg, keypointsTemp, trainImg, keypointsTrain, matchVec, matchImg, cv::Scalar::all(-1),
        cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    std::vector<cv::Point2d> objCorner(4), sceneCors(4);
    objCorner[0] = cv::Point(0, 0);
    objCorner[1] = cv::Point(tempImg.cols - 1, 0);
    objCorner[2] = cv::Point(tempImg.cols - 1, tempImg.rows - 1);
    objCorner[3] = cv::Point(0, tempImg.rows - 1);
    cv::perspectiveTransform(objCorner, sceneCors, perspectiveMatrix);  //映射矩阵

    cv::line(matchImg, cv::Point(sceneCors[0].x + tempImg.cols, sceneCors[0].y), cv::Point(sceneCors[1].x + tempImg.cols, sceneCors[1].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(sceneCors[1].x + tempImg.cols, sceneCors[1].y), cv::Point(sceneCors[2].x + tempImg.cols, sceneCors[2].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(sceneCors[2].x + tempImg.cols, sceneCors[2].y), cv::Point(sceneCors[3].x + tempImg.cols, sceneCors[3].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(sceneCors[3].x + tempImg.cols, sceneCors[3].y), cv::Point(sceneCors[0].x + tempImg.cols, sceneCors[0].y), cv::Scalar(0, 0, 255), 2);
	return true;
}

bool DM_FeatureMatch(cv::Mat descriptorsTrain, cv::Mat descriptorsTemp, std::vector<cv::KeyPoint> keypointsTrain, std::vector<cv::KeyPoint> keypointsTemp, cv::Mat  &perspectiveMatrix)
{
	//匹配特征点
    std::vector<cv::DMatch> matches;
    cv::BFMatcher matcher;
    std::vector<std::vector<cv::DMatch>> knnMatches;
	if (keypointsTrain.size()<4)
	{
		return  false;
	}

	matcher.knnMatch(descriptorsTemp, descriptorsTrain, knnMatches, 2);
    std::vector<cv::DMatch> matchs;  //存储里面的一些点的信息
    matcher.match(descriptorsTemp, descriptorsTrain, matchs, cv::Mat());
	double  RatioThreshold = 0.8;
	for (size_t i = 0; i < knnMatches.size(); i++)
	{
        const cv::DMatch& bestMatch = knnMatches[i][0];
        const cv::DMatch& betterMatch = knnMatches[i][1];
		if (bestMatch.distance <= betterMatch.distance * RatioThreshold)
		{
			matches.push_back(bestMatch);
		}
	}
	if (matches.size() < 4)
	{
		return false;
	}

	//最佳匹配点
    std::sort(matches.begin(), matches.end(), comperDmatch);
    std::vector<cv::DMatch> matchVec;
	if (matches[0].distance > 0)
	{
		double distanceThreshold = matches[0].distance * 5;
		for (int i = 0; i < matches.size(); i++)
		{
			if (matches[i].distance <= distanceThreshold)
			{
				matchVec.push_back(matches[i]);     //push_back 将满足条件的值赋值给matchVec数组
			}
		}
	}
	else
	{
		matchVec = matches;
	}
	if (matchVec.empty())
	{
		return false;
	}

	//单应性滤波
	//特征点一致性检测
    std::vector<cv::Point2d> obj, scene;
	for (int i = 0; i < matchVec.size(); i++)
	{
		obj.push_back(keypointsTemp[matchVec[i].queryIdx].pt);   //为前图进行特征点索引  pt代表point(pt.x,pt.y);
		scene.push_back(keypointsTrain[matchVec[i].trainIdx].pt);  //为模板进行特征点索引
	}
	std::vector<unsigned char> inliersMask(obj.size());
    perspectiveMatrix = cv::findHomography(obj, scene, CV_RANSAC, 3, inliersMask);  //随机点匹配

	bool flag = false;
	for (size_t i = 0; i < inliersMask.size(); )
	{
		if (!inliersMask[i])
		{
			matchVec.erase(matchVec.begin() + i);
			inliersMask.erase(inliersMask.begin() + i);
			obj.erase(obj.begin() + i);
			scene.erase(scene.begin() + i);
			flag = true;
		}
		else
		{
			i++;
		}
	}
	if (obj.size() < 4 || scene.size() < 4)
	{
		return false;
	}
	if (flag)//重新生成单应性矩阵
	{
		perspectiveMatrix = findHomography(obj, scene, CV_RANSAC);  //随机点匹配
	}
	if (perspectiveMatrix.empty())
	{
		return false;
	}
	return true;
}

//匹配多组，按照轮廓分类方式进行
bool DM_matchTemplateBase_SIFT(cv::Mat tempImg, cv::Mat trainImg, std::vector<std::vector<cv::Point2d>> &roitVertices, std::vector<cv::Point2d> &grabPoints,
                               cv::Point2d templateGrabP = cv::Point2d(-1,-1), int tempfeatures = 0, int trainfeatures = 0)
{
	if (tempImg.empty() || trainImg.empty())
	{
		return false;
	}
	//查找模板特征点
    std::vector<cv::KeyPoint> keypointsTemp;
	cv::Mat descriptorsTemp;

    cv::Ptr<SIFT> detector = SIFT::create(tempfeatures);
    detector->detectAndCompute(tempImg, cv::Mat(), keypointsTemp, descriptorsTemp);
	if (keypointsTemp.size() < 4)
	{
		return false;
	}

	//查找待检测图片的特征点
    std::vector<cv::KeyPoint> keypointsTrain;
	cv::Mat	descriptorsTrain;

    cv::Ptr<SIFT> detectorTrain = SIFT::create(trainfeatures);
	
    detectorTrain->detectAndCompute(trainImg, cv::Mat(), keypointsTrain, descriptorsTrain);
	if (keypointsTrain.size() < 4)
	{
		return false;
	}

	//描述特征点
	cv::Mat tempC, trainC;
    cv::cvtColor(tempImg, tempC, cv::COLOR_GRAY2BGR);
    cv::cvtColor(trainImg, trainC, cv::COLOR_GRAY2BGR);
	for (int i =0; i < keypointsTemp.size(); i++)
	{
        cv::circle(tempC, keypointsTemp[i].pt, 3, cv::Scalar(255, 0, 0), -1);
	}
	
    std::vector<cv::Point2f> keyPointsT;
	for (int i = 0; i < keypointsTrain.size(); i++)
	{
		keyPointsT.push_back(keypointsTrain[i].pt);
	}
	cv::Mat label,centerIMG;
	int k = keypointsTrain.size() / keypointsTemp.size();
	k = k < 1 ? 1 : k;
    cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 0.1);
    cv::kmeans(keyPointsT, k , label, criteria, 3, cv::KMEANS_PP_CENTERS, centerIMG);
    std::vector<cv::Mat> descriptorsT;
    std::vector<std::vector<cv::KeyPoint>> keypointsT;
    cv::Scalar colorTab[] = {
                            cv::Scalar(25 ,0,0),
                            cv::Scalar(50 ,0,0),
                            cv::Scalar(75 ,0,0),
                            cv::Scalar(100,0,0),
                            cv::Scalar(125,0,0),
                            cv::Scalar(150,0,0),
                            cv::Scalar(175,0,0),
                            cv::Scalar(200,0,0),
                            cv::Scalar(225,0,0),
                            cv::Scalar(250,0,0),
							
                            cv::Scalar(0,25 ,0),
                            cv::Scalar(0,50 ,0),
                            cv::Scalar(0,75 ,0),
                            cv::Scalar(0,100,0),
                            cv::Scalar(0,125,0),
                            cv::Scalar(0,150,0),
                            cv::Scalar(0,175,0),
                            cv::Scalar(0,200,0),
                            cv::Scalar(0,225,0),
                            cv::Scalar(0,250,0),
							
                            cv::Scalar(0,0,25),
                            cv::Scalar(0,0,50),
                            cv::Scalar(0,0,75),
                            cv::Scalar(0,0,100),
                            cv::Scalar(0,0,125),
                            cv::Scalar(0,0,150),
                            cv::Scalar(0,0,175),
                            cv::Scalar(0,0,200),
                            cv::Scalar(0,0,225),
                            cv::Scalar(0,0,250)};
	for (int i = 0; i < keypointsTrain.size(); i++)
	{
		int xx = label.at<int>(i);
        cv::circle(trainC, keyPointsT[i], 3, colorTab[xx%30], -1);

	}
	for (int i = 0; i < k; i++)
	{
		float x = centerIMG.at<float>(i, 0);
		float y = centerIMG.at<float>(i, 1);
        cv::circle(trainC, cv::Point(x, y), 5, colorTab[i%30], 1);
	}



	for (int i = 0; i < k; i++)
	{
        cv::Mat descriptorsTTemp;
        std::vector<cv::KeyPoint> keypointsTTemp;

		for (int j = 0; j < descriptorsTrain.rows; j++)
		{
			if (label.at<int>(j) == i)
			{
				descriptorsTTemp.push_back(descriptorsTrain.row(j));
				keypointsTTemp.push_back(keypointsTrain[j]);
			}
		}
		descriptorsT.push_back(descriptorsTTemp);
		keypointsT.push_back(keypointsTTemp);
		cv::Mat  perspectiveMatrix;
		if (DM_FeatureMatch(descriptorsTTemp,descriptorsTemp,keypointsTTemp, keypointsTemp, perspectiveMatrix))
		{
			//查找对应的斜矩形
            std::vector<cv::Point2d> objVertices(4), sceneVertices(4);
            objVertices[0] = cv::Point2d(0, 0);
            objVertices[1] = cv::Point2d(tempImg.cols - 1, 0);
            objVertices[2] = cv::Point2d(tempImg.cols - 1, tempImg.rows - 1);
            objVertices[3] = cv::Point2d(0, tempImg.rows - 1);
			cv::perspectiveTransform(objVertices, sceneVertices, perspectiveMatrix);  //映射矩阵(模板的四个端点)

			//抓取点
            std::vector<cv::Point2d> grabP_original(1), grabP_object(1);
			if (templateGrabP.x >= 0 && templateGrabP.y >= 0)
			{
				grabP_original[0] = templateGrabP;
			}
			else
			{
                grabP_original[0] = cv::Point2d(double(tempImg.cols - 1)/2.0, double(tempImg.rows - 1)/2.0);
			}
			cv::perspectiveTransform(grabP_original, grabP_object, perspectiveMatrix);  //映射矩阵(模板的四个端点)
            std::vector<cv::Point2f> pts{
									sceneVertices[0],
									sceneVertices[1],
									sceneVertices[2],
									sceneVertices[3] };
            cv::RotatedRect rRect = cv::minAreaRect(pts);
			//判定找到的区域和模板区域做对比
			int tempS = tempImg.rows * tempImg.cols;
			int roiS = rRect.size.width * rRect.size.height;
			int tempMinL = tempImg.rows > tempImg.cols ? tempImg.cols : tempImg.rows;
			int tempMaxL = tempImg.rows > tempImg.cols ? tempImg.rows : tempImg.cols;
			int RoiMinL = rRect.size.width > rRect.size.height ? rRect.size.height : rRect.size.width;
			int RoiMaxL = rRect.size.width > rRect.size.height ? rRect.size.width : rRect.size.height;
			if (tempS > roiS * 5 ||
				tempS * 5 < roiS ||
				tempMinL > RoiMinL * 5 ||
				tempMinL * 5 < RoiMinL ||
				tempMaxL > RoiMaxL * 5 ||
				tempMaxL * 5 < RoiMaxL)
			{
				continue;
			}
			roitVertices.push_back(sceneVertices);
			grabPoints.push_back(grabP_object[0]);

            cv::line(trainC, cv::Point(sceneVertices[0].x, sceneVertices[0].y), cv::Point(sceneVertices[1].x, sceneVertices[1].y), cv::Scalar(0, 0, 255), 2);
            cv::line(trainC, cv::Point(sceneVertices[1].x, sceneVertices[1].y), cv::Point(sceneVertices[2].x, sceneVertices[2].y), cv::Scalar(0, 0, 255), 2);
            cv::line(trainC, cv::Point(sceneVertices[2].x, sceneVertices[2].y), cv::Point(sceneVertices[3].x, sceneVertices[3].y), cv::Scalar(0, 0, 255), 2);
            cv::line(trainC, cv::Point(sceneVertices[3].x, sceneVertices[3].y), cv::Point(sceneVertices[0].x, sceneVertices[0].y), cv::Scalar(0, 0, 255), 2);
            cv::circle(trainC, cv::Point(grabP_object[0].x, grabP_object[0].y), 3, cv::Scalar(0, 0, 255), -1);

		}
	}
	return true;
}

//在图片中找多组，利用轮廓查找，先将图像取反，然后查找【效果不佳】
bool DM_matchTemplateBase_SIFT_D(cv::Mat tempImg, cv::Mat trainImg, std::vector<std::vector<cv::Point2d>> &roitVertices, std::vector<cv::Point2d> &grabPoints,
                               cv::Point2d templateGrabP = cv::Point2d(-1,-1), int tempfeatures = 0, int trainfeatures = 0)
{
	if (tempImg.empty() || trainImg.empty())
	{
		return false;
	}
	//查找模板特征点
    std::vector<cv::KeyPoint> keypointsTemp;
	cv::Mat descriptorsTemp;
    cv::Ptr<SIFT> detector = SIFT::create(tempfeatures);
    detector->detectAndCompute(tempImg, cv::Mat(), keypointsTemp, descriptorsTemp);
	if (keypointsTemp.size() < 4)
	{
		return false;
	}

	//查找待检测图片的特征点
    std::vector<cv::KeyPoint> keypointsTrain;
	cv::Mat	descriptorsTrain;
    cv::Ptr<SIFT> detectorTrain = SIFT::create(trainfeatures);
    detectorTrain->detectAndCompute(trainImg, cv::Mat(), keypointsTrain, descriptorsTrain);
	if (keypointsTrain.size() < 4)
	{
		return false;
	}

	//查找轮廓
	cv::Mat binaryImg;
	cv::threshold(trainImg, binaryImg, 100, 255, CV_THRESH_OTSU);
    int mode_ = cv::RETR_EXTERNAL;
    int method_ = cv::CHAIN_APPROX_NONE;
    std::vector<std::vector<cv::Point>> contours;//返回找到的轮廓
    std::vector<cv::Vec4i> hierarchy; //轮廓索引编号
    cv::findContours(binaryImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    std::vector<cv::RotatedRect> trainRect;
	for (int i = 0; i < contours.size(); i++)
	{
        trainRect.push_back(cv::minAreaRect(contours[i]));
	}
    std::vector<cv::Mat> descriptorsTrainClass;
    std::vector<std::vector<cv::KeyPoint>> keypointsTrainClass;

	//描述特征点
	cv::Mat tempC, trainC;
    cvtColor(tempImg, tempC, cv::COLOR_GRAY2BGR);
    cvtColor(trainImg, trainC, cv::COLOR_GRAY2BGR);

	if (trainRect.empty())
	{
		descriptorsTrainClass.push_back(descriptorsTrain);
		keypointsTrainClass.push_back(keypointsTrain);
	}
	else
	{
		for (int i = 0; i < trainRect.size(); i++)
		{
            cv::Point2f pts[4];
			trainRect[i].points(pts);
            std::vector<cv::Point2f> ptss;
			ptss.push_back(pts[0]);
			ptss.push_back(pts[1]);
			ptss.push_back(pts[2]);
			ptss.push_back(pts[3]);
						



            cv::Mat descriptorsTrainT;
            std::vector<cv::KeyPoint> keypointsTrainT;

			for (int j = 0; j < descriptorsTrain.rows; j++)
			{
                if (cv::pointPolygonTest(ptss, keypointsTrain[j].pt, false) >= 0)
				{
                    cv::line(trainC, cv::Point(ptss[0].x, ptss[0].y), cv::Point(ptss[1].x, ptss[1].y), cv::Scalar(0, 0, 255), 2);
                    cv::line(trainC, cv::Point(ptss[1].x, ptss[1].y), cv::Point(ptss[2].x, ptss[2].y), cv::Scalar(0, 0, 255), 2);
                    cv::line(trainC, cv::Point(ptss[2].x, ptss[2].y), cv::Point(ptss[3].x, ptss[3].y), cv::Scalar(0, 0, 255), 2);
                    cv::line(trainC, cv::Point(ptss[3].x, ptss[3].y), cv::Point(ptss[0].x, ptss[0].y), cv::Scalar(0, 0, 255), 2);

					descriptorsTrainT.push_back(descriptorsTrain.row(j));
					keypointsTrainT.push_back(keypointsTrain[j]);
				}
			}
			descriptorsTrainClass.push_back(descriptorsTrainT);
			keypointsTrainClass.push_back(keypointsTrainT);
		}
	}
	for (int i = 0; i < keypointsTemp.size(); i++)
	{
        circle(tempC, keypointsTemp[i].pt, 3, cv::Scalar(255, 0, 0), -1);
	}
    cv::Scalar colorTab[] = {
                            cv::Scalar(25 ,0,0),
                            cv::Scalar(50 ,0,0),
                            cv::Scalar(75 ,0,0),
                            cv::Scalar(100,0,0),
                            cv::Scalar(125,0,0),
                            cv::Scalar(150,0,0),
                            cv::Scalar(175,0,0),
                            cv::Scalar(200,0,0),
                            cv::Scalar(225,0,0),
                            cv::Scalar(250,0,0),

                            cv::Scalar(0,25 ,0),
                            cv::Scalar(0,50 ,0),
                            cv::Scalar(0,75 ,0),
                            cv::Scalar(0,100,0),
                            cv::Scalar(0,125,0),
                            cv::Scalar(0,150,0),
                            cv::Scalar(0,175,0),
                            cv::Scalar(0,200,0),
                            cv::Scalar(0,225,0),
                            cv::Scalar(0,250,0),

                            cv::Scalar(0,0,25),
                            cv::Scalar(0,0,50),
                            cv::Scalar(0,0,75),
                            cv::Scalar(0,0,100),
                            cv::Scalar(0,0,125),
                            cv::Scalar(0,0,150),
                            cv::Scalar(0,0,175),
                            cv::Scalar(0,0,200),
                            cv::Scalar(0,0,225),
                            cv::Scalar(0,0,250) };

	for (int i = 0; i < keypointsTrainClass.size(); i++)
	{
		for (int j = 0; j < keypointsTrainClass[i].size(); j++)
		{
			circle(trainC, keypointsTrainClass[i][j].pt, 5, colorTab[i % 30], 1);
		}
	}
	for (int i = 0; i < descriptorsTrainClass.size(); i++)
	{
		cv::Mat  perspectiveMatrix;
		if (DM_FeatureMatch(descriptorsTrainClass[i], descriptorsTemp, keypointsTrainClass[i], keypointsTemp, perspectiveMatrix))
		{
			//查找对应的斜矩形
            std::vector<cv::Point2d> objVertices(4), sceneVertices(4);
            objVertices[0] = cv::Point2d(0, 0);
            objVertices[1] = cv::Point2d(tempImg.cols - 1, 0);
            objVertices[2] = cv::Point2d(tempImg.cols - 1, tempImg.rows - 1);
            objVertices[3] = cv::Point2d(0, tempImg.rows - 1);
			cv::perspectiveTransform(objVertices, sceneVertices, perspectiveMatrix);  //映射矩阵(模板的四个端点)

			//抓取点
            std::vector<cv::Point2d> grabP_original(1), grabP_object(1);
			if (templateGrabP.x >= 0 && templateGrabP.y >= 0)
			{
				grabP_original[0] = templateGrabP;
			}
			else
			{
                grabP_original[0] = cv::Point2d(double(tempImg.cols - 1) / 2.0, double(tempImg.rows - 1) / 2.0);
			}
			cv::perspectiveTransform(grabP_original, grabP_object, perspectiveMatrix);  //映射矩阵(模板的四个端点)
            std::vector<cv::Point2f> pts{
									sceneVertices[0],
									sceneVertices[1],
									sceneVertices[2],
									sceneVertices[3] };
            cv::RotatedRect rRect = cv::minAreaRect(pts);
			//判定找到的区域和模板区域做对比
			int tempS = tempImg.rows * tempImg.cols;
			int roiS = rRect.size.width * rRect.size.height;
			int tempMinL = tempImg.rows > tempImg.cols ? tempImg.cols : tempImg.rows;
			int tempMaxL = tempImg.rows > tempImg.cols ? tempImg.rows : tempImg.cols;
			int RoiMinL = rRect.size.width > rRect.size.height ? rRect.size.height : rRect.size.width;
			int RoiMaxL = rRect.size.width > rRect.size.height ? rRect.size.width : rRect.size.height;
			if (tempS > roiS * 5 ||
				tempS * 5 < roiS ||
				tempMinL > RoiMinL * 5 ||
				tempMinL * 5 < RoiMinL ||
				tempMaxL > RoiMaxL * 5 ||
				tempMaxL * 5 < RoiMaxL)
			{
				continue;
			}
			roitVertices.push_back(sceneVertices);
			grabPoints.push_back(grabP_object[0]);

            cv::line(trainC, cv::Point(sceneVertices[0].x, sceneVertices[0].y), cv::Point(sceneVertices[1].x, sceneVertices[1].y), cv::Scalar(0, 0, 255), 2);
            cv::line(trainC, cv::Point(sceneVertices[1].x, sceneVertices[1].y), cv::Point(sceneVertices[2].x, sceneVertices[2].y), cv::Scalar(0, 0, 255), 2);
            cv::line(trainC, cv::Point(sceneVertices[2].x, sceneVertices[2].y), cv::Point(sceneVertices[3].x, sceneVertices[3].y), cv::Scalar(0, 0, 255), 2);
            cv::line(trainC, cv::Point(sceneVertices[3].x, sceneVertices[3].y), cv::Point(sceneVertices[0].x, sceneVertices[0].y), cv::Scalar(0, 0, 255), 2);
            cv::circle(trainC, cv::Point(grabP_object[0].x, grabP_object[0].y), 3, cv::Scalar(0, 0, 255), -1);

		}
	}
	
	return true;
}
//在图片中找一组
bool DM_matchTemplateBase_SIFT_backups(cv::Mat tempImg, cv::Mat trainImg, std::vector<std::vector<cv::Point2d>> &roitVertices, std::vector<cv::Point2d> &grabPoints,
                              cv::Point2d templateGrabP = cv::Point2d(-1, -1), int tempfeatures = 0, int trainfeatures = 0)
{
	if (tempImg.empty() || trainImg.empty())
	{
		return false;
	}
	//查找模板特征点
    std::vector<cv::KeyPoint> keypointsTemp;
	cv::Mat descriptorsTemp;

    cv::Ptr<SIFT> detector = SIFT::create(tempfeatures);
    detector->detectAndCompute(tempImg, cv::Mat(), keypointsTemp, descriptorsTemp);
	if (keypointsTemp.size() < 4)
	{
		return false;
	}

	//查找待检测图片的特征点
    std::vector<cv::KeyPoint> keypointsTrain;
	cv::Mat	descriptorsTrain;

    cv::Ptr<SIFT> detectorTrain = SIFT::create(trainfeatures);

    detectorTrain->detectAndCompute(trainImg, cv::Mat(), keypointsTrain, descriptorsTrain);
	if (keypointsTrain.size() < 4)
	{
		return false;
	}


	//匹配特征点
    std::vector<cv::DMatch> matches;
    cv::BFMatcher matcher;
    std::vector<std::vector<cv::DMatch>> knnMatches;
	matcher.knnMatch(descriptorsTemp, descriptorsTrain, knnMatches, 2);
	double  RatioThreshold = 0.7;
	for (size_t i = 0; i < knnMatches.size(); i++)
	{
        const cv::DMatch& bestMatch = knnMatches[i][0];
        const cv::DMatch& betterMatch = knnMatches[i][1];
		if (bestMatch.distance <= betterMatch.distance * RatioThreshold)
		{
			matches.push_back(bestMatch);
		}
	}
	if (matches.size() < 4)
	{
		return false;
	}

	//最佳匹配点
    std::sort(matches.begin(), matches.end(), comperDmatch);
    std::vector<cv::DMatch> matchVec;
	if (matches[0].distance > 0)
	{
		double distanceThreshold = matches[0].distance * 3;
		for (int i = 0; i < matches.size(); i++)
		{
			if (matches[i].distance <= distanceThreshold)
			{
				matchVec.push_back(matches[i]);     //push_back 将满足条件的值赋值给matchVec数组
			}
		}
	}
	else
	{
		matchVec = matches;
	}
	if (matchVec.empty())
	{
		return false;
	}

	//单应性滤波
	//特征点一致性检测
    std::vector<cv::Point2d> obj, scene;
	for (int i = 0; i < matchVec.size(); i++)
	{
		obj.push_back(keypointsTemp[matchVec[i].queryIdx].pt);   //为前图进行特征点索引  pt代表point(pt.x,pt.y);
		scene.push_back(keypointsTrain[matchVec[i].trainIdx].pt);  //为模板进行特征点索引
	}
	std::vector<unsigned char> inliersMask(obj.size());
    cv::Mat  perspectiveMatrix = cv::findHomography(obj, scene, CV_RANSAC, 3, inliersMask);  //随机点匹配

	bool flag = false;
	for (size_t i = 0; i < inliersMask.size(); )
	{
		if (!inliersMask[i])
		{
			matchVec.erase(matchVec.begin() + i);
			inliersMask.erase(inliersMask.begin() + i);
			obj.erase(obj.begin() + i);
			scene.erase(scene.begin() + i);
			flag = true;
		}
		else
		{
			i++;
		}
	}
	if (obj.size() < 4 || scene.size() < 4)
	{
		return false;
	}
	if (flag)//重新生成单应性矩阵
	{
        perspectiveMatrix = cv::findHomography(obj, scene, CV_RANSAC);  //随机点匹配
	}
	if (perspectiveMatrix.empty())
	{
		return false;
	}

	//查找对应的斜矩形
    std::vector<cv::Point2d> objVertices(4), sceneVertices(4);
    objVertices[0] = cv::Point2d(0, 0);
    objVertices[1] = cv::Point2d(tempImg.cols - 1, 0);
    objVertices[2] = cv::Point2d(tempImg.cols - 1, tempImg.rows - 1);
    objVertices[3] = cv::Point2d(0, tempImg.rows - 1);
	cv::perspectiveTransform(objVertices, sceneVertices, perspectiveMatrix);  //映射矩阵

	//抓取点
    std::vector<cv::Point2d> grabP_original(1), grabP_object(1);
	if (templateGrabP.x >= 0 && templateGrabP.y >= 0)
	{
		grabP_original[0] = templateGrabP;
	}
	else
	{
        grabP_original[0] = cv::Point2d(double(tempImg.cols - 1) / 2.0, double(tempImg.rows - 1) / 2.0);
	}
	cv::perspectiveTransform(grabP_original, grabP_object, perspectiveMatrix);  //映射矩阵(模板的四个端点)

    std::vector<cv::Point2f> pts{
		sceneVertices[0],
		sceneVertices[1],
		sceneVertices[2],
		sceneVertices[3] };
    cv::RotatedRect rRect = cv::minAreaRect(pts);
	//判定找到的区域和模板区域做对比
	int tempS = tempImg.rows * tempImg.cols;
	int roiS = rRect.size.width * rRect.size.height;
	int tempMinL = tempImg.rows > tempImg.cols ? tempImg.cols : tempImg.rows;
	int tempMaxL = tempImg.rows > tempImg.cols ? tempImg.rows : tempImg.cols;
	int RoiMinL = rRect.size.width > rRect.size.height ? rRect.size.height : rRect.size.width;
	int RoiMaxL = rRect.size.width > rRect.size.height ? rRect.size.width : rRect.size.height;
	if (tempS > roiS * 5 ||
		tempS * 5 < roiS ||
		tempMinL > RoiMinL * 5 ||
		tempMinL * 5 < RoiMinL ||
		tempMaxL > RoiMaxL * 5 ||
		tempMaxL * 5 < RoiMaxL)
	{
		return false;
	}
	roitVertices.push_back(sceneVertices);
	grabPoints.push_back(grabP_object[0]);
#ifdef DM_Dubeg_Mode	
	//绘制特征点，及边框；
	cv::Mat matchImg;
    cv::drawMatches(tempImg, keypointsTemp, trainImg, keypointsTrain, matchVec, matchImg, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    cv::line(matchImg, cv::Point(sceneVertices[0].x + tempImg.cols, sceneVertices[0].y), cv::Point(sceneVertices[1].x + tempImg.cols, sceneVertices[1].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(sceneVertices[1].x + tempImg.cols, sceneVertices[1].y), cv::Point(sceneVertices[2].x + tempImg.cols, sceneVertices[2].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(sceneVertices[2].x + tempImg.cols, sceneVertices[2].y), cv::Point(sceneVertices[3].x + tempImg.cols, sceneVertices[3].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(sceneVertices[3].x + tempImg.cols, sceneVertices[3].y), cv::Point(sceneVertices[0].x + tempImg.cols, sceneVertices[0].y), cv::Scalar(0, 0, 255), 2);
#endif
	return true;
}
//=======================================================================================================================================
//函数名称：基于SIFT的模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@roiVertices：模板图片的四个顶点对应在trainImg种位置，0-左上，1-右上，2-右下，3-左下点
//  @grabPoints:被检测图片的
//  @templateGrabP:模板的抓取位置
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@tempfeatures:模板特征点的个数，默认为0，全部查找
//	@trainfeatures：:检测图片特征点的个数，默认为0，全部查找
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配唯一的缺点是运算比较慢，但是是一个万能匹配算法，具备旋转不变性，尺度不变性，位移不变性等良好的特性
//  ②本算法考虑的图像的倾斜关系，所以输出来的4个顶点并不一定是矩形，可能是梯形，如果是二维平面变化，需要再用minAreaRect函数求解外接矩形
//=======================================================================================================================================
bool DM_matchTemplateFast_SIFT(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<std::vector<cv::Point2d>> &roiVertices, std::vector<cv::Point2d> &grabPoints,
    cv::Point2d templateGrabP, double imgScale, int tempfeatures, int trainfeatures)
{

	roiVertices.clear();
	grabPoints.clear();
	if (tempImg_.empty() || trainImg_.empty())
	{
		return false;
	}
	if (imgScale<=0)
	{
		imgScale = 1;
	}
	cv::Mat tempImg;
	cv::Mat trainImg;
    cv::resize(tempImg_, tempImg, cv::Size(tempImg_.cols / imgScale, tempImg_.rows / imgScale));
    cv::resize(trainImg_, trainImg, cv::Size(trainImg_.cols / imgScale, trainImg_.rows / imgScale));
	
    std::vector<std::vector<cv::Point2d>> vertices;
    std::vector<cv::Point2d> grabP;
	if (DM_matchTemplateBase_SIFT_backups(tempImg, trainImg, vertices, grabP, templateGrabP, tempfeatures, trainfeatures))
	{
		for (int i = 0; i < vertices.size(); i++)
		{
            std::vector<cv::Point2d> pts;
			//调整透视变化矩阵
            pts.push_back(cv::Point2d(vertices[i][0].x*imgScale, vertices[i][0].y*imgScale));
            pts.push_back(cv::Point2d(vertices[i][1].x*imgScale, vertices[i][1].y*imgScale));
            pts.push_back(cv::Point2d(vertices[i][2].x*imgScale, vertices[i][2].y*imgScale));
            pts.push_back(cv::Point2d(vertices[i][3].x*imgScale, vertices[i][3].y*imgScale));
			roiVertices.push_back(pts);
            cv::Point2d  grabP_ = cv::Point2d(grabP[i].x*imgScale, grabP[i].y*imgScale);
			
			grabPoints.push_back(grabP_);
#ifdef DM_Dubeg_Mode	
			cv::Mat dst;
            cv::cvtColor(trainImg_, dst, cv::COLOR_GRAY2BGR);
            cv::line(dst, cv::Point(pts[0].x, pts[0].y), cv::Point(pts[1].x, pts[1].y), cv::Scalar(0, 0, 255), 1);
            cv::line(dst, cv::Point(pts[1].x, pts[1].y), cv::Point(pts[2].x, pts[2].y), cv::Scalar(0, 0, 255), 1);
            cv::line(dst, cv::Point(pts[2].x, pts[2].y), cv::Point(pts[3].x, pts[3].y), cv::Scalar(0, 0, 255), 1);
            cv::line(dst, cv::Point(pts[3].x, pts[3].y), cv::Point(pts[0].x, pts[0].y), cv::Scalar(0, 0, 255), 1);

            cv::circle(dst, cv::Point(grabP_.x, grabP_.y), 3, cv::Scalar(0, 0, 255), -1);
#endif
		}
		return true;
	}
	else
	{
		return false;
	}
	
}

//=======================================================================================================================================
//函数名称：基于SURF的模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@roiVertices：模板图片的四个顶点对应在trainImg种位置，0-左上，1-右上，2-右下，3-左下点
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@tempHessianThreshold:模板特征点的Hessian阈值，值越大，特征点越小
//	@trainHessianThreshold:检测图片特征点的Hessian阈值，值越大，特征点越小
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配唯一的缺点是运算比较慢，但是是一个万能匹配算法，具备旋转不变性，尺度不变性，位移不变性等良好的特性
//  ②本算法考虑的图像的倾斜关系，所以输出来的4个顶点并不一定是矩形，可能是梯形，如果是二维平面变化，需要再用minAreaRect函数求解外接矩形
//=======================================================================================================================================
bool DM_matchTemplateBase_SURF(cv::Mat tempImg, cv::Mat trainImg, std::vector<cv::Point2d> &roitVertices, double tempHessianThreshold = 500, double trainHessianThreshold = 500)
{
	if (tempImg.empty() || trainImg.empty())
	{
		return false;
	}
	//查找模板特征点
    std::vector<cv::KeyPoint> keypointsTemp;
	cv::Mat descriptorsTemp;

    cv::Ptr<SURF> detector = SURF::create(tempHessianThreshold);
    detector->detectAndCompute(tempImg, cv::Mat(), keypointsTemp, descriptorsTemp);
	if (keypointsTemp.size() < 4)
	{
		return false;
	}

	//查找待检测图片的特征点
    std::vector<cv::KeyPoint> keypointsTrain;
	cv::Mat	descriptorsTrain;

    cv::Ptr<SURF> detectorTrain = cv::xfeatures2d::SURF::create(trainHessianThreshold);

    detectorTrain->detectAndCompute(trainImg, cv::Mat(), keypointsTrain, descriptorsTrain);
	if (keypointsTrain.size() < 4)
	{
		return false;
	}

	//匹配特征点
    std::vector<cv::DMatch> matches;
    cv::BFMatcher matcher;
    std::vector<std::vector<cv::DMatch>> knnMatches;
	matcher.knnMatch(descriptorsTemp, descriptorsTrain, knnMatches, 2);
	double  RatioThreshold = 0.7;
	for (size_t i = 0; i < knnMatches.size(); i++)
	{
        const cv::DMatch& bestMatch = knnMatches[i][0];
        const cv::DMatch& betterMatch = knnMatches[i][1];
		if (bestMatch.distance <= betterMatch.distance * RatioThreshold)
		{
			matches.push_back(bestMatch);
		}
	}
	if (matches.size() < 4)
	{
		return false;
	}

	//最佳匹配点
    std::sort(matches.begin(), matches.end(), comperDmatch);
	double distanceThreshold = matches[0].distance > 0 ? matches[0].distance * 5 : 0.3;
	distanceThreshold = distanceThreshold > 0.3 ? 0.3 : distanceThreshold;
    std::vector<cv::DMatch> matchVec;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance <= distanceThreshold)
		{
			matchVec.push_back(matches[i]);     //push_back 将满足条件的值赋值给matchVec数组
		}
	}
	if (matchVec.empty())
	{
		return false;
	}
	//单应性滤波
	//特征点一致性检测
    std::vector<cv::Point2d> obj, scene;
	for (int i = 0; i < matchVec.size(); i++)
	{
		obj.push_back(keypointsTemp[matchVec[i].queryIdx].pt);   //为前图进行特征点索引  pt代表point(pt.x,pt.y);
		scene.push_back(keypointsTrain[matchVec[i].trainIdx].pt);  //为模板进行特征点索引
	}
    std::vector<unsigned char> inliersMask(obj.size());
    cv::Mat  perspectiveMatrix = cv::findHomography(obj, scene, CV_RANSAC, 3, inliersMask);  //随机点匹配
	cv::Mat matchImg1;
    cv::drawMatches(tempImg, keypointsTemp, trainImg, keypointsTrain, matchVec, matchImg1, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	bool flag = false;
	for (size_t i = 0; i < inliersMask.size(); )
	{
		if (!inliersMask[i])
		{
			matchVec.erase(matchVec.begin() + i);
			inliersMask.erase(inliersMask.begin() + i);
			obj.erase(obj.begin() + i);
			scene.erase(scene.begin() + i);
			flag = true;
		}
		else
		{
			i++;
		}
	}
	if (obj.size() < 4 || scene.size() < 4)
	{
		return false;
	}
	if (flag)//重新生成单应性矩阵
	{
		perspectiveMatrix = findHomography(obj, scene);  //随机点匹配
	}
	if (perspectiveMatrix.empty())
	{
		return false;
	}

	//查找对应的斜矩形
    std::vector<cv::Point2d> objVertices(8), sceneVertices(8);
    objVertices[0] = cv::Point2d(0, 0);
    objVertices[1] = cv::Point2d(tempImg.cols - 1, 0);
    objVertices[2] = cv::Point2d(tempImg.cols - 1, tempImg.rows - 1);
    objVertices[3] = cv::Point2d(0, tempImg.rows - 1);

	cv::perspectiveTransform(objVertices, sceneVertices, perspectiveMatrix);  //映射矩阵

    std::vector<cv::Point2f> pts{
		sceneVertices[0],
		sceneVertices[1],
		sceneVertices[2],
		sceneVertices[3] };
    cv::RotatedRect rRect = cv::minAreaRect(pts);
	//判定找到的区域和模板区域做对比
	int tempS = tempImg.rows * tempImg.cols;
	int roiS = rRect.size.width * rRect.size.height;
	int tempMinL = tempImg.rows > tempImg.cols ? tempImg.cols : tempImg.rows;
	int tempMaxL = tempImg.rows > tempImg.cols ? tempImg.rows : tempImg.cols;
	int RoiMinL = rRect.size.width > rRect.size.height ? rRect.size.height : rRect.size.width;
	int RoiMaxL = rRect.size.width > rRect.size.height ? rRect.size.width : rRect.size.height;
	if (tempS > roiS * 5 ||
		tempS * 5 < roiS ||
		tempMinL > RoiMinL * 5 ||
		tempMinL * 5 < RoiMinL ||
		tempMaxL > RoiMaxL * 5 ||
		tempMaxL * 5 < RoiMaxL)
	{
		return false;
	}
	roitVertices = sceneVertices;

#ifdef DM_Dubeg_Mode	
	//绘制特征点，及边框；
	cv::Mat matchImg;
    cv::drawMatches(tempImg, keypointsTemp, trainImg, keypointsTrain, matchVec, matchImg, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    cv::line(matchImg, cv::Point(roitVertices[0].x + tempImg.cols, roitVertices[0].y), cv::Point(roitVertices[1].x + tempImg.cols, roitVertices[1].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(roitVertices[1].x + tempImg.cols, roitVertices[1].y), cv::Point(roitVertices[2].x + tempImg.cols, roitVertices[2].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(roitVertices[2].x + tempImg.cols, roitVertices[2].y), cv::Point(roitVertices[3].x + tempImg.cols, roitVertices[3].y), cv::Scalar(0, 0, 255), 2);
    cv::line(matchImg, cv::Point(roitVertices[3].x + tempImg.cols, roitVertices[3].y), cv::Point(roitVertices[0].x + tempImg.cols, roitVertices[0].y), cv::Scalar(0, 0, 255), 2);

#endif
	return true;
}
//=======================================================================================================================================
//函数名称：基于SURF的模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@roiVertices：模板图片的四个顶点对应在trainImg种位置，0-左上，1-右上，2-右下，3-左下点
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@tempHessianThreshold:模板特征点的Hessian阈值，值越大，特征点越小
//	@trainHessianThreshold:检测图片特征点的Hessian阈值，值越大，特征点越小
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配唯一的缺点是运算比较慢，但是是一个万能匹配算法，具备旋转不变性，尺度不变性，位移不变性等良好的特性
//  ②本算法考虑的图像的倾斜关系，所以输出来的4个顶点并不一定是矩形，可能是梯形，如果是二维平面变化，需要再用minAreaRect函数求解外接矩形
//=======================================================================================================================================
bool DM_matchTemplateFast_SURF(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<cv::Point2d> &roiVertices, double imgScale,
	double tempHessianThreshold, double trainHessianThreshold)
{

	if (tempImg_.empty() || trainImg_.empty())
	{
		return false;
	}
	if (imgScale <= 0)
	{
		imgScale = 1;
	}
	cv::Mat tempImg;
	cv::Mat trainImg;
    cv::resize(tempImg_, tempImg, cv::Size(tempImg_.cols / imgScale, tempImg_.rows / imgScale));
    cv::resize(trainImg_, trainImg, cv::Size(trainImg_.cols / imgScale, trainImg_.rows / imgScale));

    std::vector<cv::Point2d> vertices;
	if (DM_matchTemplateBase_SURF(tempImg, trainImg, vertices, tempHessianThreshold, trainHessianThreshold))
	{
		//调整透视变化矩阵
        roiVertices.push_back(cv::Point2d(vertices[0].x*imgScale, vertices[0].y*imgScale));
        roiVertices.push_back(cv::Point2d(vertices[1].x*imgScale, vertices[1].y*imgScale));
        roiVertices.push_back(cv::Point2d(vertices[2].x*imgScale, vertices[2].y*imgScale));
        roiVertices.push_back(cv::Point2d(vertices[3].x*imgScale, vertices[3].y*imgScale));

#ifdef DM_Dubeg_Mode
		cv::Mat dst;
        cv::cvtColor(trainImg_, dst, cv::COLOR_GRAY2BGR);
        cv::line(dst, cv::Point(roiVertices[0].x, roiVertices[0].y), cv::Point(roiVertices[1].x, roiVertices[1].y), cv::Scalar(0, 0, 255), 1);
        cv::line(dst, cv::Point(roiVertices[1].x, roiVertices[1].y), cv::Point(roiVertices[2].x, roiVertices[2].y), cv::Scalar(0, 0, 255), 1);
        cv::line(dst, cv::Point(roiVertices[2].x, roiVertices[2].y), cv::Point(roiVertices[3].x, roiVertices[3].y), cv::Scalar(0, 0, 255), 1);
        cv::line(dst, cv::Point(roiVertices[3].x, roiVertices[3].y), cv::Point(roiVertices[0].x, roiVertices[0].y), cv::Scalar(0, 0, 255), 1);
#endif
		return true;
	}
	else
	{
		return false;
	}

}




//=======================================================================================================================================
//函数名称：基于opencv模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@pos: x,y分别表示匹配点的位置，z表示匹配点的得分系数
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@maskImg：匹配掩膜
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配算法只使用于工件有定位，图片只存在普通的平通状态，实用该算法。如果在该条件下，匹配算法的精度、效率均远高于特征点匹配，故
//=======================================================================================================================================
bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, cv::Point3d &pos,double imgScale,cv::Mat maskImg)
{

	if (tempImg_.empty() || trainImg_.empty())
	{
		return false;
	}
	if (imgScale <= 0)
	{
		imgScale = 1;
	}
	cv::Mat tempImg;
	cv::Mat trainImg;
    cv::resize(tempImg_, tempImg, cv::Size(tempImg_.cols / imgScale, tempImg_.rows / imgScale));
    cv::resize(trainImg_, trainImg, cv::Size(trainImg_.cols / imgScale, trainImg_.rows / imgScale));

	cv::Mat resImg;
    cv::matchTemplate(trainImg, tempImg, resImg, cv::TM_SQDIFF, maskImg);

    cv::normalize(resImg, resImg, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

	double minVal = -1;
	double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    cv::Point matchLoc;
    cv::minMaxLoc(resImg, &minVal, &maxVal, &minLoc, &maxLoc);
	matchLoc = minLoc;
    pos = cv::Point3d(minLoc.x*imgScale, minLoc.y*imgScale, abs(minVal));
	cv::Mat dst;
    cv::cvtColor(trainImg, dst, cv::COLOR_GRAY2BGR);
    cv::rectangle(dst, matchLoc, cv::Point(matchLoc.x + tempImg.cols, matchLoc.y + tempImg.rows), cv::Scalar(0, 255, 0), 2, 8, 0);
}

//将src旋转angle之后得到dst
//angle：弧度
void getRotateImage(cv::Mat &src,cv::Mat &dst, float angle)
{
	//float radian = (float)(angle / 180.0 * CV_PI);

	//填充图像
    int maxBorder = (int)(cv::max(src.cols, src.rows)* 1.414); //即为sqrt(2)*max
	int dx = (maxBorder - src.cols) / 2;
	int dy = (maxBorder - src.rows) / 2;
    cv::copyMakeBorder(src, dst, dy, dy, dx, dx, cv::BORDER_CONSTANT);

	//旋转
    cv::Point2f center((float)(dst.cols / 2), (float)(dst.rows / 2));
    cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle*DM_180_PI, 1.0);//求得旋转矩阵
    cv::warpAffine(dst, dst, affine_matrix, dst.size());

	//计算图像旋转之后包含图像的最大的矩形
	float sinVal = abs(sin(angle));
	float cosVal = abs(cos(angle));
    cv::Size targetSize((int)(src.cols * cosVal + src.rows * sinVal),
		(int)(src.cols * sinVal + src.rows * cosVal));

	//剪掉多余边框
	int x = (dst.cols - targetSize.width) / 2;
	int y = (dst.rows - targetSize.height) / 2;
    cv::Rect rect(x, y, targetSize.width, targetSize.height);
    dst = cv::Mat(dst, rect);
}

//=======================================================================================================================================
//函数名称：基于opencv模板匹配函数
//函数参数说明：
//  @tempImg_：模板图片
//  @trainImg_：被检测图片
//	@roiVertices：模板图片的四个顶点对应在trainImg种位置，0-左上，1-右上，2-右下，3-左下点
//	@imgScale:为了提高匹配的运行速度，可以调整图像的姜维系数，系数越大，运算越快，但是匹配的精度也会越低
//	@startAngle:模板特征点的个数（单位弧度），默认为0，不旋转
//	@endtAngle：:检测图片特征点的个数（单位弧度），默认为0，不旋转
//	@AnglePrecision：角度细分精度，默认0.0087弧度，转化成角度就是0.5°
//返回值：计算完成返回true，计算失败返回fasle；
//特殊说明：
//	①该匹配算法如果用于有旋转的情况，计算料率非常低，不建议使用。如果模板和被测图像之间只有平移关系，用该算法会比用特征点匹配更加精准，效率更高。如果只有平移则
//    直接调用bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, cv::Point3d &pos, double imgScale = 2,cv::Mat maskImg = cv::Mat());
//=======================================================================================================================================
bool DM_matchTemplate_General(cv::Mat tempImg_, cv::Mat trainImg_, std::vector<cv::Point2d> &roiVertices, double imgScale,
	                          double startAngle, double endtAngle,double anglePrecision)
{
	if (tempImg_.empty() || trainImg_.empty())
	{
		return false;
	}
	if (imgScale <= 0)
	{
		imgScale = 1;
	}
	if (anglePrecision <= 0)//默认精度为0.5°
	{
		anglePrecision = 0.5 / DM_180_PI;
	}
	cv::Mat tempImg;
	cv::Mat trainImg;
    cv::resize(tempImg_, tempImg, cv::Size(tempImg_.cols / imgScale, tempImg_.rows / imgScale));
    cv::resize(trainImg_, trainImg, cv::Size(trainImg_.cols / imgScale, trainImg_.rows / imgScale));


	int calNum = abs(endtAngle - startAngle) / anglePrecision;
    std::vector<cv::Point3d> pos;
	for (int i = 0; i <= calNum; i++)
	{
		cv::Mat rotateTempImg;
		getRotateImage(tempImg, rotateTempImg, (startAngle + anglePrecision*i));
		//计算模板
		//定义变量
        std::vector<std::vector<cv::Point>>contours;
        std::vector<cv::Vec4i>hierarchy;
		cv::Mat rotateTempImgB = rotateTempImg > 0;
        cv::findContours(rotateTempImgB, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		//绘制轮廓图
		cv::Mat tempImgmask = cv::Mat::zeros(rotateTempImgB.size(), CV_8UC1);
        cv::drawContours(tempImgmask, contours, -1, cv::Scalar(255), CV_FILLED, cv::LINE_AA, hierarchy);

		cv::Point3d  posTemp;
		DM_matchTemplate_General(rotateTempImg, trainImg, posTemp,1,tempImgmask);
		pos.push_back(posTemp);
        std::cout << "旋转角度" << startAngle + anglePrecision * i << "后的匹配结果：" << posTemp << std::endl;
	}
	//仿射变化得到模板图片
	int minIndex = 0;
    cv::Point3d  minPos;
	if (pos.empty())
	{
		return false;
	}
	else if (pos.size() <= 1)
	{
		minPos = pos[0];
		minIndex = 0;

		roiVertices.clear();
        roiVertices.push_back(cv::Point2d(minPos.x*imgScale, minPos.y*imgScale));
        roiVertices.push_back(cv::Point2d(minPos.x*imgScale + tempImg_.cols, minPos.y *imgScale));
        roiVertices.push_back(cv::Point2d(minPos.x*imgScale + tempImg_.cols, minPos.y *imgScale + tempImg_.rows));
        roiVertices.push_back(cv::Point2d(minPos.x*imgScale, minPos.y *imgScale + tempImg_.rows));


#ifdef DM_Dubeg_Mode
		cv::Mat dst;
        cv::cvtColor(trainImg_, dst, cv::COLOR_GRAY2BGR);
        cv::line(dst, cv::Point(roiVertices[0].x, roiVertices[0].y), cv::Point(roiVertices[1].x, roiVertices[1].y), cv::Scalar(0, 255, 0), 1);
        cv::line(dst, cv::Point(roiVertices[1].x, roiVertices[1].y), cv::Point(roiVertices[2].x, roiVertices[2].y), cv::Scalar(0, 255, 0), 1);
        cv::line(dst, cv::Point(roiVertices[2].x, roiVertices[2].y), cv::Point(roiVertices[3].x, roiVertices[3].y), cv::Scalar(0, 255, 0), 1);
        cv::line(dst, cv::Point(roiVertices[3].x, roiVertices[3].y), cv::Point(roiVertices[0].x, roiVertices[0].y), cv::Scalar(0, 255, 0), 1);
#endif
	}
	else
	{
		minPos = pos[0];
		minIndex = 0;
		for (int i = 0; i < pos.size(); i++)
		{
			if (pos[i].z < minPos.z)
			{
				minPos = pos[i];
				minIndex = i;
			}
		}

		double angle = startAngle + anglePrecision * minIndex;
		cv::Mat rotateTempImg;
		getRotateImage(tempImg, rotateTempImg, angle);
        cv::Point2f center = cv::Point2f(minPos.x + rotateTempImg.cols / 2, minPos.y + rotateTempImg.rows / 2);
        cv::RotatedRect rect = cv::RotatedRect(center, cv::Size2f(tempImg.cols, tempImg.rows ), -angle * DM_180_PI);

        cv::Point2f rectVertices[4];
		rect.points(rectVertices);
		roiVertices.clear();
        roiVertices.push_back( cv::Point2d(rectVertices[1].x*imgScale, rectVertices[1].y*imgScale));
        roiVertices.push_back( cv::Point2d(rectVertices[2].x*imgScale, rectVertices[2].y*imgScale));
        roiVertices.push_back( cv::Point2d(rectVertices[3].x*imgScale, rectVertices[3].y*imgScale));
        roiVertices.push_back( cv::Point2d(rectVertices[0].x*imgScale, rectVertices[0].y*imgScale));
#ifdef DM_Dubeg_Mode
		cv::Mat dst;
        cv::cvtColor(trainImg_, dst, cv::COLOR_GRAY2BGR);
        cv::line(dst, cv::Point(roiVertices[0].x, roiVertices[0].y), cv::Point(roiVertices[1].x, roiVertices[1].y), cv::Scalar(0, 255, 0), 1);
        cv::line(dst, cv::Point(roiVertices[1].x, roiVertices[1].y), cv::Point(roiVertices[2].x, roiVertices[2].y), cv::Scalar(0, 255, 0), 1);
        cv::line(dst, cv::Point(roiVertices[2].x, roiVertices[2].y), cv::Point(roiVertices[3].x, roiVertices[3].y), cv::Scalar(0, 255, 0), 1);
        cv::line(dst, cv::Point(roiVertices[3].x, roiVertices[3].y), cv::Point(roiVertices[0].x, roiVertices[0].y), cv::Scalar(0, 255, 0), 1);
#endif

	}
	return  true;
}
