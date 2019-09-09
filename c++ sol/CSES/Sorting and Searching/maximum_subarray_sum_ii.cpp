#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'

struct minstack{
	stack<pair<long, long>> s1, s2;
	
	minstack(){}
	
	void add(long x){
		s1.push(make_pair(x, s1.empty() ? x : min(x, s1.top().second)));
	}
	
	void del(){
		if(s2.empty()){
			while(!s1.empty()){
				s2.push(make_pair(s1.top().first, s2.empty() ? s1.top().first : min(s1.top().first, s2.top().second)));
				s1.pop();
			}
		}
		
		s2.pop();
	}
	
	long minv(){
		if(s1.empty() || s2.empty()) return !s1.empty() ? s1.top().second : s2.top().second;
		
		return min(s1.top().second, s2.top().second);
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, a, b;
	cin >> n >> a >> b;
	
	a--, b--;
	
	long ar[n];
	long maxv = -200000000000007;
	minstack stk;
	stk.add(0);
	
	for(int i = 0; i < n; i++){
		cin >> ar[i];
		if(i > 0) ar[i] += ar[i - 1];
		
		if(i >= a){
			maxv = max(maxv, ar[i] - stk.minv());
			stk.add(ar[i - a]);
		} 
		
		if(i >= b) stk.del();
	}
	
	cout << maxv << endl;

	return 0;
}