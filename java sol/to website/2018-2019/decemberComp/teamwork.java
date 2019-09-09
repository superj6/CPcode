import java.io.*;
import java.util.*;
import java.lang.*;


public class teamwork {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("teamwork.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("teamwork.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        
        int n = Integer.parseInt(st.nextToken()), k = Integer.parseInt(st.nextToken());
        int[] array = new int[n];
        int[] dp = new int[n];
        
        for(int i = 0; i < n; i++) array[i] = Integer.parseInt(f.readLine());
        
        for(int i = 0; i < n; i++){
            int[] max = new int[k];
            max[0] = array[i];
            for(int j = i - 1; j >= Math.max(i - k + 1, 0); j--){
                max[i - j] = Math.max(array[j], max[i - j - 1]);
            }
            
            //System.out.println(Arrays.toString(max));
            
            for(int j = i; j >= Math.max(i - k + 1, 0); j--){
                if(j - 1 >= 0){
                    dp[i] = Math.max(dp[i], dp[j - 1] + (i - j + 1) * max[i - j]);
                }else{
                    dp[i] = Math.max(dp[i], (i - j + 1) * max[i - j]);
                }
            }
            
        }
        
        //System.out.println(Arrays.toString(dp));
        
        out.println(dp[n - 1]);
        
        out.close();
    }

}