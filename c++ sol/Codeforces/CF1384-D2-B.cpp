/*
  You can always wait and move forward as much as possible in tide positions, so you want to be as early on in the decreasing section
as possible. Iterate through highest and keep track of how far back you can be, and you must forward one tide position every time and
then make also make sure you are compliant with the depth limit, but if the depth limit is higher than the tide height you can go back
to the beginning of the tide positions.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n, m, k;

void answer(){
	cin >> n >> m >> k;
	
	bool t = 1;
	for(int i = 0, j = m; i < n; i++){
		int x;
		cin >> x;
		if(!t) continue;
		
		x = k - x;
		if(x < 0 || -(--j) > x) t = 0;
		else if(x >= m) j = m;
		else j = min(j, x);
	} 
	
	cout << (t ? "YES" : "NO") << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
