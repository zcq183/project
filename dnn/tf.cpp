
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

#include "opencv2/opencv.hpp"

#include "opencv2/dnn/dnn.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;
 
const size_t inWidth = 300;
const size_t inHeight = 300;
const float WHRatio = inWidth / (float)inHeight;
const char* classNames[] = { "background","face" };//这个需要根据训练的类别定义
 
int main() { 
	Mat frame = cv::imread("./t.jpg");
	Size frame_size = frame.size();
 
 
	String weights = "/home/gang/project/models/ssd/frozen_inference_graph.pb";
	String prototxt = "/home/gang/project/models/ssd/pipeline.config";

	cout<<weights<<endl;

	dnn::Net net = cv::dnn::readNetFromTensorflow(weights, prototxt);

	//const string model ;
	  //dnn::Net net2 =  cv::dnn::readNetFromTensorflow(model);
 
	Size cropSize;
	if (frame_size.width / (float)frame_size.height > WHRatio)
	{
		cropSize = Size(static_cast<int>(frame_size.height * WHRatio),
			frame_size.height);
	}
	else
	{
		cropSize = Size(frame_size.width,
			static_cast<int>(frame_size.width / WHRatio));
	}
 
	Rect crop(Point((frame_size.width - cropSize.width) / 2,
		(frame_size.height - cropSize.height) / 2),
		cropSize);
 
 
	cv::Mat blob = cv::dnn::blobFromImage(frame, 1. / 255, Size(300, 300));
	//cout << "blob size: " << blob.size << endl;
 
	net.setInput(blob);
	Mat output = net.forward();
	//cout << "output size: " << output.size << endl;
 
	Mat detectionMat(output.size[2], output.size[3], CV_32F, output.ptr<float>());
 
	frame = frame(crop);
	float confidenceThreshold = 0.20;
	for (int i = 0; i < detectionMat.rows; i++)
	{
		float confidence = detectionMat.at<float>(i, 2);
 
		if (confidence > confidenceThreshold)
		{
			size_t objectClass = (size_t)(detectionMat.at<float>(i, 1));
 
			int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
			int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
			int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
			int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
 
			ostringstream ss;
			ss << confidence;
			String conf(ss.str());
 
			Rect object((int)xLeftBottom, (int)yLeftBottom,
				(int)(xRightTop - xLeftBottom),
				(int)(yRightTop - yLeftBottom));
 
			rectangle(frame, object, Scalar(0, 255, 0), 2);
			String label = String(classNames[objectClass]) + ": " + conf;
			int baseLine = 0;
			Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
			rectangle(frame, Rect(Point(xLeftBottom, yLeftBottom - labelSize.height),
				Size(labelSize.width, labelSize.height + baseLine)),
				Scalar(0, 255, 0), 2);
			putText(frame, label, Point(xLeftBottom, yLeftBottom),
				FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
		}
	}
	imshow("image", frame);
	waitKey(0);
	return 0;
}
