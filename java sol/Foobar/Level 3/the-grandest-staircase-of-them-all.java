import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {

	public static int solution(int n){
		int[] dp = new int[n + 1];
		dp[0] = 1;
		
		for(int i = 1; i < n; i++){
			for(int j = n - i; j >= 0; j--){
				dp[j + i] += dp[j];
			}
		}
		
		return dp[n];
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	int n = Integer.parseInt(f.readLine());
    	
    	System.out.println(solution(n));
        
        //out.close();
    }

}