import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class visitfj {
	static int[] dr = new int[]{0, 1, 2, 3, 2, 1, 0, -1, -2, -3, -2, -1, -1, 1, 0, 0};
	static int[] dc = new int[]{3, 2, 1, 0, -1, -2, -3, -2, -1, 0, 1, 2, 0, 0, -1, 1};
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("visitfj.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("visitfj.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st = new StringTokenizer(f.readLine());
 
    	int n = Integer.parseInt(st.nextToken()), t = Integer.parseInt(st.nextToken());
        int[][] a = new int[n][n];
 
        for(int i = 0; i < n; i++){
        	st = new StringTokenizer(f.readLine());
        	for(int j = 0; j < n; j++){
        		a[i][j] = Integer.parseInt(st.nextToken());
        	}
        }
 
        int[][] D = new int[n][n];
        for(int i = 0; i < n; i++) Arrays.fill(D[i], Integer.MAX_VALUE);
        D[0][0] = 0;
 
        PriorityQueue<pair> q = new PriorityQueue<>();
        q.add(new pair(0, 0));
 
        int result = Integer.MAX_VALUE;
 
        while(!q.isEmpty()){
        	int d = -q.peek().x;
        	int r = q.peek().y / n;
        	int c = q.peek().y % n;
        	q.poll();
 
        	if(d != D[r][c]){
        		continue;
        	}
 
        	int dist = Math.abs(n - 1 - r) + Math.abs(n - 1 - c);
        	if(dist <= 2){
        		result = Math.min(result, d + dist * t);
        	}
 
        	for(int i = 0; i < dr.length; i++){
        		int nr = r + dr[i];
        		int nc = c + dc[i];
 
        		if(nr < 0 || nr >= n || nc < 0 || nc >= n || D[nr][nc] < d + a[nr][nc] + 3 * t){
        			continue;
        		}
 
        		D[nr][nc] = d + a[nr][nc] + 3 * t;
        		q.add(new pair(-D[nr][nc], nr * n + nc));
        	}
 
        }
 
        out.println(result);
 
        out.close();
    }
 
    static class pair implements Comparable<pair>{
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
 
		public int compareTo(pair f){
			return x - f.x;
		}
	}
 
}