/*
	For this problem, it helps to first consider comparing running normal bubble sort to bessie's quickish sort. If you run
through the steps of each for the same array, you should notice that they are both essentially equivalent as when running normal
bubble sort, because when normal bubble sort you will never move a parition point anyway and you are sweeping through both sides
of the partition point anyway. This means that the answer is almost equivalent to the number of times the bubble sort function
would be ran normally in the bubble sort function multiplied by the number of elements. However, this overcounts when an element
is already sorted. This means what we have to count instead is, for each element, how many times is the bubble sort function ran
on the entire array in the normal bubble sort algorithm before the element partitions the array. To do this, sort the array while
keeping track of the elements original indices, then iterate through the sorted array while keeping track of the highest original
index of an element passed so far. Then, hold an array p where p[i] is the highest index at that point minus i. Then, when you
iterate through the array, for each element you should add the max of p[i] and p[i - 1] as that is the max of all elements with
less value to go before that position and the for the element at that position to get there before the elements ahead of it. This
is because in bubble sort higher elements move forward first and lower elements move backward only 1 place per run of the bubble
sort function. Also, you must be careful about the edgecases of n being equal to 1 because then the answer is 0, and if the array
is already sorted and n is greater than 1 each element is still passed through with the bubble sort function 1 time. The complexity
of this is O(nlogn) due to sorting.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
pi a[maxn];
int p[maxn];
long ret;

int main() {
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
	
	for(int i = 0, j = 0; i < n; i++){
		j = max(j, a[i].second);
		p[i] = j - i;
		ret += max((n > 1 ? 1 : 0), max(p[i], (i > 0 ? p[i - 1] : 0)));
	}
	
	cout << ret << endl;
	
	return 0;
}
