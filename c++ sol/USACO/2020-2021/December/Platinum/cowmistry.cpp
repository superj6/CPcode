/*
	First realize all triplets must have all bits greater than the highest set bit of m (K + 1 in problem) set,
and we want all element pairwise xors in a triplet to be strictly less than m. Now there are two possible cases. If
all three elements of a triplet have the same set bit for the highest set bit m, that bit will always be turned off
in all xor pairs, so that triplet will always work. Otherwise we have two elements with the same bit set and one
element with a different bit set for the highest set bit position of m. We will recurse on this case holding pairs
representing sets of partial intervals given in the problem that recursed together if they have the all bits 
greater than the top set bit of m the same and seperated by if the top set bit of m is set or not.
	We will recurse with the function sol(vi a, vi b, int x, int y), where a and b are the two sets of
intervals seperated by the bit which is signified by x which is a power of two with 1 at the seperated bit position,
and all higher bits must be equal, and y is the number of accumulated values that could pair with numbers in set a
but have higher bits unequal at some point, ie they are not in set a nor set b. The function sol() needs to find
intervals in b that can pair with intervals and a but can not for sure be used yet based on the bits x and above. 
We can first seperate a and b by their bit at the bit lower than x ie xx, and we'll call the new seperated sets 
aa[0], aa[1], bb[0], and bb[1], signifying the bit set at xx. Now if the bit xx of m is not set, that means we must
recurse on the pairs of sets with the same bit at xx, as the pairs of numbers at that point have a different bit
set at xx then the pair will for sure be greater than m. However, if bit xx of m is set, we can recurse with pairs
of aa and bb such that their bit xx is different, because they still have a chance of being less than m in a lower
bit. Also, all pairs of aa and bb with the same bit set will for sure now work, so you can the the amount of values
in the bb interval with the same bit as the aa set your recursing on to the y value in the recursive call. Finally
once you reach a base case where a or b is empty or b intervals has every value less than x, you return the number
of values in set a multiplied by the number of ways to choose two values in y plus all values still in set b that
work, as all of these will now be valid sets that started off with different bits at the highest bit of m.
	Now to show the recursive call works in time, realize all initial b sets will be split at most once
where they add a new interval to the set. This is because the case in the recursion when b has every value less 
than x is a stopping point, so after an initial interval is split creating a new interval, the second time it is
split one of the recursive calls will stop immediately while the other one may keep going. Also, when recursing the
intervals splits the current sets into two disjoint groups. And of course empty sets stop recursing immediately.
This means there can be at most 2 * n intervals at each bit layer of recursion, and there are only lgn bits to go
down, which is why the complexity ends up as O(nlgn). 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<pi>

const int mod = 1000000007;
int n, m, k, kk;
map<int, vi> mp;

ll f(vi &v){ ll ret = 0; for(pi i : v) ret += i.s - i.f + 1; return ret;}
ll f2(ll x){ return x * (x - 1) / 2 % mod;}
ll f3(ll x){ return f2(x) * (x - 2) % mod * (mod + 1) / 3 % mod;}

void add(vi &v, pi p, int x){
	p.f = max(p.f, 0), p.s = min(p.s, x - 1);
	if(p.f <= p.s) v.push_back(p);
}

ll sol(vi a, vi b, int x, int y){
	if(a.empty()) return 0;
	if(b.empty()) return f(a) * f2(y) % mod;
	if(f(b) == x) return f(a) * f2(y + ((x - 1) & m)) % mod; 
	vi aa[2], bb[2];
	ll xx = x / 2, ret = 0;
	for(pi i : a) add(aa[0], i, xx), add(aa[1], {i.f - xx, i.s - xx}, xx);
	for(pi i : b) add(bb[0], i, xx), add(bb[1], {i.f - xx, i.s - xx}, xx);
	for(int i = 0; i < 2; i++){
		if(m & xx) (ret += sol(aa[i], bb[!i], xx, y + f(bb[i]))) %= mod;
		else (ret += sol(aa[i], bb[i], xx, y)) %= mod;
	}
	return ret;
}

ll ans(vi v){
	vi a[2];
	ll ret = 0;
	for(pi i : v) add(a[0], i, kk), add(a[1], {i.f - kk, i.s - kk}, kk);
	for(int i = 0; i < 2; i++){
		(ret += f3(f(a[i]))) %= mod;
		(ret += sol(a[i], a[!i], kk, 0)) %= mod;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	kk = 1 << __lg(++m), k = 2 * kk, m -= kk;

	ll ret = 0, z = k * f2(m) + 2 * f3(kk);
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;
		int l = x / k, r = y / k;
		x %= k, y %= k;
		if(l != r){
			(ret += (r - l - 1) * z) %= mod;
			mp[l].push_back({x, k - 1});
			mp[r].push_back({0, y});
		}else{
			mp[l].push_back({x, y});
		}
	}
	
	for(auto i : mp) (ret += ans(i.s)) %= mod;

	cout << ret << endl;

	return 0;
}