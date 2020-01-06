import java.io.*;
import java.util.*;
import java.lang.*;


class angrys {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("angry.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("angry.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
		int n = Integer.parseInt(st.nextToken()), k = Integer.parseInt(st.nextToken());
		int[] array = new int[n];
		
		for(int i = 0; i < n; i++){
			array[i] = Integer.parseInt(f.readLine());
		}
		
		Arrays.sort(array);
		
		int[][] dp = new int[k][n];
		
		for(int i = 0; i < n; i++){
			dp[0][i] = array[i] - array[0]; 
		}
		
		//System.out.println(Arrays.toString(dp[0]));
		
		for(int i = 1; i < k; i++){
			
			for(int j = 0; j < n; j++){
				dp[i][j] = dp[i-1][j];
				for(int t = 0; t < j; t++){
					dp[i][j] = Math.min(dp[i][j], Math.max(dp[i - 1][t], array[j] - array[t + 1]));
				}
			}
			//System.out.println(Arrays.toString(dp[i]));
		}
     
    	out.println((int)Math.ceil((float)dp[k - 1][n - 1] / 2));
     
        
        out.close();
    }

}