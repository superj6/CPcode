import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class angry {
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("angry.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("angry.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
	int n = Integer.parseInt(f.readLine());
    	int[] len = new int[n];
 
    	for(int i = 0; i < n; i++){
    		len[i] = Integer.parseInt(f.readLine());
    		len[i] *= 2;
    	}
    	Arrays.sort(len);
 
    	//System.out.println(Arrays.toString(len));
 
    	int[][] dp = new int[2][n];
    	for(int it = 0; it < 2; it++){
    		int lstj = 0;
    		Arrays.fill(dp[it], 1000000);
    		dp[it][0] = -2;
    		for(int i = 1; i < n; i++){
    			while(lstj + 1 < i && Math.abs(len[i] - len[lstj + 1]) > dp[it][lstj + 1] + 2){
    				lstj++;
    			}
    			dp[it][i] = Math.min(Math.abs(len[i] - len[lstj]), dp[it][lstj + 1] + 2);
    		}
    		len = reverse(len);
    		//System.out.println(Arrays.toString(dp[it]));
    	}
    	dp[1] = reverse(dp[1]);
 
    	int i = 0;
    	int j = n-1;
    	int result = Integer.MAX_VALUE;
    	while(i < j){
    		result = Math.min(result, Math.max((len[j] - len[i]) / 2,  2 + Math.max(dp[0][i], dp[1][j])));
    		if(dp[0][i + 1] < dp[1][j - 1]){
    			i++;
    		}else{
    			j--;
    		}
    	}
 
        out.println((result/2) + "." + (result%2 * 5));
 
        out.close();
    }
 
    public static int[] reverse(int[] array){
    	int[] output = new int[array.length];
 
    	for(int i = 0; i < array.length; i++){
    		output[i] = array[array.length - 1 - i];
    	}
 
    	return output;
    }
 
}