#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n, k;
vector<pi> v, ans;
int ret = 0, cnt = 0;

void solve(){
    if(v.size() > ret){
        ret = v.size();
        cnt = 0;
    }
    if(v.size() == ret){
        if(++cnt == k) ans = v;
    }
    
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
        pi p = {i, j};
        if(v.empty() || p > v.back()){
            bool t = 1;
            for(pi x : v){
                t &= abs(p.f - x.f) != abs(p.s - x.s);
            }
            if(t){
                v.push_back(p);
                solve();
                v.pop_back();
            } 
        }
    }
}

void answer(){
	cin >> n >> k;
	
	solve();
	
	cout << ret << endl;
	for(pi i : ans) cout << i.f + 1 << " " << i.s + 1 << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}