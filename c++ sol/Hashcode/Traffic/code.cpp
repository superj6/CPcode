#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100001, k = 500;
int D, I, S, V, F;
int B[mxn], E[mxn], L[mxn], q[mxn], vis[mxn], d[mxn];
string streetName[mxn];
vector<int> g[mxn], carPaths[mxn];
vector<pi> lightTimes[mxn], carTimes[mxn];
map<string, int> streetIndex;

int main(){
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
  cin >> D >> I >> S >> V >> F;

  for(int i = 0; i < S; i++){
    cin >> B[i] >> E[i] >> streetName[i] >> L[i];
    g[E[i]].push_back(i);
    streetIndex[streetName[i]] = i;
  }

  for(int i = 0; i < V; i++){
    int P;
    cin >> P;
    for(int j = 0; j < P; j++){
      string name;
      cin >> name;
      carPaths[i].push_back(streetIndex[name]);
    }
    carTimes[q[carPaths[i][0]]++].push_back({i, 0});
  }

  for(int i = 0; i < I; i++){
	lightTimes[i].push_back({-1, -1});	
  }
  
  for(int i = 0; i < D; i++){
  	for(int j = 0; j < I; j++){
  		int best = -1;
  		for(int l : g[j]){ 
  			d[l] += q[l];
  			if(lightTimes[j].back().s < k && (!vis[l] || l == lightTimes[j].back().f) && q[l]){
  				if(!~best || q[l] > q[best]) best = l;
  			}
  		}
  		if(~best){
  			if(best == lightTimes[j].back().f){
  				lightTimes[j].back().s += (k + i) / k;
  			}else{
  				vis[best] = 1;
  				lightTimes[j].push_back({best, lightTimes[j].back().s + (k + i) / k});
  			}
  		}
  	}
    for(pi j : carTimes[i]){
      q[carPaths[j.f][j.s]]--;
    }
    for(pi &j : carTimes[i]){
      if(++j.s == carPaths[j.f].size() - 1) continue;
      carTimes[i + 1 + L[carPaths[j.f][j.s]] + q[carPaths[j.f][j.s]]++ + i / k].push_back(j);
    }
  }
  
  int ret = 0;
  for(int i = 0; i < I; i++){
  	int totalTime = lightTimes[i].back().s + 1;
  	for(int j = lightTimes[i].size() - 1; j; j--){
	  lightTimes[i][j].s -= lightTimes[i][j - 1].s;
	}
	for(int j : g[i]) if(!vis[j] && d[j]){
	  vis[j] = 1;
	  lightTimes[i].push_back({j, 1});
	  totalTime++;
	}
	while(totalTime > D){
		bool anyChange = 0;
		for(int j = lightTimes[i].size() - 1; j && totalTime > D; j++){
			if(lightTimes[i][j].s > 1){
				anyChange = 1;
				totalTime--;
				lightTimes[i][j].s--;
			}
		}
		if(!anyChange){
			while(totalTime > D){
				totalTime--;
				lightTimes[i].pop_back();
			}
		}
	}
	ret += !!totalTime;
  }
  
  cout << ret << endl;
  for(int i = 0; i < I; i++) if(~-lightTimes[i].size()){
  	cout << i << endl;
	cout << (lightTimes[i].size() - 1) << endl;
	for(int j = 1; j < lightTimes[i].size(); j++){
	  cout << streetName[lightTimes[i][j].f] << " " << lightTimes[i][j].s << endl;
	}
  }
	
  return 0;
}