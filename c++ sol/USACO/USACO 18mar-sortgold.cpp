/*
  Realize that between each round of the sorting algorithm, if you were to split the array between to indices, at most one element
can go from the left to right side, and at most one element can go from the right to left side. Because the number of elements
going left to right is the same as amount going right to left because the number of elements on each side stays the same after
sorting, you can just sort the array keeping their original indices, then use a fenwick tree to add elements in their original
index when iterating through the sorted array, and test how many elements finishing left of that point started to the right of
that point, and take the maximum amount as the answer.
*/ 
 
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int maxn = 100001;
int n;
int bit[maxn];
pair<int, int> a[maxn];

void add(int i){
	i++;
	for(; i <= n; i += i & -i) bit[i]++;
}

int qry(int i){
	i++;
	int ret = 0;
	for(; i > 0; i -= i & -i) ret += bit[i];
	return ret;
}

int main(){
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].first;
		a[i].second = i;
	}
	
	sort(a, a + n);
	
	int ans = 1;
	for(int i = 0; i < n; i++){
		add(a[i].second);
		ans = max(ans, i + 1 - qry(i));
	}
	
	cout << ans << endl;

	return 0;
}
