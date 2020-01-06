import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class snakes {
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("snakes.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("snakes.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
 
		int n = Integer.parseInt(st.nextToken()), k = Integer.parseInt(st.nextToken());
		int[] groups = new int[n]; //stores input
		st = new StringTokenizer(f.readLine());
 
		for(int i = 0; i < n; i++){
			groups[i] = Integer.parseInt(st.nextToken());
		}
 
		//System.out.println(Arrays.toString(groups));
		//System.out.println();
 
 
    	int[][] maxv = new int[n][n]; //max in interval (length - 1, start_index)
    	maxv[0] = groups.clone();
 
    	for(int i = 1; i < n; i++){
    		for(int j = 0; j < n - i; j++){
    			maxv[i][j] = Math.max(maxv[i - 1][j], maxv[i - 1][j + 1]);
    		}
    	}
    	//for(int i = 0; i < n; i++) System.out.println(Arrays.toString(maxv[i]));
    	//System.out.println();
 
 
        int[][] sum = new int[n][n]; // sum in interval (length - 1, start_index)
        sum[0] = groups.clone();
 
        for(int i = 1; i < n; i++){
    		for(int j = 0; j < n - i; j++){
    			sum[i][j] = sum[i - 1][j] + groups[i + j];
    		}
    	}
    	//for(int i = 0; i < n; i++) System.out.println(Arrays.toString(sum[i]));
    	//System.out.println();
 
 
    	int[][] waste = new int[n][n]; // waste in interval (length - 1, start_index)
 
        for(int i = 0; i < n; i++){
    		for(int j = 0; j < n - i; j++){
    			waste[i][j] = maxv[i][j] * (i + 1) - sum[i][j];
    		}
    	}
    	//for(int i = 0; i < n; i++) System.out.println(Arrays.toString(waste[i]));
    	//System.out.println();
 
 
    	int[][] dp = new int[k + 1][n]; // min val obtained with for (changes, to_index)
        for(int i = 0; i < k; i++) Arrays.fill(dp[i], 1000000);
        for(int i = 0; i < n; i++) dp[0][i] = waste[i][0];
 
        for(int i = 1; i <= k; i++){
        	for(int j = 0; j < n; j++){
        			dp[i][j] = dp[i - 1][j];
        		for(int w = 1; w <= j; w++){
        			dp[i][j] = Math.min(dp[i][j], dp[i - 1][w - 1] + waste[j - w][w]);
        		}
        	}
        }
 
        //for(int i = 0; i <= k; i++) System.out.println(Arrays.toString(dp[i]));
    	//System.out.println();
 
 
    	out.println(dp[k][n - 1]);
 
        out.close();
    }
 
}