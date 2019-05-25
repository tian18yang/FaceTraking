#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <typeinfo>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    Mat frame, gray; //USBカメラから得た１フレームを格納する場所
    CascadeClassifier cascade1, cascade2; //カスケード分類器格納場所
    cascade1.load("../opencv-master/data/haarcascades/haarcascade_frontalface_alt2.xml"); //正面顔情報が入っているカスケード
    cascade2.load("../opencv-master/data/haarcascades/haarcascade_profileface.xml"); //正面顔情報が入っているカスケード
    vector<Rect> faces1, faces2; //輪郭情報を格納場所

    VideoCapture cap(0); // USBカメラのオープン
    if(!cap.isOpened()) //カメラが起動できなかった時のエラー処理
    {
        return -1;
    }
//	cout << cap.get(CV_CAP_PROP_FRAME_WIDTH);

    while(1)//無限ループ
    {
        cap >> frame; //USBカメラが得た動画の１フレームを格納
	cvtColor(frame, gray, CV_RGB2GRAY);
        cascade1.detectMultiScale(gray, faces1, 1.1, 3, 0, Size(20, 20)); //格納されたフレームに対してカスケードファイルに基づいて顔を検知
        cascade2.detectMultiScale(gray, faces2, 1.1, 3, 0, Size(20, 20)); //格納されたフレームに対してカスケードファイルに基づいて顔を検知
	for(int i = 0; i<faces1.size(); i++) //検出した顔の個数"faces.size()"分ループを行う
        {
            rectangle(frame, Point(faces1[i].x, faces1[i].y), Point(faces1[i].x + faces1[i].width, faces1[i].y + faces1[i].height), Scalar(0, 0, 255), 3, CV_AA); //検出した顔を赤色矩形で囲む
        }
	for(int i = 0; i<faces2.size(); i++) //検出した顔の個数"faces.size()"分ループを行う
        {
            rectangle(frame, Point(faces2[i].x, faces2[i].y), Point(faces2[i].x + faces2[i].width, faces2[i].y + faces2[i].height), Scalar(0, 255, 0), 3, CV_AA); //検出した顔を赤色矩形で囲む
        }

        imshow("window", frame);//画像を表示．

        int key = waitKey(1);
        if(key == 113)//qボタンが押されたとき
        {
//	cout << frame.size(); 
//	cout << typeid(frame.size).name();
            break;//whileループから抜ける（終了）
        }
    }
    destroyAllWindows();
    return 0;
}
