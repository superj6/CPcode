import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class closing {
	public static int[] par;
 
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("closing.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("closing.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
 
		int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken());
		int[] order = new int[n + 1], place = new int[n + 1], u = new int[m], v = new int[m];
		par = new int[n + 1];
		boolean[] res = new boolean[n];
 
		for(int i = 0; i < m; i++){
			st = new StringTokenizer(f.readLine());
			u[i] = Integer.parseInt(st.nextToken());
			v[i] = Integer.parseInt(st.nextToken());
		}
 
		for(int i = 0; i < n; i++){
			order[i] = Integer.parseInt(f.readLine());
			place[order[i]] = i;
		}
 
		LinkedList<Integer>[] adj = new LinkedList[n + 1];
		for(int i = 0; i < adj.length; i++) adj[i] = new LinkedList<>();
 
        for(int i = 0; i < m; i++){
        	if(place[u[i]] > place[v[i]]){ adj[v[i]].add((Integer)u[i]);
        	}else adj[u[i]].add((Integer)v[i]);
        }
 
        union_init(par, n + 1);
        int comps = 0;
 
        for(int i = n - 1; i >= 0; i--){
        	int u1 = order[i];
        	comps ++;
        	for(int j = 0; j < adj[u1].size(); j++){
        		int v1 = adj[u1].get(j);
 
        		if(union_query(par, u1) != union_query(par, v1)) {
        			union_merge(par, u1, v1);
        			comps--;
        		}
        	}
 
        	res[i] = (comps <= 1);
        }
 
        for(int i = 0; i < n; i++){
        	if(res[i]) out.println("YES");
        	else out.println("NO");
        }
 
 
 
 
 
        out.close();
    }
 
    public static void union_init(int d[], int s){
    	for(int i = 0; i < s; i++) d[i] = i;
    }
 
    public static int union_query(int d[], int n){
    	int res = n;
    	while(d[res] != res) res = d[res];
 
    	int m;
    	while(d[n] != n){
    		m = d[n];
    		d[n] = res;
    		n = m;
    	}
 
    	return res;
    }
 
    public static boolean union_merge(int d[], int x, int y){
    	x = union_query(d, x);
    	y = union_query(d, y);
    	if(x == y) return false;
    	d[x] = y;
    	return true;
    }
 
}