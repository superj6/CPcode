#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long maxn = 100000000000;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
    for(long long i = 0; i < maxn; i++){
        int x = 0;
        x++;
        x--;
        x++;
        x--;
        x += ++x & ++x;
    }

    cout << "finally" << endl;

	return 0;
}