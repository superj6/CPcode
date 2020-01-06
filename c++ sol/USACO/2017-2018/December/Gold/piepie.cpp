#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int n, d;
vector<int> A, B;
vector<int> dist;

struct cmpA{
	bool operator()(int a, int b){
		return B[a] > B[b];
	}
};

struct cmpB{
	bool operator()(int a, int b){
		return A[a] > A[b];
	}
};

multiset<int, cmpA> sA;
multiset<int, cmpB> sB;

queue<int> q;

int main(){
	ifstream fin ("piepie.in");
	ofstream fout ("piepie.out");
	
	fin >> n >> d;
	A.resize(2 * n);
	B.resize(2 * n);
	dist.resize(2 * n);
	
	for(int i = 0; i < 2 * n; i++){
		fin >> A[i] >> B[i];
		A[i] = A[i], B[i] = B[i];
		dist[i] = -1;
	}
	
	for(int i = 0; i < n; i++){
		if(B[i]==0){
			q.push(i);
			dist[i] = 1;
		}else{
			sA.insert(i);
		}
		
		if(A[i + n]==0){
			q.push(i + n);
			dist[i + n] = 1;
		}else{
			sB.insert(i + n);
		}
	}
	
	multiset<int, cmpA>::iterator itA;
	multiset<int, cmpB>::iterator itB;
	
	
	while(!q.empty()){
		int i = q.front();
		q.pop();
		
		//cout << i << endl;
		
		if(i < n){
			while(true){
				itB = sB.lower_bound(i);
				if(itB == sB.end() || A[*itB] < A[i] - d) break;
				
				dist[*itB] = dist[i] + 1;
				q.push(*itB);
				sB.erase(itB);
			}
		}else{
			while(true){
				itA = sA.lower_bound(i);
				if(itA == sA.end() || B[*itA] < B[i] - d) break;
				
				dist[*itA] = dist[i] + 1;
				q.push(*itA);
				sA.erase(itA);
			}
		}
	}
	
	//cout << endl;
	
	for(int i = 0; i < n; i++) fout << dist[i] << endl;
	
	return 0;
}