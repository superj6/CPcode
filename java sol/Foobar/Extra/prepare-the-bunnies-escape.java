import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	static int n, m;
	static int[] dx = {0, 1, 0, -1};
	static int[] dy = {1, 0, -1, 0};
	
	static boolean works(int x, int y){
		return x >= 0 && y >= 0 && x < n && y < m;
	}
	
	public static int solution(int[][] a){
		n = a.length; m = a[0].length;
		
		int[][][] dp = new int[n][m][2];
		for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
		for(int k = 0; k < 2; k++){
			dp[i][j][k] = n * m;
		} 
		dp[0][0][0] = dp[0][0][1] = 1;
		
		Queue<Integer> q = new LinkedList<>();
		q.add(0);
		
		while(!q.isEmpty()){
			int x = q.peek() / m, y = q.poll() % m;
			for(int i = 0; i < 4; i++){
				int nx = x + dx[i], ny = y + dy[i];
				if(works(nx, ny)){
					if(a[nx][ny] == 0){
						if(dp[x][y][0] + 1 < dp[nx][ny][0]){
							dp[nx][ny][0] = dp[x][y][0] + 1;
							if(dp[nx][ny][0] < dp[nx][ny][1]) dp[nx][ny][1] = dp[nx][ny][0];
							q.add(nx * m + ny);
						}else if(dp[x][y][1] + 1 < dp[nx][ny][1]){
							dp[nx][ny][1] = dp[x][y][1] + 1;
							q.add(nx * m + ny);
						}
					}else if(a[x][y] == 0){
						if(dp[x][y][0] + 1 < dp[nx][ny][1]){
							dp[nx][ny][1] = dp[x][y][0] + 1;
							q.add(nx * m + ny);
						}
					}
				}
			}	
		}
		
		return dp[n - 1][m - 1][1];
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
		
		int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken());
		
		int[][] a = new int[n][m];
		for(int i = 0; i < n; i++){
			st = new StringTokenizer(f.readLine());
			for(int j = 0; j < m; j++){
				a[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
    	System.out.println(solution(a));
        
        //out.close();
    }

}