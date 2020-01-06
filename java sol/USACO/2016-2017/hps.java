import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class hps {
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("hps.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hps.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
 
		int n = Integer.parseInt(st.nextToken()), k = Integer.parseInt(st.nextToken());
		int[] moves = new int[n];
		int[][][] dp = new int[n + 1][k + 1][3];
 
		for(int i = 0; i < n; i++){
			char hey = f.readLine().charAt(0);
			if(hey == 'H') moves[i] = 0;
			if(hey == 'P') moves[i] = 1;
			if(hey == 'S') moves[i] = 2;
		}
 
		for(int i = 0; i <= n; i++){
			for(int j = 0; j <= k; j++){
				for(int state = 0; state < 3; state++){
					if(i == 0){
						dp[i][j][state] = 0;
					}else{
						if(j == 0){
							dp[i][j][state] = dp[i - 1][j][state] + (moves[i - 1] == state ? 1 : 0);
						}else{
							int ostate1 = (state + 1) % 3;
							int ostate2 = (state + 2) % 3;
 
							dp[i][j][state] = Math.max(Math.max(dp[i-1][j][state], dp[i-1][j-1][ostate1]), dp[i-1][j-1][ostate2]) + (moves[i-1] == state ? 1 : 0);
						}
 
					}
				}
			}
 
		}
 
 
    	out.println(Math.max(Math.max(dp[n][k][0], dp[n][k][1]), dp[n][k][2]));
 
        out.close();
    }
 
}