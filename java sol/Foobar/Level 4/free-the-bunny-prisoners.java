import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	public static int nx(int x){
		long u = x & -x;
		long v = x + u;
		return (int)(v + (((v ^ x) / u) >> 2));
	}
	
	public static int[][] solution(int n, int m){
		ArrayList<Integer>[] ans = new ArrayList[n];
		for(int i = 0; i < n; i++) ans[i] = new ArrayList<Integer>();
		
		if(m > 1){
			for(int i = (1 << (m - 1)) - 1, c = 0; i < (1 << n); i = nx(i), c++){
				for(int j = 0; j < n; j++){
					if((i & (1 << j)) == 0){
						ans[n - j - 1].add(c);
					}
				}
			}
		}else if(m == 1){
			for(int i = 0; i < n; i++){
				ans[i].add(0);
			}
		}
		
		int k = ans[0].size();
		int[][] ret = new int[n][k];
		for(int i = 0; i < n; i++){
			for(int j = 0; j < k; j++){
				ret[i][j] = ans[i].get(j);
			}
		}
		
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	int n = Integer.parseInt(f.readLine()), m = Integer.parseInt(f.readLine());
    	
    	int[][] ret = solution(n, m);
    	
    	for(int i = 0; i < ret.length; i++) System.out.println(Arrays.toString(ret[i]));
        
        //out.close();
    }

}