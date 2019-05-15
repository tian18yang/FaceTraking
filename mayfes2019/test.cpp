#include <iostream>
#include <string>
using namespace std;
int main(){
	int a = 123;
	string b = to_string(a);
	cout << b.c_str()[0]  << endl;
//	cout << '1'==b.c_str()[0] <<endl;
}
