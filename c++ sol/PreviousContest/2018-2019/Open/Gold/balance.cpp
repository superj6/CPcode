/*
	This problem by far was the most challenging gold problem this contest. To start, it first helps to think about what the
smallest amount of swaps you have to make is without ever swapping across the middle point, as swapping across the middle point is
what is most challenging to think about. For this simplified problem, the key thing to realize is that it is always possible to
change one of the sides inversion count by -1 if it is not 0, as you can always swap a 1 and 0. Similarly, you can never change
the inversion count of a side by more than 1, and each side is independent without swapping across the middle, so the solution to
this simplified problem is just the difference in the inversion count between the 2 sides. Now for the full problem, you can just
moving 1s countinuously in one direction, and each time you move a 1 across the midpoint you set the result to the minimum of it and
the number of moves you have done to swap 1s across the middle + the difference. To move 1s across the midpoint, hold a pointer on
the leftmost 0 and right rightmost just move them outward until one is out of range. To keep track of the change in difference after
moving stuff across the center use some witchcraft and think about the inversions lost when moving a 1 away from 1 side and inversion
gained when moving a 1 to the other side. Lastly, you have to try moving the 1s in both directions. The complexity of this is O(n).
*/

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
