#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;

struct T{
	int l, r, d;
	struct M{
		ll aa, ab, ba, bb;
		
		M() : aa(1), ab(0), ba(0), bb(1) {}
		M(int aa, int ab, int ba, int bb) :
			aa(aa), ab(ab), ba(ba), bb(bb) {}
		M(int x, int y){
			aa = ab = max(0, (x - 1) / 2);
			ba = bb = !(x & 1);
			aa = (y * aa + 1) % mod, ba *= y;
		}
		
		M operator*(M m){
			return M((aa * m.aa + ab * m.ba) % mod, 
				(aa * m.ab + ab * m.bb) % mod,
				(ba * m.aa + bb * m.ba) % mod,
				(ba * m.ab + bb * m.bb) % mod);
		}
	} m;
	
	T() : d(0){}
	T(pi p) : l(p.f + 1), r(p.s - 1), d((p.s - p.f) / 2) {}
	
	friend T operator + (T a, T b){
		if(!a.d) return b;
		if(!b.d) return a;
		T ret = a;
		ret.r = b.r;
		ret.m = a.m * M(b.l - a.r, b.d) * b.m;
		return ret;
	}
};

const int maxn = 1 << 17;
int n;
T tre[maxn << 1];

//update 0101010 ranges
vector<int> id;
vector<pi> q[maxn];
set<pi> s;

void add(int t, pi p){
	id.push_back(p.f);
	q[t].push_back(p);
	s.insert(p);
}

void del(int t, set<pi>::iterator it){
	q[t].push_back(*it);
	s.erase(it);
}

void add(int t, int x){
	pi p = {x - 1, x + 1};
	auto it = s.lower_bound({x, 2e9});
	if(it == s.begin() || prev(it)->s < x){
		if(it != s.begin() && prev(it)->s + 1 == x){
			p.f = prev(it)->f;
			del(t, prev(it));
		}
		if(it->f - 1 == x){
			p.s = it->s;
			del(t, it);	
		}
		add(t, p);
	}else{
		it--;
		if((x - it->f) & 1){
			p = {it->f + 1, x};
			x = it->s;
			del(t, it);
			if(p.f < p.s) add(t, p);
			if(p.f >= 2) add(t, max(1, p.f - 2));
			add(t, x);
		}else{
			p = {it->f, min(x, it->s - 2)};
			x = max(x + 1, it->s);
			del(t, it);
			if(p.f < p.s) add(t, p);
			add(t, x);
		}
	}
}
//end update 0101010 ranges

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		add(i, x);
	}
	
	sort(id.begin(), id.end());
	id.erase(unique(id.begin(), id.end()), id.end());
	
	for(int i = 0; i < n; i++){
		for(pi p : q[i]){
			int x = lower_bound(id.begin(), id.end(), p.f) - id.begin() + maxn;
			tre[x] = tre[x].d ? T() : T(p);
			for(x >>= 1; x; x >>= 1){
				tre[x] = tre[x << 1] + tre[x << 1 | 1];
			}
		}
		cout << (T::M(tre[1].l, tre[1].d) * tre[1].m).aa << endl;
	}

	return 0;
}