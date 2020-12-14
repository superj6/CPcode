import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;


class Solution {
	
	public static int solution(boolean[][] a){
		int n = a.length + 1, m = a[0].length + 1;
		int[][] dp = new int[1 << n][m];
		
		int ret = 0;
		for(int i = 0; i < m; i++){
			for(int j = 0; j < (1 << n); j++){
				if(i == 0) dp[j][i] = 1;
				else{
					for(int k = 0; k < (1 << n); k++){
						boolean t = true;
						for(int l = 0; l < n - 1; l++){
							t &= ((((j >> l) & 1) + ((j >> (l + 1)) & 1) + 
							((k >> l) & 1) + ((k >> (l + 1)) & 1)) == 1) == (a[l][i - 1]);
						}
						if(t) dp[j][i] += dp[k][i - 1];
					}
				}
				if(i == m - 1) ret += dp[j][i];
			}
		}
		
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
		
		int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken());
		boolean[][] a = new boolean[n][m];
		
		for(int i = 0; i < n; i++){
			st = new StringTokenizer(f.readLine());
			for(int j = 0; j < m; j++) a[i][j] = Boolean.parseBoolean(st.nextToken());
		}
     
    	System.out.println(solution(a));
        
        //out.close();
    }

}