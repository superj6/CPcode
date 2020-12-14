#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000001;
int n, q;
int a[mxn], s[mxn];
int ret, f, t;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++){
		char c;
		cin >> c;
		a[i] = 1 + (c == 'T');
		s[i] = a[i] + s[i - 1];
		if(!~-a[i]) ret = s[i], f = i;
	}
	
	reverse(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) s[i] = a[i] + s[i - 1];
	int cur = n;
	while(~-a[cur] && cur) cur--;
	if(s[cur] > ret){
		ret = s[cur], f = cur, t = 1;
	}else{
		reverse(a + 1, a + n + 1);
		for(int i = 1; i <= n; i++) s[i] = a[i] + s[i - 1];
	}
	
	while(q--){
		int x, l, r;
		cin >> x;
		if(x <= ret){
			l = upper_bound(s, s + n + 1, ret - x) - s;
			r = f - (s[l - 1] != ret - x);
		}else if(x <= s[n] && (x & 1) == (s[n] & 1)){
			l = 1;
			r = lower_bound(s, s + n + 1, x) - s;
		}else{
			cout << "NIE" << endl;
			continue;
		}
		if(t){
			swap(l, r);
			l = n - l + 1, r = n - r + 1;
		}
		cout << l << " " << r << endl;
	}

	return 0;
}