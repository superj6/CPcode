#include <iostream>
#include <random>
#include <time.h>
using namespace std;
#define endl '\n'
 
int main(){
	srand(time(0));
 
	int n = 30;
	for(int i = 0; i < n; i++){
		cout << (rand() & 0xf) << endl;
	}
}
