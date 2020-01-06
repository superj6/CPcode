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