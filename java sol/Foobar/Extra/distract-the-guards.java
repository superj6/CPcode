import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	static int n;
	static ArrayList<Integer>[] graph;
	static int qh, qt;
	static int[] p, q, m, b;
	static boolean[] iq, ip, ib;
	
	static int gcd(int x, int y){
		return y == 0 ? x : gcd(y, x % y);
	}
	
	static boolean works(int x, int y){
		int z = (x + y) / gcd(x, y);
		while(z % 2 == 0) z /= 2;
		return z != 1;
	}
	
	static int lca(int u, int v){
		Arrays.fill(ip, false);
		while(true){
			ip[u = b[u]] = true;
			if(m[u] == -1) break;
			u = p[m[u]];
		}
		while(!ip[v = b[v]]) v = p[m[v]];
		return v;
	}
	
	static void mark_blossom(int l, int u){
		while(b[u] != l){
			int v= m[u];
			ib[b[u]] = ib[b[v]] = true;
			u = p[v];
			if(b[u] != l) p[u] = v;
		}
	}
	
	static void blossom(int u, int v){
		int l = lca(u, v);
		Arrays.fill(ib, false);
		mark_blossom(l, u);
		mark_blossom(l, v);
		if(b[u] != l) p[u] = v;
		if(b[v] != l) p[v] = u;
		for(int i = 0; i < n; i++){
			if(ib[b[i]]){
				b[i] = l;
				if(!iq[i]) iq[q[++qt] = i] = true;
			}
		}
	}
	
	static int find_path(int x){
		Arrays.fill(iq, false);
		Arrays.fill(p, -1);
		for(int i = 0; i < n; i++) b[i] = i;
		iq[q[qh = qt = 0] = x] = true;
		
		while(qh <= qt){
			int u = q[qh++];
			for(int v : graph[u]){
				if(b[u] == b[v] || m[u] == v) continue;
				if(v == x || (m[v] != -1 && p[m[v]] != -1)){
					blossom(u, v);
				}else if(p[v] == -1){
					p[v] = u;
					if(m[v] == -1) return v;
					else if(!iq[m[v]]) iq[q[++qt] = m[v]] = true;
				}
			}
		}
		
		return -1;
	}
	
	static int augment(int x){
		int u, v, w;
		for(u = x; u != -1; u = w){
			v = p[u];
			w = m[v];
			m[v] = u;
			m[u] = v;
		}
		return x != -1 ? 1 : 0;
	}
	
	static int edmonds(){
		p = new int[n]; q = new int[n]; m = new int[n]; b = new int[n];
		iq = new boolean[n]; ip = new boolean[n]; ib = new boolean[n];
		
		int ret = 0;
		Arrays.fill(m, -1);
		for(int i = 0; i < n; i++){
			if(m[i] == -1){
				ret += augment(find_path(i));
			}
		}
		
		return ret;
	}
	
	public static int solution(int[] a){
		n = a.length;
		graph = new ArrayList[n];
		
		for(int i = 0; i < n; i++){
			graph[i] = new ArrayList<Integer>();
			for(int j = 0; j < i; j++){
				if(works(a[i], a[j])){
					graph[i].add(j);
					graph[j].add(i);
				} 
			}
		}
		
		return n - 2 * edmonds();
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(f.readLine());
		int[] a = new int[n];
     
    	StringTokenizer st = new StringTokenizer(f.readLine());
    	for(int i = 0; i < n; i++) a[i] = Integer.parseInt(st.nextToken());
    	
    	System.out.println(solution(a));
        
        //out.close();
    }

}