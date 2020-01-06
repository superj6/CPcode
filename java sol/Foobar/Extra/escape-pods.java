import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	final static int inf = 1000000007;
	static int n;
	static int[] h, x;
	static int[][] flow, graph;
	
	static void push(int u, int v){
		int d = Math.min(x[u], graph[u][v] - flow[u][v]);
		flow[u][v] += d;
		flow[v][u] -= d;
		x[u] -= d;
		x[v] += d;
	}
	
	static void relabel(int u){
		int d = inf;
		for(int i = 0; i < n; i++){
			if(flow[u][i] < graph[u][i]) d = Math.min(d, h[i]);
		}
		if(d < inf) h[u] = d + 1;
	}
	
	static ArrayList<Integer> fmax(){
		ArrayList<Integer> ret = new ArrayList<Integer>();
		for(int i = 1; i < n - 1; i++){
			if(x[i] == 0) continue;
			if(!ret.isEmpty() && h[i] > h[ret.get(0)]) ret.clear();
			if(ret.isEmpty() || h[i] == h[ret.get(0)]) ret.add(i);
		}
		return ret;
	}
	
	public static int solution(int[] s, int[] t, int[][] g){
		n = g.length + 2;
		h = new int[n];
		x = new int[n];
		flow = new int[n][n];
		graph = new int[n][n];
		
		h[0] = n;
		x[0] = inf;
		for(int i : s){
			x[i + 1] = inf;
			flow[0][i + 1] = graph[0][i + 1] = inf;
			flow[i + 1][0] = -inf;
		} 
		for(int i : t) graph[i + 1][n - 1] = inf;
		
		for(int i = 0; i < n - 2; i++)
		for(int j = 0; j < n - 2; j++){
			graph[i + 1][j + 1] = g[i][j];
		}
		
		ArrayList<Integer> cur;
		while(!(cur = fmax()).isEmpty()){
			for(int i : cur){
				boolean p = false;
				for(int j = 0; j < n && x[i] > 0; j++){
					if(flow[i][j] < graph[i][j] && h[i] == h[j] + 1){
						push(i, j);
						p = true;
					}
				}
				if(!p){
					relabel(i);
					break;
				}
			}
		}
		
		int ret = 0;
		for(int i = 0; i < n; i++) ret += flow[0][i];
		
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        
		int[] s = {0, 1};
		int[] t = {4, 5};
		int[][] g = {{0, 0, 4, 6, 0, 0}, {0, 0, 5, 2, 0, 0}, {0, 0, 0, 0, 4, 4}, {0, 0, 0, 0, 6, 6}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
		
		System.out.println(solution(s, t, g));
        
        //out.close();
    }

}