#include <iostream>
using namespace std;
int main(){
	int a=1;
	char A = (unsigned char)a;
	cout << A << endl;
	int b = (int)A;
	cout << b << endl;
	cout << (unsigned char)((char)2+1) << endl;
}
