#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <iterator>
using namespace std;

int n, k, r;
int coolnum[31];
vector<int> inputs;
set<string> adj[31];
vector<vector<string>> sentences;

int main(){
	ifstream fin ("nocow.in");
	ofstream fout ("nocow.out");
	
	fin >> n >> k;
	k--;
	sentences.resize(n);
	inputs.resize(n);
	
	for(int i = 0; i < n; i++){
		fin.ignore(19);
		
		string input;
		fin >> input;
		r = 0;
		
		while(input != "cow."){
			adj[r].insert(input);
			sentences[i].push_back(input);
			r++;
			fin >> input;
		}
	}
	
	coolnum[0] = 1;
	for(int i = 0; i < r; i++){
		coolnum[i + 1] = coolnum[i] * adj[r - i - 1].size();
	}
	
	for(int i = 0; i < n; i++){
		inputs[i] = 0;
		for(int j = 0; j < r; j++){
			int c = distance(adj[j].begin(), adj[j].lower_bound(sentences[i][j]));
			inputs[i] += c * coolnum[r - j - 1];
		}
	}
	
	sort(inputs.begin(), inputs.end());
	
	int last = 0, curr = upper_bound(inputs.begin(), inputs.end(), k) - inputs.begin();
	
	while(last != curr){
		k += curr - last;
		last = curr;
		curr = upper_bound(inputs.begin(), inputs.end(), k) - inputs.begin();
	}
	
	vector<string> output(r);
	
	for(int i = 0; i < r; i++){
		set<string>::iterator itr = adj[i].begin();
		advance(itr, k / coolnum[r - i - 1]);
		output[i] = *itr;
		k = k % coolnum[r - i - 1];
	}
	
	for(int i = 0; i < r; i++){
		fout << output[i];
		
		if(i == r - 1) fout << endl;
		else fout << " ";
	}

	return 0;
}