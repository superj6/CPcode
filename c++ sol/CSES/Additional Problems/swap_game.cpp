#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
unordered_map<long, int> mp;
long a;
 
void precomp(){
	long c = 0;
	for(int i = 0; i < 9; i++) c = 9 * c + i;
	
	long p[9];
	p[0] = 1;
	for(int i = 1; i < 9; i++) p[i] = 9 * p[i - 1];
	
	queue<long> q;
	q.push(c);
	mp[c] = 0;
	if(a == c) return;
	
	while(!q.empty()){
		c = q.front();
		q.pop();
		
		int v = mp[c];
		
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++){
			long f = (c / p[i * 3 + j]) % 9;
			
			if(i < 2){
				long g = (c / p[(i + 1) * 3 + j]) % 9; 
				c += (g - f) * p[i * 3 + j] + (f - g) * p[(i + 1) * 3 + j];
				if(mp.find(c) == mp.end()){
					mp[c] = v + 1;
					if(c == a) return;
					q.push(c);
				}
				c += (f - g) * p[i * 3 + j] + (g - f) * p[(i + 1) * 3 + j];
			}
			if(j < 2){
				long g = (c / p[i * 3 + (j + 1)]) % 9; 
				c += (g - f) * p[i * 3 + j] + (f - g) * p[i * 3 + (j + 1)];
				if(mp.find(c) == mp.end()){
					mp[c] = v + 1;
					if(c == a) return;
					q.push(c);
				}
				c += (f - g) * p[i * 3 + j] + (g - f) * p[i * 3 + (j + 1)];
			}
		}
	}
	
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	for(int i = 0; i < 9; i++){
		long x;
		cin >> x;
		x--;
		a = 9 * a + x;
	}
	
	precomp();
	
	cout << mp[a] << endl;
 
	return 0;
}