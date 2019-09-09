#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

long minb[1 << 19], sumb[1 << 19], incb[1 << 19];

void update(int node){
	int l = (node << 1), r = (node << 1) + 1;
	
	minb[node] = min(minb[l], minb[r]);
	sumb[node] = sumb[l] + sumb[r];
}

void pushDown(int node, int a, int b){
	minb[node] += incb[node];
	sumb[node] += incb[node] * (b - a + 1);

	incb[(node << 1)] += incb[node];
	incb[(node << 1) + 1] += incb[node];
	
	incb[node] = 0;
}

void pullUp(int node, int a, int b){
	int mid = (a + b) >> 1;
	int l = (node << 1), r = (node << 1) + 1;
	
	minb[node] = min(minb[l] + incb[l], minb[r] + incb[r]);
	sumb[node] = (sumb[l] + incb[l] * (mid - a + 1)) + (sumb[r] + incb[r] * (b - mid));
}

long getmin(int node, int a, int b, int minv, int maxv){
	if(b < minv || a > maxv) return 1000000000;
	if(a >= minv && b <= maxv) return minb[node] + incb[node];
	
	pushDown(node, a, b);
	
	int mid = (a + b) >> 1;
	int l = (node << 1), r = (node << 1) + 1;
	
	long ret = min(getmin(l, a, mid, minv, maxv), getmin(r, mid + 1, b, minv, maxv));
	
	pullUp(node, a, b);
	
	return ret;
}

long getsum(int node, int a, int b, int minv, int maxv){
	if(b < minv || a > maxv) return 0;
	if(a >= minv && b <= maxv) return sumb[node] + incb[node] * (b - a + 1);
	
	pushDown(node, a, b);
	
	int mid = (a + b) >> 1;
	int l = (node << 1), r = (node << 1) + 1;
	
	long ret = getsum(l, a, mid, minv, maxv) + getsum(r, mid + 1, b, minv, maxv);
	
	pullUp(node, a, b);
	
	return ret;
}

void setinc(int node, int a, int b, int minv, int maxv, int val){
	if(b < minv || a > maxv) return;
	if(a >= minv && b <= maxv){
		incb[node] += val;
		return;
	} 
	
	pushDown(node, a, b);
	
	int mid = (a + b) >> 1;
	int l = (node << 1), r = (node << 1) + 1;
	
	setinc(l, a, mid, minv, maxv, val);
	setinc(r, mid + 1, b, minv, maxv, val);
	
	pullUp(node, a, b);
}

int main(){
	freopen("haybales.in", "r", stdin);
	freopen("haybales.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	for(int i = 0; i < (1 << 19); i++){
		minb[i] = 1000000000;
		sumb[i] = 0;
		incb[i] = 0;
	}
	
	for(int i = 0; i < n; i++){
		cin >> sumb[i + (1 << 18)];
		minb[i + (1 << 18)] = sumb[i + (1 << 18)];
		
		for(int j = ((i + (1 << 18)) >> 1); j > 0; j>>=1) update(j);
	}
	
	for(int i = 0; i < q; i++){
		char t;
		int a, b;
		cin >> t >> a >> b;
		a--, b--;
		
		if(t == 'M'){
			cout << getmin(1, 0, (1 << 18) - 1, a, b) << endl;
		}else if(t == 'S'){
			cout << getsum(1, 0, (1 << 18) - 1, a, b) << endl;
		}else{
			int c;
			cin >> c;
			
			setinc(1, 0, (1 << 18) - 1, a, b, c);
		}
	}

	return 0;
}