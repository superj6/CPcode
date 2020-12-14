//#include "Catherine.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

const int k = 6;
int a, b;
int prv = -1;
bool f = 0;
int s[k] = {0, 0, 1, 0, 1, 1};
vi t;

void Init(int A, int B){
	a = A, b = B;
}

int Move(vi v){
	if(a > 2){
		if(~prv) v[prv]++;
		for(int i = 0; i < 3; i++){
			if(v[i] && v[(i + 1) % 3]) return prv = i;
		}
		for(int i = 0; i < 3; i++){
			if(v[i]) return prv = i;
		}
	}else{
		if(f){
			if(v[0] + v[1] > 1) v[prv]++;
			return prv = (v[0] == 1) ^ 1;
		}
		if(!~prv){
			if(v[0] + v[1] != 2){
				f = 1;
				return prv = (v[0] == 1) ^ 1; 
			}
			prv = (v[0] > 0) ^ 1;
			t.push_back((v[0] > 1) ^ 1);
			t.push_back(prv);
			return prv;
		}
		if(v[0] + v[1] == 0){
			f = 1;
			return -1;
		}
		if(v[0] + v[1] > 1){
			f = 1;
			return !v[prv] ? -1 : prv ^= 1;
		}
		t.push_back((v[0] == 1) ^ 1);
		if(t.size() == k - 1){
			for(int i = 0; i < k; i++){
				f = 1;
				for(int j = 0; j < k - 1; j++) f &= s[(i + j) % k] == t[j];
				if(f) return -1;
			}
			f = 1;
		}
		return prv = (v[0] == 1) ^ 1;
	}
	return -2;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	return 0;
}