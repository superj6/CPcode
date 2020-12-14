#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int n = 4 * 12 * 60;
int a[n];
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	for(int t = 0; t < 2; t++){
	    int m;
	    cin >> m;
	    for(int i = 0; i < m; i++){
	        int x;
	        cin >> x;
	        x--;
	        a[x] += 2 * t - 1;
	    }
	}
	
	int ret1 = 0, ret2 = 0;
	for(int i = 0, j = 0, l = -1; i < n; i++){
	    if(!!a[i]){
	        ret1 += (i < n / 2);
	        if(!j){
	            ret2 += l != -1 && l != (a[i] > 0);
	            l = a[i] > 0;
	        }
	        j += a[i];
	    }
	}
	
	cout << ret1 << endl;
	cout << ret2 << endl;
 
	return 0;
}