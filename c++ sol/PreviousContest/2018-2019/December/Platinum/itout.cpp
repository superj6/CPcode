/*
	As a disclaimer this solution got only 9 / 16 cases but i'm p sure it is the correct idea. This problem was definitely 
the hardest this contest. The first thing you must notice is that any subset already in sorted order does not need to be yelled
at. This means the problem for longest increasing subsequence(lis) such that the remaining elements are the kth lexographically least
sequence, as only the remaining elements need to be yelled at. Furthermore, the kth lexographically sequence of remaining values
is equivalent the kth lexographically largest lis. To find the length of the longest lis at each index, we compress the values
and insert the lis lengths into a segment tree at its current index value as we compute them, and for each index set the lis
to 1 + the largest lis in the segment tree with a value less than the or equal the current value (this is a pretty standard 
method). Now, to find the kth lexographically largest lis, consider you computed the amount lis's of that start with each index.
You could then hold each index in different arrays based on its lis length and sort them according to value. Then for each
length, start with the largest value, if there are more lis's that start with that than k, you are going to use that element,
if not, subtract that amount from k and go to the next. When you find an element that works, go to the next length and do the
same, making sure you are only considering elements that could come after the one you previously chose ie have value >= previous
and index > previous. This will work to find the kth lexographically largest lis, so now all you have to do is figure out
how to compute the amount of lis's that start with each index. To do this, do a similar sweep as computing lis's except iterating
in reverse order through the array, and hold a segment tree for each value of lis. Each lis number for each value with the
maximum lis length will be 1, and for all others set it equal to the sum of all lis numbers in the segment tree with an lis
value 1 greater than it and having a greater value. This gives the number of lis's starting with each value and completes
the solution.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const long long inf = 1000000000000000007;

struct segTree{
	int l, r;
	long long maxv = 0, sumv = 0;
	segTree *left, *right;
	
	segTree(int l, int r){
		this->l = l;
		this->r = r;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void add(int index, long long val){
		if(l > index || r < index) return;
		if(l == r){
			maxv += val;
			sumv += val;
			maxv = min(maxv, inf);
			sumv = min(sumv, inf);
			return;
		}
		
		left->add(index, val);
		right->add(index, val);
		
		maxv = max(left->maxv, right->maxv);
		sumv = min(left->sumv + right->sumv, inf);
	}
	
	long long getMax(int a, int b){
		if(l > b || r < a) return 0;
		if(l >= a && r <= b) return maxv;
		
		return max(left->getMax(a, b), right->getMax(a, b));
	}
	
	long long getSum(int a, int b){
		if(l > b || r < a) return 0;
		if(l >= a && r <= b) return sumv;
		
		return min(left->getSum(a, b) + right->getSum(a, b), inf);
	}
};

int main(){
	freopen("itout.in", "r", stdin);
	freopen("itout.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	long long k;
	cin >> n >> k;
	
	int a[n];
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	
	segTree *tree = new segTree(1, n);
	
	int lis[n];
	int best = 0;
	
	for(int i = 0; i < n; i++){
		lis[i] = tree->getMax(1, a[i]) + 1;
		tree->add(a[i], lis[i]);
		
		best = max(best, lis[i]);
	}
	
	vector<long long> dp[best];
	vector<int> loc[best];
	vector<segTree*> tres;
	int test[best];
	int id[n];
	
	for(int i = 0; i < n; i++){
		lis[i]--;
		id[i] = dp[lis[i]].size();
		dp[lis[i]].push_back(0);
		loc[lis[i]].push_back(i);
	}
	
	for(int i = 0; i < best; i++){
		tres.push_back(new segTree(0, dp[i].size() - 1));
		test[i] = 0;
	}
	
	for(int i = 0; i < n; i++){
		if(lis[i] == 0){
			dp[lis[i]][id[i]] = 1;
		}else{
			while(a[loc[lis[i] - 1][test[lis[i] - 1]]] > a[i] && test[lis[i] - 1] < dp[lis[i] - 1].size()) test[lis[i] - 1]++;
			dp[lis[i]][id[i]] = tres[lis[i] - 1]->getSum(test[lis[i] - 1], dp[lis[i] - 1].size() - 1);
		}
		
		tres[lis[i]]->add(id[i], dp[lis[i]][id[i]]);
	}
	
	vector<int> ret;
	int val = n;
	
	for(int i = best - 1; i >= 0; i--){
		for(int j = 0; j < dp[i].size(); j++){
			if(val < a[loc[i][j]]) continue;
			
			if(dp[i][j] >= k){
				ret.push_back(a[loc[i][j]]);
				val = a[loc[i][j]];
				break;
			}
			
			k -= dp[i][j];
		}
	}
	
	reverse(ret.begin(), ret.end());
	cout << n - ret.size() << endl;
	
	for(int i = 1, j = 0; i <= n; i++){
		if(j < ret.size() && ret[j] == i) j++;
		else cout << i << endl;
	}

	return 0;
}
