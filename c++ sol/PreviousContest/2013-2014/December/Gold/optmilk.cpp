#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int size = 1 << 16;
int n, d;
int bb[1 << 17], bp[1 << 17], pb[1 << 17], pp[1 << 17];

void update(int node){
	int l = 2 * node, r = 2 * node + 1;
	bb[node] = max(bb[l] + pb[r], bp[l] + bb[r]);
	bp[node] = max(bp[l] + bp[r], bb[l] + pp[r]);
	pb[node] = max(pb[l] + pb[r], pp[l] + bb[r]);
	pp[node] = max(pb[l] + pp[r], pp[l] + bp[r]);
}

int main(){
	freopen("optmilk.in", "r", stdin);
	freopen("optmilk.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> d;
	
	for(int i = 0; i < n; i++) cin >> bb[size + i];
	for(int i = size - 1; i > 0; i--) update(i);
	
	long long sum = 0;
	
	for(int i = 0; i < d; i++){
		int id, m;
		cin >> id >> m;
		id--;
		
		bb[size + id] = m;
		for(int j = (size + id) / 2; j > 0; j/=2) update(j);
		
		sum += bb[1];
	}
	
	cout << sum << endl;

	return 0;
}