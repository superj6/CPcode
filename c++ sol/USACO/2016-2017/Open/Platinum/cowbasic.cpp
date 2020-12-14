#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <stack>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int maxn = 101;
int n = 1;

struct M{
	ll m[maxn][maxn];
	
	M(){
		memset(m, 0, sizeof(m));
	}
	
	static M I(){
		M ret;
		for(int i = 0; i < maxn; i++) ret.m[i][i] = 1;
		return ret;
	}
	
	friend M operator*(M a, M b){
		M ret;
		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		for(int k = 0; k < n; k++){
			(ret.m[i][j] += a.m[i][k] * b.m[k][j] ) %= mod;
		}
		return ret;
	}
	
	M pow(int e){
		M ret = I(), b;
		memcpy(b.m, m, sizeof(m));
		for(; e; e >>= 1){
			if(e & 1) ret = ret * b;
			b = b * b;
		}
		return ret;
	}
};

stack<pair<M, int>> stk;
string s;
map<string, int> mp;

bool f(string x, string y){
	return x.find(y) != string::npos;
}

int main(){
	freopen("cowbasic.in", "r", stdin);
	freopen("cowbasic.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	stk.push({M::I(), 1});
	
	for(getline(cin, s); !f(s, "RETURN"); getline(cin, s)){
		stringstream ss(s);
		
		if(f(s, "MOO")){
			int x;
			ss >> x;
			stk.push({M::I(), x});
		}else{
			M ret;
			if(f(s, "=")){
				int x;
				string v;
				ss >> v;
				if(mp.find(v) == mp.end()) mp[v] = n++;
				x = mp[v];
				
				ret = M::I();
				ret.m[x][x] = 0;
				
				while(ss >> v){
					if(mp.find(v) != mp.end()){
						ret.m[x][mp[v]]++;
					}else if('0' <= v[0] && v[0] <= '9'){
						ret.m[x][0] += stoi(v);
					}
				}
			}else{
				ret = stk.top().f.pow(stk.top().s);
				stk.pop();
			}
			stk.top().f = ret * stk.top().f;
		}
	}
	
	cout << stk.top().f.m[mp[s.substr(7, s.size() - 7)]][0] << endl;
	
	return 0;
}