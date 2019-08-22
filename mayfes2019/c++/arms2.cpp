#include <iostream>
#include <cmath>
#include <unistd.h>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#define SERIAL_PORT "/dev/serial0"





using namespace cv;
using namespace std;

double radian=3.14159265/180.0;

vector<int> theta_to_phi(vector<int> theta){
	vector<int> phi(3);
	int theta1 = theta[0];
	int theta2 = theta[1];
	int theta3 = theta[2];
	phi[0] = theta1-theta2/2;
	phi[1] = theta2/2;
	phi[2] = theta3-theta1+theta2;
	return phi;
}

vector<int> phi_to_theta(vector<int> phi){
	vector<int> theta(3);
	int phi1 = phi[0];
	int phi2 = phi[1];
	int phi3 = phi[2];
	theta[0] = phi1+phi2;
	theta[1] = phi2*2;
	theta[2] = phi1-phi2+phi3;
	return theta;
}

vector<int> rthetaphi_facefromcamera(Rect face, int W, int H){
	//parameter
	int  parameter_r = 1;
	int parameter_x = 1;
	int parameter_y = 1;
	int face_size_goal = 100;

	int dx = face.x + face.width/2 - W;
	int dy = face.y + face.height/2 - H;
	int r = (face.width - face_size_goal) * parameter_r;
	int theta = dx * parameter_x;
	int phi = dy * parameter_y;
	int rtp[] = {r,theta,phi};
	vector<int> rthetaphi(rtp,rtp+3);
	return rthetaphi;
}


vector<double> face_position(vector<int> phi,vector<int> ffc,int theta4,double l){
	double x = 2*l*cos(phi[1]*radian)*sin(phi[0]*radian)*cos(theta4*radian)+ffc[0]*cos((phi[2]+ffc[2])*radian)*cos((ffc[1]+theta4)*radian);
	double y = 2*l*cos(phi[1]*radian)*sin(phi[0]*radian)*sin(theta4*radian)+ffc[0]*cos((phi[2]+ffc[2])*radian)*sin((ffc[1]+theta4)*radian);
	double z = 2*l*cos(phi[1]*radian)*cos(phi[0]*radian)+ffc[0]*sin((phi[2]+ffc[2])*radian);
	double face[] = {x,y,z};
	vector<double> fp(face,face+3);
	return fp;
}

vector<int> xyz_to_phi(double x,double y,double z,double l){
	int phi1 = atan(sqrt((x*x+y*y)/(z*z)));
	int phi2 = asin(sqrt(x*x+y*y+z*z)/(2*l));
	int phi3 = 0;
	int Phi[] = {phi1,phi2,phi3};
	vector<int> phi(Phi,Phi+3);
}



vector<int> best_camera_position(vector<double> fp,double d,double l,int ffc_phi){
	vector<int> theta(4);
	//vector<int> speed(4);
	double x=fp[0],y=fp[1],z=fp[2];
	double xydis = sqrt(x*x + y*y);
	if((xydis-d)*(xydis-d)+z*z > 4*l*l){
		theta[2] = atan(sqrt(x*x+y*y)/z);
		theta[1] = 180;
		theta[0] = 180-theta[2];
		theta[3] = atan(y/x);
	}else if((xydis-d)*(xydis-d)+z*z > d*d){
		theta[0] = 0;
		theta[1] = 0;
		theta[2] = atan(sqrt(x*x+y*y)/z);
		theta[3] = atan(y/x);
	}else{
		double X = x-x*d/xydis;
		double Y = y-y*d/xydis;
		vector<int> phi = xyz_to_phi(X,Y,z,l);
		phi[2]=ffc_phi;
		vector<int> theta123 = phi_to_theta(phi);
		theta[0] = theta123[0];
		theta[1] = theta123[1];
		theta[2] = theta123[2];
		theta[3] = atan(y/x);
	}
	return theta;
}







int main(){

	//parameter
	double l = 10;//arm lengtr
	int W = 640, H = 480;//framesize
	double d = l;//distance between camera and face
	int Theta[] = {45,90,45};
	int theta4 = 0;
	vector<int> theta(Theta,Theta);
	vector<int> phi = theta_to_phi(theta);

	unsigned char buf[255];
	int fd;                             // ファイルディスクリプタ
    	struct termios tio;                 // シリアル通信設定
    	int baudRate = B9600;

    	fd = open(SERIAL_PORT, O_RDWR);     // デバイスをオープンする
    	if (fd < 0) {
        	printf("open error\n");
        	return -1;
    	}

    	tio.c_cflag += CREAD;               // 受信有効
    	tio.c_cflag += CLOCAL;              // ローカルライン（モデム制御なし）
    	tio.c_cflag += CS8;                 // データビット:8bit
    	tio.c_cflag += 0;                   // ストップビット:1bit
    	tio.c_cflag += 0;                   // パリティ:None

    	cfsetispeed( &tio, baudRate );
    	cfsetospeed( &tio, baudRate );

    	cfmakeraw(&tio);                    // RAWモード

    	tcsetattr( fd, TCSANOW, &tio );     // デバイスに設定を行う

    	ioctl(fd, TCSETS, &tio);            // ポートの設定を有効にする



	while(1){
		Rect face;
		bool detected;
		//cin >> detected;
		if(detected==1){
			//cin >> face;
			vector<int> ffc = rthetaphi_facefromcamera(face,W,H);
			vector<double> fp = face_position(phi,ffc,theta4,l);
			vector<int> bcp = best_camera_position(fp,d,l,ffc[2]);
			bcp[4]+=90;
			for(int i=0;i<4;i++){
				char send[4];
				int Speed = 100;
				send[0] = 'H';
				send[1] = (unsigned char)i;
				send[2] = (unsigned char)bcp[i];
				send[3] = (unsigned char)Speed;
				write(fd,send,4);
				cout  << (int)send[1] << " : " << (int)send[2] << "  " << (int)send[3] << endl;
			}
			int len=0;
			char receive[1];
			for(int i=0;i<4;i++){
				int index;
				while(1){
					int l=read(fd,receive,1);
					if(l==0){
						usleep(100);
						continue;
					}
					if((int)receive[0]>200){
						index = (int)receive[0]-200;
					}
					if(index==4){
						theta4=(int)receive[0]-90;
						break;
					}
					theta[index] = (int)receive[0];
				}
			}
			cout << "theta:" <<theta[0] << " " << theta[1] << " " << theta[2] << " " << theta[3] << endl;
			phi = theta_to_phi(theta);
		}
	}
}
