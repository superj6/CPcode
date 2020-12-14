#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int n;

long sweep(int a[], int l, int r, long diff, int one1, int one2, int x){
	long best = abs(diff), cnt = 0;
	
	while(l >= 0 && r < 2 * n){
		cnt += r - l;
		
		diff += (one1 + one2 + l + r + 1 - 3 * n) * (x ? -1 : 1);
		
		one1 += (x ? 1 : -1);
		one2 += (x ? -1 : 1); 

		best = min(best, abs(diff) + cnt);
		
		l--, r++;
		
		while(!a[l] ^ x && l >= 0) l--;
		while(a[r] ^ x && r < 2 * n) r++;
	}

	return best;
}

int main(){
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	int a[2 * n];
	long diff = 0;
	int l1 = -1, r0 = 2 * n;
	int l0 = -1, r1 = 2 * n;
	int one1 = 0, one2 = 0;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		one1 += a[i];
		
		if(a[i]) l1 = max(l1, i);
		else{
			l0 = max(l0, i);
			diff += one1;
		} 
	}
	
	for(int i = 0; i < n; i++){
		cin >> a[i + n];
		one2 += a[i + n];
		
		if(a[i + n]) r1 = min(r1, i + n);
		else{
			r0 = min(r0, i + n);
			diff -= one2;
		} 
	}

	cout << min(sweep(a, l1, r0, diff, one1, one2, 0), sweep(a, l0, r1, diff, one1, one2, 1)) << endl;

	return 0;
}