/*
  When all given numbers are distinct, which they are in problem, there is always an answer. This means you can solve each
dimension independently. If you had a sorted array, you could always alternate by going in increasing order flipping signs, while
you could always stay on the same side near the origin by going in decreasing order flipping signs. This means you can count the
number of times the the signs stay the same, and split the array at the index of that count, and whenever you are going across
an axis you go in increasing order on the right array otherwise you go in decreasing order on the left array. This ensure you
always stay in one side when you want to close to the origin, but when you want to swap sides the array numbers on the right will
always be greater than those on the left so it will be large enough to swap sides.
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

const int mxn = 10000;
int n;
int a[2][mxn], s[2][mxn];
int l[2], r[2];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < n; i++) cin >> a[t][i];
		sort(a[t], a[t] + n);
	}
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		for(int t = 0; t < 2; t++){
			s[t][i] = 2 * (!~-x || x == (1 << (2 - t))) - 1;
			l[t] += (i && s[t][i] == s[t][i - 1]);
		}
	}
	
	for(int t = 0; t < 2; t++) r[t] = l[t]--;
	
	for(int i = 0; i < n; i++)
	for(int t = 0; t < 2; t++){
		int x;
		if(!i || s[t][i] != s[t][i - 1]) x = (a[t][r[t]] *= s[t][i]), r[t]++;
		else x = (a[t][l[t]] *= (2 * (a[t][l[t] + 1] < 0) - 1)), l[t]--;
		cout << (x > 0 ? '+' : '-') << abs(x) << (t ? endl : ' ');
	}

	return 0;
}
