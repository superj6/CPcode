/*
  You can set values to result bit by bit, trying to set the highest bits first. Realize if you can set a bit but don't, you can
then set all bits lower than it, and you only have to set a bit if all bits are equivalent for the min and max value for the prefix
of a number. This means if you are able to set a bit at a position and there are two numbers in the group with the bit and one doesn't
have to be set, or there is a bit you can't set but there is one number in the group with a bit that doesn't have to be set, you can 
set all bits below and don't have to worry about that group anymore. If you can set a bit and there is only one number with the bit
set and it does not have to be, you no longer have to worry if the prefix matches so you can set the min value to 0 since even if you
took none of the lower bits it would still be larger than the min value.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

const int mxn = 100;
int n;
int f[mxn], vis[mxn];
vector<int> l[mxn], r[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> n;;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		l[i].resize(x);
		r[i].resize(x);
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < r[i].size(); j++){
		cin >> l[i][j] >> r[i][j];
	}
	
	int ret = 0;
	for(int k = 30; ~k; k--){
		bool t = 1;
		for(int i = 0; i < n; i++) if(!vis[i]){
			f[i] = 0;
			for(int j = 0; j < r[i].size(); j++){
				if((r[i][j] >> k) & 1){
					if(!~f[i]){
						f[i] = 2;
						break;
					}else if((l[i][j] >> k) & 1){
						f[i] = 1;
					}else if(f[i]){
						f[i] = 2;
						break;
					}else{
						f[i] = -1;
					}
				}
			}
			vis[i] |= f[i] == 2;
			t &= !!f[i];
		}
		if(t){
			ret |= 1 << k;
			for(int i = 0; i < n; i++) if(!vis[i] && !~f[i])
			for(int j = 0; j < r[i].size(); j++){
				l[i][j] *= !((r[i][j] >> k) & 1) || ((l[i][j] >> k) & 1);
			}
		}else{
			for(int i = 0; i < n; i++) vis[i] |= !~f[i];
		}
	}
	
	cout << ret << endl;

	return 0;
}
