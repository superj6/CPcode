#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
	ifstream fin ("tttt.in");
	ofstream fout ("tttt.out");
	
	bool victor[26][26];
	
	for(int i = 0; i < 26; i++){
		for(int j = 0; j < 26; j++) victor[i][j] = false;
	}
	
	char array[3][3];
	
	for(int i = 0; i < 3; i++){
		fin >> array[i];
	}
	
	int wins[2];
	for(int i = 0; i < 3; i++) wins[i] = 0;
	
	//row
	for(int i = 0; i < 3; i++){
		bool used[26];
		for(int j = 0; j < 26; j++){
			used[j] = false;
		}
		
		for(int j = 0; j < 3; j++){
			used[(int)(array[i][j] - 'A')] = true;
		}
		
		int count = -1;
		
		for(int j = 0; j < 26; j++){
			if(used[j]) count++;
		}
		
		int a = -1, b = -1;
		
		if(count == 0){
			for(int j = 0; j < 26; j++){
				if(used[j]){
					a = j;
					b = j;
					break;
				}
			}
		}
		
		if(count == 1){
			
			for(int j = 0; j < 26; j++){
				if(used[j]){
					if(a == -1){
						a = j;
					}else{
						b = j;
						
						break;
					}
				}
			}

		}
		
		if(count == 2) continue;
		
		if(!victor[a][b]){
			wins[count]++;
			victor[a][b] = true;
		}
	}
	
	//column
	for(int i = 0; i < 3; i++){
		bool used[26];
		for(int j = 0; j < 26; j++){
			used[j] = false;
		}
		
		for(int j = 0; j < 3; j++){
			used[(int)(array[j][i] - 'A')] = true;
		}
		
		int count = -1;
		
		for(int j = 0; j < 26; j++){
			if(used[j]) count++;
		}
		
		int a = -1, b = -1;
		
		if(count == 0){
			for(int j = 0; j < 26; j++){
				if(used[j]){
					a = j;
					b = j;
					break;
				}
			}
		}
		
		if(count == 1){
			
			for(int j = 0; j < 26; j++){
				if(used[j]){
					if(a == -1){
						a = j;
					}else{
						b = j;
						
						break;
					}
				}
			}

		}
		
		if(count == 2) continue;
		
		if(!victor[a][b]){
			wins[count]++;
			victor[a][b] = true;
		}
	}
	
	//diagonal1
	
	bool used[26];
	for(int j = 0; j < 26; j++){
		used[j] = false;
	}
		
	for(int j = 0; j < 3; j++){
		used[(int)(array[j][j] - 'A')] = true;
	}
		
	int count = -1;
		
	for(int j = 0; j < 26; j++){
		if(used[j]) count++;
	}
	
	int a = -1, b = -1;
		
	if(count == 0){
		for(int j = 0; j < 26; j++){
			if(used[j]){
				a = j;
				b = j;
				break;
			}
		}
	}
		
	if(count == 1){
			
		for(int j = 0; j < 26; j++){
			if(used[j]){
				if(a == -1){
					a = j;
				}else{
					b = j;
						
					break;
				}
			}
		}

	}
		
	if(count != 2){
		
		if(!victor[a][b]){
			wins[count]++;
			victor[a][b] = true;
		}
	}
	
	//diagonal2
	for(int j = 0; j < 26; j++){
		used[j] = false;
	}
		
	for(int j = 0; j < 3; j++){
		used[(int)(array[j][2-j] - 'A')] = true;
	}
		
	count = -1;
		
	for(int j = 0; j < 26; j++){
		if(used[j]) count++;
	}
		
	a = -1; 
	b = -1;
		
	if(count == 0){
		for(int j = 0; j < 26; j++){
			if(used[j]){
				a = j;
				b = j;
				break;
			}
		}
	}
		
	if(count == 1){
			
		for(int j = 0; j < 26; j++){
			if(used[j]){
				if(a == -1){
					a = j;
				}else{
					b = j;
						
					break;
				}
			}
		}

	}
		
	if(count != 2){
		
		if(!victor[a][b]){
			wins[count]++;
			victor[a][b] = true;
		}
	}
	
	fout << wins[0] << endl << wins[1] << endl;
	
	return 0;
}