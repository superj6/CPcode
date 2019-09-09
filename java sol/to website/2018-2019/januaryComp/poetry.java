import java.io.*;
import java.util.*;
import java.lang.*;


public class poetry {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("poetry.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("poetry.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken()), k = Integer.parseInt(st.nextToken());
        int mod = 1000000007;
        int[] wordsyl = new int[n];
        int[] wordrhy = new int[n];
        char[] rhypat = new char[m];
        int[] rhyamount = new int[26];
        long[] dp = new long[k + 1];
        dp[0] = 1;
        HashMap<Integer, Integer> map = new HashMap<>();
        int count = 0;
        
        for(int i = 0; i < n; i++){
            st = new StringTokenizer(f.readLine());
            
            wordsyl[i] = Integer.parseInt(st.nextToken());
            wordrhy[i] = Integer.parseInt(st.nextToken());
            
            if(!map.containsKey(wordrhy[i])){
                map.put(wordrhy[i], count);
                count++;
            }
        }

        for(int i = 0; i < m; i++){
            rhypat[i] = f.readLine().charAt(0);
            rhyamount[rhypat[i] - 'A']++;
        }
        
        for(int i = 0; i < dp.length; i++){
            if(dp[i] == -2) continue;
            for(int j = 0; j < wordsyl.length; j++){
                if(i + wordsyl[j] >= dp.length) continue;
                
                dp[i + wordsyl[j]] = (dp[i + wordsyl[j]] + dp[i]) % mod;

            }
        }
        
        //System.out.println(Arrays.toString(dp));
        
        long[] amount = new long[count];
        
        for(int i = 0; i < wordrhy.length; i++){
            int ind = map.get(wordrhy[i]);
            long mult = dp[dp.length - 1 - wordsyl[i]];
            amount[ind] = (mult + amount[ind]) % mod;
        }
        
        //System.out.println(Arrays.toString(rhyamount));
        long[] predone = new long[n + 1];
        Arrays.fill(predone, -2);
        long output = 1;
        
        for(int i = 0; i < rhyamount.length; i++){
            if(rhyamount[i] == 0) continue;
            int temp = rhyamount[i];
            if(predone[temp] == -2){
                long sum = 0;
                
                for(int j = 0; j < amount.length; j++){
                    if(amount[j] == 0) continue;
                    sum = (sum + modpow(amount[j], temp, mod)) % mod; 
                }
                
                predone[temp] = sum;
            }
            
            output = (output*predone[temp]) % mod;
            
        }
        
        //System.out.println(Arrays.toString(amount));
        
        out.println(output);
     
        
        out.close();
    }
    
    public static long modpow(long num, int pow, long mod){
        long output = 1;
        
        for(int i = 0; i < pow; i++){
            output = (output*num) % mod;
        }
        
        return output;
    }

}