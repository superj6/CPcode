#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 100000;
int n;
int a[4][maxn];
int s[maxn];
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int t = 0; t < 4; t++)
	for(int i = 0; i < n; i++){
	    cin >> a[t][i];
	}
	
	for(int tt = 0; tt < 4; tt++){
	    if(tt < 2) for(int i = 0; i < n; i++){
	        if(a[0][i] + a[1][i] >= n || !~a[0][i] ^ !~a[1][i]){
	            cout << "NE" << endl;
	            return 0;
	        }
	    }
	    for(int t = 0; t < 2; t++){
	        memset(s, 0x3f, sizeof(s));
	        for(int i = n - 1; ~i; i--){
	            if(~a[2][i]) s[a[2][i]] = i;
	        }
	        for(int i = 0; i < n; i++){
	            if(s[i] < a[0][i]){
	                cout << "NE" << endl;
	                return 0;
	            }
	        }
	        swap(a[2], a[3]);
	        reverse(a[0], a[0] + n);
	    }
	    swap(a[0], a[2]);
	    swap(a[2], a[1]);
	    swap(a[1], a[3]);
	    reverse(a[0], a[0] + n);
	    reverse(a[1], a[1] + n);
	}
	
	cout << "DA" << endl;
 
	return 0;
}