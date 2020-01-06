#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	ifstream fin ("milkorder.in");
	ofstream fout ("milkorder.out");
	
	int n, m, k;
	bool lol = false;
	fin >> n >> m >> k;
	int must[m], place[n], order[n];
	
	
	for(int i = 0; i < n; i++){
		order[i] = -1;	
		place[i] = -1;
	} 
	
	for(int i = 0; i < m; i++){
		fin >> must[i];
		must[i]--;
		if(must[i] == 0) lol = true;
		place[must[i]] = i;
	}
	
	for(int i = 0; i < k; i++){
		int a, b;
		fin >> a >> b;
		a--;
		b--;
		
		if(a == 0){
			fout << (b + 1);
			return 0;
		}
		
		order[b] = a;
	}
	
	int min = -1;
	
	for(int i = 0; i < n; i++){
		
		if(order[i] != -1){
			if(place[order[i]] != -1){
				int curr = place[order[i]] - 1, index = i, newmin = curr + 1;
				
				while(curr > min){
					while(order[index] != -1) index--;
					
					if(must[curr] == 0){
						fout << (index + 1);
						return 0;
					}
					
					order[index] = must[curr];
					
					curr--;
				}
				
				min = newmin;
				
			}
		}
		
	}
	
	if(lol){
		if(min != -1){
			for(int i = 0; i < n; i++){
				if(order[i] == must[min]){
					int extra = 0;
					for(int j = min + 1; j < m; j++){
						while(order[i + j - min + extra] != -1) extra++;
						order[i + j - min + extra] = must[j];
						
						if(must[j] == 0){
							fout << (i + j - min + extra + 1);
							return 0;
						}
					}
					break;
				}
				
			}
			
		}else{
			int extra = 0;
			for(int j = 0; j < m; j++){
				while(order[j - min + extra] != -1) extra++;
				order[j - min + extra] = must[j];
						
				if(must[j] == 0){
					fout << (j - min + extra + 1);
					return 0;
				}
			}
		}
	}
	
	/*
	for(int i = 0; i < n; i++){
		cout << (order[i] + 1) << " ";
	}
	
	cout << endl;
	*/
	
	for(int i = 0; i < n; i++){
		if(order[i] == -1){
			fout << (i + 1);
			return 0;
		}
	}
	
	
	return 0;
}