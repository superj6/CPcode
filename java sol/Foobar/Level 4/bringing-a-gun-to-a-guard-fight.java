import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;


class Solution {
	
	public static class pair implements Comparable<pair>{
		long x, y;
		public pair(long x, long y){
			this.x = x;
			this.y = y;
		}
		
		long gcd(long a, long b){
			if(b == 0) return a;
			return gcd(b, a % b);
		}
		
		public long dist(){
			return x * x + y * y;
		}
		
		pair red(){
			long g = gcd(Math.abs(x), Math.abs(y));
			if(g == 0) return new pair(x == 0 ? 0 : x / Math.abs(x), y == 0 ? 0 : y / Math.abs(y));
			return new pair(x / g, y / g);
		}
		
		pair add(pair a){
			return new pair(x + a.x, y + a.y);
		}
		
		pair mult(long a){
			return new pair(a * x, a * y);
		}
		
		pair mult(pair a){
			return new pair(x * a.x, y * a.y);
		}
		
		public int compareTo(pair a){
			if(x == a.x){
				return y == a.y ? 0 : y < a.y ? -1 : 1;
			}else{
				return x < a.x ? -1 : 1;
			}
		}
	 
		public String toString(){
			return "(" + x + ", " + y + ")"; 
		}
	}
	
	public static pair[] f = {new pair(1, 0), new pair(0, 1), new pair(-1, 0), new pair(0, -1)};
	public static pair[] g = {new pair(-1, 1), new pair(1, -1), new pair(-1, -1), new pair(1, 1)};
	public static pair[] h = {new pair(1, 0), new pair(0, 1), new pair(1, 1), new pair(0, 0)};
	public static int solution(int ss[], int aa[], int bb[], int dd){
		pair s = new pair(ss[0], ss[1]);
		pair a = new pair(aa[0], aa[1]);
		pair b = new pair(bb[0], bb[1]);
		pair c = b.add(a.mult(-1));
		long d = (long)dd * dd;
		
		int ret = (c.dist() <= d ? 1 : 0);
		TreeSet<pair> used = new TreeSet<pair>();
		used.add(c.red());

		for(int x = 1; Math.min(s.x, s.y) * (2 * x - 2) <= dd; x++){
			for(int i = 0; i < 4; i++){
				pair qa = f[i].mult(2 * x).mult(s);
				pair qb = qa.add(c);
				
				pair ra;
				if(i < 2) ra = qa.add(a.mult(f[i].mult(-2)));
				else ra = qa.add(s.add(a.mult(-1)).mult(f[i].mult(-2)));
				pair rb = ra.add(c.mult(g[i % 2]));
				
				if(rb.dist() < ra.dist()){
					if(!used.contains(rb.red()) && rb.dist() <= d) ret++;
					used.add(rb.red());
					used.add(ra.red());
				}else{
					used.add(ra.red());
					if(!used.contains(rb.red()) && rb.dist() <= d) ret++;
					used.add(rb.red());
				}
				
				if(qb.dist() < qa.dist()){
					if(!used.contains(qb.red()) && qb.dist() <= d) ret++;
					used.add(qb.red());
					used.add(qa.red());
				}else{
					used.add(qa.red());
					if(!used.contains(qb.red()) && qb.dist() <= d) ret++;
					used.add(qb.red());
				}
				
			}
		}
		
		for(int x = 1; s.x * (2 * x - 2) <= dd; x++){
			for(int y = 1; s.mult(new pair(x - 1, y - 1)).mult(2).dist() <= d; y++){
				for(int i = 0; i < 4; i++){
					pair dif = new pair(i % 2 == 0 ? 2 * (s.x - a.x) : -2 * a.x, (i + 3) % 4 < 2 ? 2 * (s.y - a.y) : -2 * a.y);
					
					for(int j = 0; j < 4; j++){
						pair qa = s.mult(new pair(x, y)).mult(2).mult(g[i]).add(dif.mult(h[j]));
						pair qb = qa.add(c.mult(g[j]));
						
						if(qb.dist() < qa.dist()){
							if(!used.contains(qb.red()) && qb.dist() <= d) ret++;
							used.add(qb.red());
							used.add(qa.red());
						}else{
							used.add(qa.red());
							if(!used.contains(qb.red()) && qb.dist() <= d) ret++;
							used.add(qb.red());
						}
					}
				}
			}
		}
		
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

		int[] s = new int[2], a = new int[2], b = new int[2];
		int d;
		
		StringTokenizer st = new StringTokenizer(f.readLine());
		for(int i = 0; i < 2; i++) s[i] = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(f.readLine());
		for(int i = 0; i < 2; i++) a[i] = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(f.readLine());
		for(int i = 0; i < 2; i++) b[i] = Integer.parseInt(st.nextToken());
		
		d = Integer.parseInt(f.readLine());
		
		System.out.println(solution(s, a, b, d));
        
        //out.close();
    }

}