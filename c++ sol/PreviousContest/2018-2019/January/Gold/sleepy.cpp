/*
	The first thing to notice is the group of cows in increasing order at the end of the sequence do not have to be yelled
at. Call the point at the start of this group k. For the remaining cows, you will have to yell at them to move past all the cows
before k plus the number of cows already sorted, the active cows, at the end that are less than it. To find out the amount each
cows has to move, use a fenwick tree (or segment tree if ur brick like me) to store active cows, and make all cows after k
active. Then, iterate from the beginning of the sequence to before k, and for each of those cows output k - its index + the
number of active cows with less value. Then add this cow to the active group. The complexity of this is O(nlogn) due to range
addition operations.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left, *right;
	int sum = 0;

	segTree(int a, int b){
		l = a;
		r = b;

		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
			
		}
	}
	
	void add(int index, int val){
		if(l > index || r < index) return;
		if(l == r){
			sum += val;
			return;
		}
		
		left->add(index, val);
		right->add(index,val);
		
		sum = left->sum + right->sum;
	}
	
	int getsum(int a, int b){
		if(l > b || r < a) return 0;
		if(l >= a && r <= b) return sum;
		
		return left->getsum(a, b) + right->getsum(a, b);
	}
};

int main(){
	freopen("sleepy.in", "r", stdin);
	freopen("sleepy.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	segTree *order = new segTree(1, n);
	
	int cnt = n - 1;
	
	for(int last = n + 1; cnt >= 0; cnt--){
		if(a[cnt] < last){
			order->add(a[cnt], 1);
			last = a[cnt];
		}else{
			break;
		}
	}
	
	cnt++;
	
	cout << cnt << endl;
	
	for(int i = 0; i < cnt; i++){
		cout << (cnt - i - 1 + order->getsum(1, a[i]));
		
		order->add(a[i], 1);
		
		if(i < cnt - 1) cout << " ";
		else cout << endl;
	}

	return 0;
}
