#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>
#include <tuple>
#include <math.h>
#include <iomanip>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

//buildup
struct pt{
  ll x, y;
  pt() {};
  pt (ll X, ll Y) : x(X), y(Y) {};
  pt operator-(pt p){
    return pt(x - p.x, y - p.y);
  }
  ll crs(pt p){
    return x * p.y - y * p.x;
  }
  ll crs(pt a, pt b){
    return (a - *this).crs(b - *this);
  }
  ll dot(pt p){
    return x * p.x + y * p.y;
  }
  ll dot(pt a, pt b){
    return (a - *this).dot(b - *this);
  }
  ll sqrl(){
    return this->dot(*this);
  }
  bool operator<(pt p){
    return x == p.x ? y < p.y : x < p.x;
  }
  bool operator==(pt p){
    return x == p.x && y == p.y;
  }
};

const pt inf_pt = pt(1e18, 1e18);

struct quad{
  pt st;
  quad *rot = 0, *onxt = 0;
  bool used = 0;
  quad *rev(){
    return rot->rot;
  }
  quad *lnxt(){
    return rot->rev()->onxt->rot;
  }
  quad *oprv(){
    return rot->onxt->rot;
  }
  pt dest(){
    return rev()->st;
  }
};

quad *make_edge(pt a, pt b){
  quad *e1 = new quad, *e2 = new quad, *e3 = new quad, *e4 = new quad;
  e1->st = a, e2->st = b, e3->st = e4->st = inf_pt;
  e1->rot = e3, e2->rot = e4, e3->rot = e2, e4->rot = e1;
  e1->onxt = e1, e2->onxt = e2, e3->onxt = e4, e4->onxt = e3;
  return e1;
}

void splice(quad *a, quad *b){
  swap(a->onxt->rot->onxt, b->onxt->rot->onxt);
  swap(a->onxt, b->onxt);
}

void del_edge(quad *e){
  splice(e, e->oprv());
  splice(e->rev(), e->rev()->oprv());
  delete e->rot, delete e->rev()->rot, delete e->rev(), delete e;
}

quad *connect(quad *a, quad *b){
  quad *e = make_edge(a->dest(), b->st);
  splice(e, a->lnxt());
  splice(e->rev(), b);
  return e;
}

bool left_of(pt p, quad *e){
  return p.crs(e->st, e->dest()) > 0;
}

bool right_of(pt p, quad *e){
  return p.crs(e->st, e->dest()) < 0;
}

typedef __int128 i128;
i128 det3(i128 a1, i128 a2, i128 a3, i128 b1, i128 b2, i128 b3, i128 c1, i128 c2, i128 c3){
  return a1 * (b2 * c3 - c2 * b3) - a2 * (b1 * c3 - c1 * b3) + a3 * (b1 * c2 - c1 * b2);
}

bool in_circle(pt a, pt b, pt c, pt d){
  i128 det = -det3(b.x, b.y, b.sqrl(), c.x, c.y, c.sqrl(), d.x, d.y, d.sqrl());
  det += det3(a.x, a.y, a.sqrl(), c.x, c.y, c.sqrl(), d.x, d.y, d.sqrl());
  det -= det3(a.x, a.y, a.sqrl(), b.x, b.y, b.sqrl(), d.x, d.y, d.sqrl());
  det += det3(a.x, a.y, a.sqrl(), b.x, b.y, b.sqrl(), c.x, c.y, c.sqrl());
  return det > 0;
}
//end buildup

typedef array<pt, 3> tri;
const int maxn = 100000;
int n;
pt p[maxn];
vector<tri> ans;

//delaunay
pair<quad*, quad*> solve(int l, int r){
  if(r - l + 1 == 2){
    quad *ret = make_edge(p[l], p[r]);
    return {ret, ret->rev()};
  }
  if(r - l + 1 == 3){
    quad *a = make_edge(p[l], p[l + 1]), *b = make_edge(p[l + 1], p[r]);
    splice(a->rev(), b);
    int sg = p[l].crs(p[l + 1], p[r]);
    sg = sg >= 0 ? sg ? 1 : 0 : -1;
    if(!sg) return {a, b->rev()};
    quad *c = connect(b, a);
    if(~sg) return  {a, b->rev()};
    else return {c->rev(), c};
  }

  int mid = (l + r) / 2;
  quad *ldo, *ldi, *rdo, *rdi;
  tie(ldo, ldi) = solve(l, mid);
  tie(rdi, rdo) = solve(mid + 1, r);
  label:
    if(left_of(rdi->st, ldi)){
      ldi = ldi->lnxt();
      goto label;
    }
    if(right_of(ldi->st, rdi)){
      rdi = rdi->rev()->onxt;
      goto label;
    }
  
  quad *bsl = connect(rdi->rev(), ldi);
  auto valid = [&](quad *e){ return right_of(e->dest(), bsl);};
  if(ldi->st == ldo->st) ldo = bsl->rev();
  if(rdi->st == rdo->st) rdo = bsl;

  while(1){
    quad *lcnd = bsl->rev()->onxt;
    if(valid(lcnd)){
      while(in_circle(bsl->dest(), bsl->st, lcnd->dest(), lcnd->onxt->dest())){
        quad *t = lcnd->onxt;
        del_edge(lcnd);
        lcnd = t;
      }  
    }
    quad *rcnd = bsl->oprv();
    if(valid(rcnd)){
      while(in_circle(bsl->dest(), bsl->st, rcnd->dest(), rcnd->oprv()->dest())){
        quad *t = rcnd->oprv();
        del_edge(rcnd);
        rcnd = t;
      }
    }
    if(!valid(lcnd) && !valid(rcnd)) break;
    if(!valid(lcnd) || (valid(rcnd) && 
    in_circle(lcnd->dest(), lcnd->st, rcnd->st, rcnd->dest()))) bsl = connect(rcnd, bsl->rev());
    else bsl = connect(bsl->rev(), lcnd->rev());
  }

  return make_pair(ldo, rdo);
}

void delaunay(){
  sort(p, p + n);
  quad *e = solve(0, n - 1).f;
  
  vector<quad*> edges = {e};
  while(e->onxt->dest().crs(e->dest(), e->st) < 0) e = e->onxt;
  vector<pt> ps;
  auto add = [&](){
    quad *cur = e;
    do{
      cur->used = 1;
      ps.push_back(cur->st);
      edges.push_back(cur->rev());
      cur = cur->lnxt();
    } while(cur != e);
  };

  add();
  ps.clear();
  for(int i = 0; i < edges.size(); i++){
    if(!(e = edges[i])->used) add();
  }

  for(int i = 0; i < ps.size(); i += 3){
    ans.push_back({ps[i], ps[i + 1], ps[i + 2]});
  }
}
//end delaunay

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
  cout << fixed << setprecision(8);
	
  cin >> n;

  for(int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

  delaunay();

  long double ret = 0;
  for(tri t : ans){
    long double cur = sqrtl((t[0] - t[1]).sqrl()) * sqrtl((t[1] - t[2]).sqrl()) * sqrtl((t[2] - t[0]).sqrl());
    cur /= 2 * det3(t[0].x, t[0].y, 1, t[1].x, t[1].y, 1, t[2].x, t[2].y, 1);
    ret = max(ret, cur);
  }

  cout << ret << endl;

	return 0;
}