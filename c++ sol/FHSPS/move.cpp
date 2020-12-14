#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int n = 8;
char a[n][n], b[n][n];
int k;
pi p[2];

string val(pi x){
    string ret(2, ' ');
    ret[0] = 'A' + x.s, ret[1] = '8' - x.f;
    return ret;
}

void answer(){
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++) cin >> a[i][j];
	
	k = 0;
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
	    cin >> b[i][j];
	    if(a[i][j] != b[i][j]) p[k++] = {i, j};
	}
	
	if(b[p[0].f][p[0].s] != '.') swap(p[0], p[1]);
	cout << val(p[0]) << "-" << val(p[1]) << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}