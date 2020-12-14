#include "grader.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
const int m = 1000, w = 4050;

void helpBessie(int x){
	int n = getTrainLength();
	int k = getWindowLength();
	int t = getCurrentPassIndex();
	int i = getCurrentCarIndex();
	int j, f, ql, qr;
	
	if(!t){
		if(!i) set(0, 1), set(1, 0);
		ql = get(0), qr = get(1); 
		
		int d = 0;
		if(i % m == 0 || (i >= k && (i - k) % m == 0) || (d = x <= get(qr << 1 | 1))){
			qr -= d;
			while(qr >= ql && get(qr << 1 | 1) >= x) qr--;
			qr++;
			set(qr << 1, i), set(qr << 1 | 1, x);
		}
		
		if(i >= k - 1 && (i - k + 1) % m == 0){
			while(qr >= ql && get(ql << 1) <= i - k) ql++;
			set(w + (i - k + 1) / m, get(ql << 1));
		}
		
		set(0, ql), set(1, qr);
	}else if (i >= get(w)){
		if(i == get(w)){
			set(0, 1), set(1, 0);
			set(w - 1, 1), set(w - 2, inf), set(w - 3, 0);
		}
		ql = get(0), qr = get(1);
		j = get(w - 1), f = get(w - 3);
		
		if(i - get(w + j - 1) <= m){
			while(qr >= ql && get(qr << 1 | 1) >= x) qr--;
			qr++;
			set(qr << 1, i), set(qr << 1 | 1, x);
		}else if(x < get(w - 2)){
			set(w - 2, x);
		}
		
		if(i == f + k - 1){
			while(qr >= ql && get(ql << 1) < f) ql++;
			shoutMinimum(min(get(w - 2), get(ql << 1 | 1)));
			f++;
		}
		
		while(m * j + k - 1 < n && i == get(w + j)){
			while(f <= m * j){
				while(qr >= ql && get(ql << 1) < f) ql++;
				shoutMinimum(min(get(w - 2), get(ql << 1 | 1)));
				f++;
			}
			j++;
			set(w - 2, inf);
			ql = qr = 1;
			set(qr << 1, i), set(qr << 1 | 1, x);
		}
		
		set(0, ql), set(1, qr);
		set(w - 1, j), set(w - 3, f);
	}
}