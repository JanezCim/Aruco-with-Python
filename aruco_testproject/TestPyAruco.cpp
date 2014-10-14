#include <iostream>
#include <aruco/aruco.h>
#include <aruco/cvdrawingutils.h>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <sstream>
#include <boost/python.hpp>

using namespace cv;
using namespace aruco;

string TheInputVideo;
string TheIntrinsicFile;
float TheMarkerSize=-1;
int ThePyrDownLevel;
MarkerDetector MDetector;
VideoCapture TheVideoCapturer;
vector<Marker> TheMarkers;
Mat TheInputImage,TheInputImageCopy;
CameraParameters TheCameraParameters;
void cvTackBarEvents(int pos,void*);
bool readCameraParameters(string TheIntrinsicFile,CameraParameters &CP,Size size);

pair<double,double> AvrgTime(0,0) ;//determines the average time required for detection
double ThresParam1,ThresParam2;
int iThresParam1,iThresParam2;
int waitTime=0;


void Init(){
	int vIdx = 0;
	cout<<"Opening camera index "<<vIdx<<endl;
	TheVideoCapturer.open(vIdx);
	waitTime=10;
		
	TheVideoCapturer>>TheInputImage;

	//Create gui
        cv::namedWindow("thres",1);
        cv::namedWindow("in",1);
        MDetector.getThresholdParams( ThresParam1,ThresParam2);       
        MDetector.setCornerRefinementMethod(MarkerDetector::SUBPIX);
        iThresParam1=ThresParam1;
        iThresParam2=ThresParam2;
        cv::createTrackbar("ThresParam1", "in",&iThresParam1, 13, cvTackBarEvents);
        cv::createTrackbar("ThresParam2", "in",&iThresParam2, 13, cvTackBarEvents);
}



int yay()
{
	try{
		
	        char key=0;
	        //capture until press ESC or until the end of the video
	        do{
			TheVideoCapturer.retrieve( TheInputImage);

			//Detection of markers in the image passed
            		MDetector.detect(TheInputImage,TheMarkers,TheCameraParameters,TheMarkerSize);
			
			//cout<<TheMarkers.size()<< std::flush;
			
			//print marker info and draw the markers in image
            		TheInputImage.copyTo(TheInputImageCopy);
	

			for (unsigned int i=0;i<TheMarkers.size();i++) {
                		TheMarkers[i].draw(TheInputImageCopy,Scalar(0,0,255),1);
            		}









			cv::imshow("in",TheInputImageCopy);
			cv::imshow("thres",MDetector.getThresholdedImage());

			key=cv::waitKey(waitTime);//wait for key to be pressed
		}while(key!=27 && TheVideoCapturer.grab());
		
		cv::destroyAllWindows();

		return TheMarkers.size();
	

	} 
	catch (std::exception &ex){
	        cout<<"Exception :"<<ex.what()<<endl;
		cv::destroyAllWindows();
		return 0;
	}
}




void cvTackBarEvents(int pos,void*)
{
    if (iThresParam1<3) iThresParam1=3;
    if (iThresParam1%2!=1) iThresParam1++;
    if (ThresParam2<1) ThresParam2=1;
    ThresParam1=iThresParam1;
    ThresParam2=iThresParam2;
    MDetector.setThresholdParams(ThresParam1,ThresParam2);
//recompute
    MDetector.detect(TheInputImage,TheMarkers,TheCameraParameters);
    TheInputImage.copyTo(TheInputImageCopy);
    for (unsigned int i=0;i<TheMarkers.size();i++)	TheMarkers[i].draw(TheInputImageCopy,Scalar(0,0,255),1);
    cv::imshow("in",TheInputImageCopy);
    cv::imshow("thres",MDetector.getThresholdedImage());
}






BOOST_PYTHON_MODULE(libTestPyAruco)
{
  using namespace boost::python;
  def("yay", yay);
  def("Init", Init);
}
