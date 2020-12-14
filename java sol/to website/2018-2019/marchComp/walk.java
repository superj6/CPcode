import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class walk {
	public static int[] parent;
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("walk.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("walk.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
 
		int n = Integer.parseInt(st.nextToken()), k = Integer.parseInt(st.nextToken());
 
		parent = new int[n];
 
		ArrayList<Edge> edges = new ArrayList<Edge>();
 
		for(int i = 0; i < n; i++){
			parent[i] = i;
 
			for(int j = i + 1; j < n; j++){
				long mod = 2019201997;
				long a = 2019201913 - mod;
				long b = 2019201949 - mod;
				long distance = ((((i + 1) * a) % mod + ((j + 1) * b) % mod) % mod + mod) % mod;
				edges.add(new Edge(i, j, (int)distance));
			}
		}
 
		Collections.sort(edges);
 
		int lastWeight = 0;
		int numComponents = k;
 
		for(Edge curr : edges){

				lastWeight = curr.w;
 
				if(--numComponents == 0){
					break;
				}
		
		}
 
    	out.println(lastWeight);
 
        out.close();
    }
 
    public static int find(int curr){
    	if(curr == parent[curr]){
    		return curr;
    	}else{
    		return (parent[curr] = find(parent[curr]));
    	}
    }
 
    public static void merge(int x, int y){
    	parent[find(x)] = find(y);
    }
 
    static class Edge implements Comparable<Edge> {
    	public int i, j, w;
 
    	public Edge(int a, int b, int c){
    		i = a;
    		j = b;
    		w = c;
    	}
 
    	public int compareTo(Edge e){
    		return w - e.w;
    	}
    }
 
}