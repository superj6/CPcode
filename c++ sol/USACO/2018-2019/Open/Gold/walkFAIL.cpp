#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'

const long long a = 2019201913, b = 2019201949, mod = 2019201997;

int parent[7500], rankf[7500];

int find(int x){
    return parent[x] == x ? x : find(parent[x]);
}

int main(){
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;
	
	for(int i = 0; i < n; i++){
	    parent[i] = i;
	    rankf[i] = 0;
	    for(int j = i + 1; j < n; j++){
	        pq.push(make_pair((a * (i + 1) + b * (j + 1)) % mod, make_pair(i, j)));
	    }
	}
	
	while(n >= k){
	    int x = find(pq.top().second.first), y = find(pq.top().second.second);
	    
	    if(x != y){
	        n--;
	        if(rankf[x] < rankf[y]){
	            x = x + y;
	            y = x - y;
	            x = x - y;
	        }
	        
	        parent[y] = x;
	        
	        if(rankf[x] == rankf[y]) rankf[x]++;
	    }
	    
	    if(n == k - 1){
	        cout << pq.top().first;
	        break;
	    }
	    
	    pq.pop();
	}

	return 0;
}