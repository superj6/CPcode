/*
	For this problem, you need to hold the breed at index i as a[i], but for the other side, hold the index of breed i as p[i].
Now, you can iterate through the breeds of the first side in order and in a segment tree hold the maximum value using pairings up to
and index on the other side. This is because for pairs to not intersect, both indices of one pairing must be before both indices of
the other, so iterating through one side ensures the first index ordering and you can query for the maximum value of the segment tree
before a certain index on the other to ensure the second index ordering. Now, to calculate the dp for index i, hold all p[j] for all j
within 4 of a[i] in reverse sorted order in a temporary array cur. Now, iterate through cur and set in the segment tree cur[j] to be
the max of what it is and 1 + querying the segment tree before cur[j]. You sort in reverse order to ensure you do not use a value from
the segment tree which would cause pair crossing, and when you add 1 + the query before cur[j] this is equivalent to using the pair
between a[i] and the breed at the index of cur[j] and the best pairing using only indices on both sides before that. The complexity of
this is O(nlogn) from the segment tree.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left, *right;
	int maxv = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = l + (r - l) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void add(int i, int x){
		if(l > i || r < i) return;
		if(l == r){
			maxv = max(maxv, x);
			return;
		}
		
		left->add(i, x);
		right->add(i, x);
		maxv = max(left->maxv, right->maxv);
	}
	
	int qry(int a, int b){
		if(l > b || r < a) return 0;
		if(l >= a && r <= b) return maxv;
		
		return max(left->qry(a, b), right->qry(a, b));
	}
};

int main(){
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int a[n], p[n];
	segTree *t = new segTree(0, n - 1);
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
	} 
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		p[x] = i;
	}
	
	for(int i = 0; i < n; i++){
		vector<int> cur;
		for(int j = max(a[i] - 4, 0); j < min(a[i] + 5, n); j++) cur.push_back(p[j]);
		sort(cur.begin(), cur.end(), greater<int>());
		
		for(int j = 0; j < cur.size(); j++){
			t->add(cur[j], 1 + t->qry(0, cur[j] - 1));
		}
	}
	
	cout << t->qry(0, n - 1) << endl;

	return 0;
}
