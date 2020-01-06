#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>

struct line{
	long long x, y, X, Y;
	
	friend bool operator<(line a, line b){
		if(a.x > b.x){
			return (a.y - b.y) * (b.X - b.x) > (b.Y - b.y) * (a.x - b.x);
		}else{
			return (b.y - a.y) * (a.X - a.x) < (a.Y - a.y) * (b.x - a.x);
		}
	}
};

struct cmp{
	bool operator()(line a, line b){
		return (pi){a.x, a.y} < (pi){b.x, b.y};
	}
};

const int maxn = 200000;
int n;
line a[maxn];

int main(){
	freopen("hillwalk.in", "r", stdin);
	freopen("hillwalk.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i].x >> a[i].y >> a[i].X >> a[i].Y;
		a[i + n] = {a[i].X, a[i].Y, a[i].x, a[i].y};
	}
	
	sort(a, a + 2 * n, cmp());
	
	int ret = 1;
	line cur = a[0];
	set<line> st;
	st.insert(cur);
	for(int i = 1; i < 2 * n; i++){
		if(cur.X < a[i].x){
			if(st.upper_bound(cur) == st.end()) break;
			cur = *st.upper_bound(cur);
			ret++;
		}
		
		if(a[i].x < a[i].X) st.insert(a[i]);
		else st.erase((line){a[i].X, a[i].Y, a[i].x, a[i].y});
	}
	
	cout << ret << endl;
	
	return 0;
}