#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;


int main() {
	
	ifstream fin ("bcs.in");
	ofstream fout ("bcs.out");
	
	int n, k;
	fin >> n >> k;
	
	char figure[n][n];
	char piece[k][n][n];
	
	for(int i = 0; i < n; i++){
		fin >> figure[i];
	}
	
	for(int i = 0; i < k; i++){
		for(int j = 0; j < n; j++){
			
			fin >> piece[i][j];
		}
	}
	
	for(int i = 0; i < k; i++){
		for(int j = i + 1; j < k; j++){
			
			for(int tx = -n + 1; tx < n; tx++){
				for(int ty = -n + 1; ty < n; ty++){
					
					for(int sx = -n + 1; sx < n; sx++){
						for(int sy = -n + 1; sy < n; sy++){
							bool out = false;
							
							char piece1[n][n], piece2[n][n];
							
							for(int a = 0; a < n; a++){
								for(int b = 0; b < n; b++){
									piece1[a][b] = '.';
									piece2[a][b] = '.';
								}
							}
							
							for(int a = 0; a < n; a++){
								for(int b = 0; b < n; b++){
									if(a + tx < 0 || a + tx >= n || b + ty < 0 || b + ty >= n){
										if(piece[i][a][b] == '#'){
											out = true;
											break;
										}
									}else{
										piece1[a + tx][b + ty] = piece[i][a][b];
									}
									
									
									if(a + sx < 0 || a + sx >= n || b + sy < 0 || b + sy >= n){
										if(piece[j][a][b] == '#'){
											out = true;
											break;
										}
									}else{
										piece2[a + sx][b + sy] = piece[j][a][b];
									}
									
								}
								if(out) break;
							}
							
							
							
							for(int a = 0; a < n; a++){
								for(int b = 0; b < n; b++){
									
									if(figure[a][b] == '.'){
										if(piece1[a][b] == '#' || piece2[a][b] == '#'){
											out = true;
											break;
										}
									}else{
										if((piece1[a][b] == '.' && piece2[a][b] == '.') || (piece1[a][b] == '#' && piece2[a][b] == '#')){
											out = true;
											break;
										}
									}
									
								}
								if(out) break;
							}
							
							
							if(!out){
								fout << (min(i, j) + 1) << " " << (max(i, j) + 1);
								return 0;
							}
						}	
					}
				}	
			}
			
			
		}
		
		
	}
	
	
	
	cout << "yeet";
	return 0;
	
}