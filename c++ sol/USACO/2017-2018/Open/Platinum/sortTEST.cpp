#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100000;
int n;
int a[maxn];
int ret;

void bsort(int l, int r){
	for(int i = l; i < r; i++){
		if(a[i] > a[i + 1]) swap(a[i], a[i + 1]);
	}
}

bool works(int l, int r){
	for(int i = l; i < r; i++){
		int maxv = a[l], minv = a[r];
		for(int j = l; j <= r; j++){
			if(j <= i){
				maxv = max(maxv, a[j]);
			}else{
				minv = min(minv, a[j]);
			}
		}
		if(maxv <= minv) return 1;
	}
	return 0;
}

void fsort(int l, int r){
	if(l == r) return;
	
	//do{
		/*
		for(int i = 0; i < n; i++){
			if(i == l) cout << " " << "|";
			cout << " " << a[i];
			if(i == r) cout << " " << "|";
		} 
		cout << endl;
		*/
		bsort(l, r);
		ret += r - l + 1;
	//} while(!works(l, r));
	
	/*
	for(int i = 0; i < n; i++){
		if(i == l) cout << " " << "|";
		cout << " " << a[i];
		if(i == r) cout << " " << "|";
	} 
	cout << endl;
	*/
	
	int last = l;
	for(int i = l; i < r; i++){
		int maxv = a[last], minv = a[r];
		for(int j = l; j <= r; j++){
			if(j <= i){
				maxv = max(maxv, a[j]);
			}else{
				minv = min(minv, a[j]);
			}
		}
		if(maxv <= minv){
			fsort(last, i);
			last = i + 1;
		}
	}
	fsort(last, r);
}

int main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	fsort(0, n - 1);
	
	cout << ret << endl;
	
	return 0;
}