#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
#include <stack>
#include <deque>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
typedef array<deque<int>, 2> T;
 
const int mod = 1000000007;
const int mxn = 1000001;
int n;
pi a[mxn];
stack<T> stk;
 
inline int f(int x){
	return stk.top()[x].empty() ? 2 * n + 2 : stk.top()[x].front();
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i].f >> a[i].s;
	a[n] = {2 * n + 1, 2 * n + 1};
	
	sort(a, a + n);
	
	int ret = 1;
	for(int i = 0; i <= n; i++){
		while(!stk.empty()){
			for(int j = 0; j < 2; j++){
				while(f(j) < a[i].f) stk.top()[j].pop_front();
			}
			if(f(0) > f(1)) swap(stk.top()[0], stk.top()[1]);
			if(!stk.top()[0].empty()) break;
			stk.pop(), (ret *= 2) %= mod;
		}
		if(stk.empty() || a[i].s < f(0)){
			stk.push(T());
			stk.top()[0].push_front(a[i].s);
		}else{
			while(stk.size() > 1 && stk.top()[1].empty()){
				T x;
				swap(stk.top(), x);
				stk.pop();
				if(a[i].s < f(0)){
					stk.push(T());
					swap(stk.top(), x);
					break;
				}
				if(x[0].size() < stk.top()[0].size()){
					while(!x[0].empty()){
						stk.top()[0].push_front(x[0].back());
						x[0].pop_back();
					}
				}else{
					swap(x[0], stk.top()[0]);
					while(!x[0].empty()){
						stk.top()[0].push_back(x[0].front());
						x[0].pop_front();
					}
				}
			}
			if(a[i].s > f(1)){
				ret = 0;
				break;
			}
			stk.top()[1].push_front(a[i].s);
		}
	}
	
	cout << ret << endl;
 
	return 0;
}
