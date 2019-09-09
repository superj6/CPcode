import java.io.*;
import java.util.*;
import java.lang.*;
 
 
public class radio {
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("radio.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("radio.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
 
		int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(f.readLine());
		int fx = Integer.parseInt(st.nextToken()), fy = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(f.readLine());
		int bx = Integer.parseInt(st.nextToken()), by = Integer.parseInt(st.nextToken());
 
		char[] fmove = f.readLine().toCharArray();
		char[] bmove = f.readLine().toCharArray();
 
		HashMap<Character, Integer> map = new HashMap<>();
		map.put('N', 3);
		map.put('E', 1);
		map.put('S', 2);
		map.put('W' , 0);
 
		int[][] dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
 
		pair[] fpath = new pair[n + 1];
		pair[] bpath = new pair[m + 1];
 
		fpath[0] = new pair(fx, fy);
		bpath[0] = new pair(bx, by);
 
		for(int i = 1; i < fpath.length; i++){
			fpath[i] = new pair(fpath[i-1].getx() + dirs[map.get(fmove[i - 1])][0], fpath[i-1].gety() + dirs[map.get(fmove[i - 1])][1]);
		}
 
		for(int i = 1; i < bpath.length; i++){
			bpath[i] = new pair(bpath[i-1].getx() + dirs[map.get(bmove[i - 1])][0], bpath[i-1].gety() + dirs[map.get(bmove[i - 1])][1]);
		}
 
		//System.out.println(Arrays.toString(fpath));
		//System.out.println(Arrays.toString(bpath));
 
		int[][] weight = new int[n + 1][m + 1];
 
		for(int i = 0; i < n + 1; i++){
			for(int j = 0; j < m + 1; j++){
				weight[i][j] = (int)Math.pow(fpath[i].getx() - bpath[j].getx(), 2) + (int)Math.pow(fpath[i].gety() - bpath[j].gety(), 2);
			}
 
			//System.out.println(Arrays.toString(weight[i]));
		}
 
		int[][] dp = new int[n + 1][m + 1];
		dp[0][0] = weight[0][0];
 
		for(int i = 0; i < n + 1; i++){
			for(int j = 0; j < m + 1; j++){
				if(i == 0){
					if(j != 0) dp[i][j] = weight[i][j] + dp[i][j - 1];
				}else if(j == 0){
					dp[i][j] = weight[i][j] + dp[i - 1][j];
				}else{
					dp[i][j] = weight[i][j] + Math.min(dp[i-1][j-1], Math.min(dp[i-1][j], dp[i][j-1]));
				}
			}
 
			//System.out.println(Arrays.toString(dp[i]));
		}
 
		out.println((dp[n][m] - weight[0][0]));
		out.close();
    }
 
}
 
class pair{
	int x, y;
	public pair(int x, int y){
		this.x = x;
		this.y = y;
	}
 
	public int getx(){
		return x;
	}
 
	public int gety(){
		return y;
	}
 
	public void setx(int x){
		this.x = x;
	}
 
	public void sety(int y){
		this.y = y;
	}
 
	public String toString(){
		return "(" + x + ", " + y + ")"; 
	}
}