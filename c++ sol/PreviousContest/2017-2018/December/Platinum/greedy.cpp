/*
       For this problem, the first thing to notice is that if a cow does not ever get a present,
that means no cow behind it will ever get a present. Similarly, at some point of time, all the
cows at some suffix of the queue will never move forward. This means you want to find the first
spot in the queue that will not get a present, and because you can you are looking for a suffix,
this hints that you can do a binary search. To do this, it is actually easier to look at the
prefix, and to think about which position each cow will go back to rather than thinking how
many they skip from the end. After a few examples, you will notice that a prefix of cows will
all get presents if the cow that moves to the least position moves to position 2 or higher,
the next least moves to position 3 or higher, etc. You can see this will work by doing a few
examples, and it works because if every cow in a prefix gets a present, it means each all cows
must move back far enough so that at group of sizes increasing by at least 1 will be moving
forward so there is never a suffix of cows that stays in the same position. This means you just
binary search, sort the positions the cows will go to, and make sure the lowest goes to at least
position 2, next lowest at least position 3, etc. The complexity of this is O(nlog^2n) because
there is one log factor from the binary search and the other log from sorting. 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n;
int a[maxn];

bool works(int x){
	int b[x];
	for(int i = 0; i < x; i++) b[i] = a[i];
	sort(b, b + x);
	
	
	for(int i = 0; i < x; i++){
		if(b[i] <= i) return 1;
	}
	
	return 0;
}

int main(){
	freopen("greedy.in", "r", stdin);
	freopen("greedy.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i] = n - a[i] - 1;
	}
	
	int l = 0, r = n;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(works(mid)) r = mid;
		else l = mid;
	}
	
	cout << n - r << endl;

	return 0;
}
