/*
  NAME: super_j6
  LANG: C++
  PROG: bookshelf
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

template <typename T>
struct minstack{
	stack<pair<T, T>> stk;
	
	T top(){
		return stk.top().first;
	}
	
	T minv(){
		return stk.empty() ? T() : stk.top().second;
	}
	
	void push(T x){
		stk.push({x, min(x, stk.empty() ? x : minv())});
	}
	
	void pop(){
		stk.pop();
	}
	
	bool empty(){
		return stk.empty();
	}
	
	int size(){
		return stk.size();
	}
};

template <typename T>
struct mindeque{
	minstack<T> l, m, r;
	
	void mov_front(){
		if(r.empty()){
			while(m.size() + 1 < l.size()) m.push(l.top()), l.pop();
			while(!l.empty()) r.push(l.top()), l.pop();
			while(!m.empty()) l.push(m.top()), m.pop();
		}
	}
	
	void mov_back(){
		if(l.empty()){
			while(m.size() + 1 < r.size()) m.push(r.top()), r.pop();
			while(!r.empty()) l.push(r.top()), r.pop();
			while(!m.empty()) r.push(m.top()), m.pop();
		}
	}
	
	T front(){
		mov_front();
		return r.top();
	}
	
	T back(){
		mov_back();
		return l.top();
	}
	
	T minv(){
		if(l.empty()) return r.minv();
		if(r.empty()) return l.minv();
		return min(l.minv(), r.minv());
	}
	
	void push_front(T x){
		r.push(x);
	}
	
	void push_back(T x){
		l.push(x);
	}
	
	void pop_front(){
		mov_front();
		r.pop();
	}
	
	void pop_back(){
		mov_back();
		l.pop();
	}
	
	bool empty(){
		return l.empty() && r.empty();
	}
	
	int size(){
		return l.size() + r.size();
	}
};

const int maxn = 100001;
long long n, l;
long long h[maxn], w[maxn], dp[maxn];
mindeque<long long> dq, dqv;

int main(){
	freopen("bookshelf.in", "r", stdin);
	freopen("bookshelf.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> l;
	
	for(int i = 1; i <= n; i++){
		cin >> h[i] >> w[i];
		if(i) w[i] += w[i - 1];
	}

	for(int i = 1, j = 0; i <= n; i++){
		while(!dq.empty() && h[dq.front()] <= h[i]) dq.pop_front(), dqv.pop_front();
		dqv.push_front((dq.empty() ? dp[i - 1] : dp[dq.front()]) + h[i]);
		dq.push_front(i);
		
		while(w[i] - w[j] > l) j++;
		while(dq.back() <= j){
			dq.pop_back();
			dqv.pop_back();
			dqv.pop_back();
			dqv.push_back(dp[dq.back() - 1] + h[dq.back()]);
		}
		
		dp[i] = min(dqv.minv(), dp[j] + h[dq.back()]);
	}
	
	cout << dp[n] << endl;

	return 0;
}