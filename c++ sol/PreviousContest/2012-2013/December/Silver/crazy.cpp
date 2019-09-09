#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int n, c;
int p = 0, s = 0;

struct point{
	double x, y;
	
	point(double x, double y){
		this->x = x;
		this->y = y;
	}
	
	friend bool operator<(point a, point b){
		return make_pair(a.x,a.y) < make_pair(b.x,b.y); 
	}
};

struct shape{
	int pri = 0;
	vector<int> vertex;
	
	friend bool operator<(shape a, shape b){
		return a.pri > b.pri; 
	}
};

vector<point> points;
vector<bool> used;
vector<int> graph[1000];
map<point, int> pointi;
vector<shape> shapes;

point pointon(point a, point b, point pt){
	if(a.y == b.y){
		if(a.y != pt.y)  return point(-10000000, -10000000);
		else return point((a.x + b.x) / 2, pt.y);
	}
	return point((pt.y - a.y) * (b.x - a.x) / (b.y - a.y) + a.x, pt.y);
}

bool inside(point pt, shape sp){
	pt.y += 0.001;
	int before = 0;
	int k = sp.vertex.size();
	for(int i = 0; i < k; i++){
		point a = points[sp.vertex[i % k]], b = points[sp.vertex[(i + 1) % k]];
		
		point test = pointon(a, b, pt);
		
		if(test.x < pt.x && test.x == b.x && test.y == b.y) continue;
		if(test.x < pt.x && test.x >= min(a.x, b.x) && test.x <= max(a.x, b.x) && test.y >= min(a.y, b.y) && test.y <= max(a.y, b.y)) before++;
		
	}
	
	return before % 2;
}

int main(){
	ifstream fin ("crazy.in");
	ofstream fout ("crazy.out");

	fin >> n >> c;

	for(int i = 0; i < n; i++){
		int a, b;
		double x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		
		if(pointi.find(point(x1, y1)) == pointi.end()){
			pointi[point(x1, y1)] = p;
			points.push_back(point(x1, y1));
			p++;
		}
		
		a = pointi[point(x1, y1)];
		
		if(pointi.find(point(x2, y2)) == pointi.end()){
			pointi[point(x2, y2)] = p;
			points.push_back(point(x2, y2));
			p++;
		}
		
		b = pointi[point(x2, y2)];
		
		graph[a].push_back(b);
		graph[b].push_back(a);
		
		used.push_back(false);
	}
	
	for(int i = 0; i < p; i++){
		if(used[i]) continue;
		
		shapes.push_back(shape());
		
		queue<int> q;
		q.push(i);
		
		while(!q.empty()){
			int cur = q.front();
			q.pop();
			
			shapes[s].vertex.push_back(cur);
			used[cur] = true;
			
			for(int i = 0; i < graph[cur].size(); i++){
				if(!used[graph[cur][i]]){
					q.push(graph[cur][i]);
					break;
				} 
			}
		}
		
		s++;
	}
	
	for(int i = 0; i < s; i++){
		for(int j = i + 1; j < s; j++){
			if(inside(points[shapes[i].vertex[0]], shapes[j])) shapes[i].pri++;
			else if(inside(points[shapes[j].vertex[0]], shapes[i])) shapes[j].pri++;
		}
	}
	
	sort(shapes.begin(), shapes.end());
	
	for(int i = 0; i < s; i++){
		for(int j = 0; j < shapes[i].vertex.size(); j++){
			int cur = shapes[i].vertex[j];
			cout << points[cur].x << " " << points[cur].y << " | ";
		}
		cout << shapes[i].pri << endl;
	}
	
	int community[s + 1];
	int maxv = 0;
	
	for(int i = 0; i <= s; i++) community[i] = 0;
	
	for(int i = 0; i < c; i++){
		int x, y;
		fin >> x >> y;
		point cur = point(x, y);
		
		for(int j = 0; j <= s; j++){
			if(j == s){
				community[j]++;
				maxv = max(maxv, community[j]);
				break;
			}
			
			if(inside(cur, shapes[j])){
				community[j]++;
				maxv = max(maxv, community[j]);
				break;
			}
		}
	}
	
	fout << maxv << endl;

	return 0;
}