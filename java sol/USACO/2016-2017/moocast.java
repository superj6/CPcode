import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class moocast {
	public static int[] parent;
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("moocast.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("moocast.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
 
		int n = Integer.parseInt(f.readLine());
		int[] x = new int[n];
		int[] y = new int[n];
 
		for(int i = 0; i < n; i++){
			StringTokenizer st = new StringTokenizer(f.readLine());
			x[i] = Integer.parseInt(st.nextToken());
			y[i] = Integer.parseInt(st.nextToken());
		}
 
		parent = new int[n];
 
		ArrayList<Edge> edges = new ArrayList<Edge>();
 
		for(int i = 0; i < n; i++){
			parent[i] = i;
 
			for(int j = 0; j < i; j++){
				int distance = (int)Math.pow(x[i] - x[j], 2) + (int)Math.pow(y[i] - y[j], 2);
				edges.add(new Edge(i, j, distance));
			}
		}
 
		Collections.sort(edges);
 
		int lastWeight = 0;
		int numComponents = n;
 
		for(Edge curr : edges){
			if(find(curr.i) != find(curr.j)){
				merge(curr.i, curr.j);
				lastWeight = curr.w;
 
				if(--numComponents == 1){
					break;
				}
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