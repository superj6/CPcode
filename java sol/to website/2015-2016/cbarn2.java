import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class cbarn2 {
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("cbarn2.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cbarn2.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
 
		long N = Long.parseLong(st.nextToken()), K = Long.parseLong(st.nextToken());
		long[] a = new long[(int)N];
		long[][] dp = new long[(int)(K + 1)][(int)N + 1];
 
    	for(int i = 0; i < N; i++){
    		a[i] = Long.parseLong(f.readLine());
    	}
 
        long result = Integer.MAX_VALUE - 1000000;
 
        for(int i = 0; i < N; i++){
        	for(int g = 0; g < dp.length; g++) Arrays.fill(dp[g], Integer.MAX_VALUE - 1000000);
        	dp[0][(int)N] = 0;
 
        	for(int k = 1; k <= K; k++){
        		for(int j = 0; j < N; j++){
        			long val = 0;
        			for(int b = j + 1; b <= N; b++){
        				val += a[b-1] * (b - j - 1);
        				dp[k][j] = Math.min(dp[k][j], val + dp[k - 1][b]);
        			}
        		}
        	}
 
        	result = Math.min(result, dp[(int)K][0]);
 
 
        	//System.out.println(Arrays.toString(a));
        	//System.out.println();
        	//for(int g = 0; g < dp.length; g++) System.out.println(Arrays.toString(dp[g]));
        	//System.out.println();
        	a = rotate(a);
 
        }
 
        out.println(result);
        out.close();
    }
 
    public static long[] rotate(long[] array){
    	long[] output = new long[array.length];
 
    	for(int i = 0; i < array.length; i++){
    		output[(i + 1) % array.length] = array[i];
    	}
 
    	return output;
    }
 
}