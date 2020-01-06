import java.io.*;
import java.util.*;
import java.lang.*;


class cownav {
	static int[] dx = new int[]{-1, 0, 1, 0};
	static int[] dy = new int[]{0, 1, 0, -1};
	static int n;
	static char[][] grid;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("cownav.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cownav.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	n = Integer.parseInt(f.readLine());
    	grid = new char[n][];
    	
    	for(int i = 0; i < n; i++){
    		grid[i] = f.readLine().toCharArray();
    	}
    	
    	int[][][][][][] dp = new int[n][n][4][n][n][4];
    	dp[n - 1][0][0][n - 1][0][1] = 1;
    	LinkedList<State> q = new LinkedList<State>();
    	q.add(new State(n - 1, 0, 0, n - 1, 0, 1));
    	
    	while(!q.isEmpty()){
    		State curr = q.removeFirst();
    		if(curr.ax == 0 && curr.bx == 0 && curr.ay == n - 1 && curr.by == n - 1){
    			out.println(dp[curr.ax][curr.ay][curr.ad][curr.bx][curr.by][curr.bd] - 1);
    			break;
    		}
    		for(State next: curr.genTransitions()){
    			if(dp[next.ax][next.ay][next.ad][next.bx][next.by][next.bd] == 0){
    				dp[next.ax][next.ay][next.ad][next.bx][next.by][next.bd] = dp[curr.ax][curr.ay][curr.ad][curr.bx][curr.by][curr.bd] + 1;
    			
    				q.add(next);
    			}
    		}
    	}
        
        out.close();
    }
    
    static class State{
    	int ax, ay, ad;
    	int bx, by, bd;
    	
    	public State(int ax, int ay, int ad, int bx, int by, int bd){
    		this.ax = ax;
    		this.ay = ay;
    		this.ad = ad;
    		this.bx = bx;
    		this.by = by;
    		this.bd = bd;
    	}
    	
    	public State[] genTransitions(){
    		return new State[]{
    			turnLeft(),
    			turnRight(),
    			advance(),
    		};
    	}
    	
    	private State turnLeft(){
    		return new State(ax, ay, (ad + 3) % 4, bx, by, (bd + 3) % 4);
    	}
    	private State turnRight(){
    		return new State(ax, ay, (ad + 1) % 4, bx, by, (bd + 1) % 4);
    	}
    	private State advance(){
    		int nax = ax, nay = ay;
    		
    		if(nax != 0 || nay != n - 1){
    			if(nax + dx[ad] >= 0 && nax + dx[ad] < n){
    				nax += dx[ad];
    			}
    			if(nay + dy[ad] >= 0 && nay + dy[ad] < n){
    				nay += dy[ad];
    			}
    			if(grid[nax][nay] == 'H'){
    				nax = ax;
    				nay = ay;
    			}
    		}
    		
    		int nbx = bx, nby = by;
    		
    		if(nbx != 0 || nby != n - 1){
    			if(nbx + dx[bd] >= 0 && nbx + dx[bd] < n){
    				nbx += dx[bd];
    			}
    			if(nby + dy[bd] >= 0 && nby + dy[bd] < n){
    				nby += dy[bd];
    			}
    			if(grid[nbx][nby] == 'H'){
    				nbx = bx;
    				nby = by;
    			}
    		}
    		
    		return new State(nax, nay, ad, nbx, nby, bd);
    		
    	}
    }

}