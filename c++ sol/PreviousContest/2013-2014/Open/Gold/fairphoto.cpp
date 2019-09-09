#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
#define endl '\n'

int cnt[8], pos[8];
int order[8] = {0, 1, 2, 3, 4, 5, 6, 7};
map<vector<int>, int> s[256];

int main(){
	freopen("fairphoto.in", "r", stdin);
	freopen("fairphoto.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	pair<int, int> cow[n];
	for(int i = 0; i < 8; i++) pos[i] = n;
	
	for(int i = 0; i < n; i++){
		cin >> cow[i].first >> cow[i].second;
		cow[i].second--;
		cnt[cow[i].second]++;
	}
	
	sort(cow, cow + n);
	
	for(int i = n - 1; i >= 0; i--){
		cnt[cow[i].second]--;
		pos[cow[i].second] = i;
		
		sort(order, order + 8, [&](int a, int b)->bool{
			return pos[a] < pos[b];
		});
		
		int f = 8, h = 0;
		
		for(int l = 0; l < 8 && pos[order[l]] != n; l++){
			f = min(f, order[l]);
			h |= 1 << order[l];
			if(l >= k - 1){
				vector<int> a(8);
			
				for(int j = 0; j < 8; j++){
					a[order[j]] = cnt[order[j]];
					if(j <= l) a[order[j]] -= cnt[f];
				}
				
				s[h][a] = cow[i].first;
			}
		}

	}
	
	int maxv = -1;
	for(int i = 0; i < 8; i++) pos[i] = -1;
	
	for(int i = 0; i < n; i++){
		cnt[cow[i].second]++;
		pos[cow[i].second] = i;
		
		sort(order, order + 8, [&](int a, int b)->bool{
			return pos[a] > pos[b];
		});
		
		int f = 8, h = 0;
		
		for(int l = 0; l < 8 && pos[order[l]] != -1; l++){
			f = min(f, order[l]);
			h |= 1 << order[l];
			
			if(l >= k - 1){
				vector<int> a(8);
			
				for(int j = 0; j < 8; j++){
					a[order[j]] = cnt[order[j]];
					if(j <= l) a[order[j]] -= cnt[f];
				}
				
				auto dif = s[h].find(a);
				
				if(dif != s[h].end()){
					maxv = max(maxv, cow[i].first - dif->second);
				}
				
			}
		}
	}
	
	cout << maxv << endl;

	return 0;
}