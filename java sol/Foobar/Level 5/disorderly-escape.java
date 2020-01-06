import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	static class par{
		int l;
		int[] p;
		
		par(int l){
			p = new int[l];
			p[0] = l;
			this.l = 1;
		}
		
		int get(int x){
			return p[x];
		}
		
		boolean works(){
			return p[0] != 0;	
		}
		
		void nxt(){
			if(p[0] == 1){
				p[0] = 0;
				return;
			}
			
			int c = 0;
			while(p[l - 1] == 1){
				c++;
				l--;	
			} 
			
			c++;
			p[l - 1]--;
			for(; c > 0; l++){
				p[l] = Math.min(p[l - 1], c);
				c -= p[l];
			}
		}
		
		public String toString(){
			String s = "";
			for(int i = 0; i < l; i++) s += p[i] + " ";
			return s;
		}
	}

	public static int gcd(int x, int y){
		if(y == 0) return x;
		return gcd(y, x % y);
	}
	
	public static String solution(int n, int m, int k){
		BigInteger f = BigInteger.ONE;
		for(int i = 1; i <= n; i++) f = f.multiply(BigInteger.valueOf(i));
		for(int i = 1; i <= m; i++) f = f.multiply(BigInteger.valueOf(i));
		
		
		BigInteger ret = BigInteger.ZERO;
		for(par x = new par(n); x.works(); x.nxt()){
			for(par y = new par(m); y.works(); y.nxt()){
				int e = 0;
				for(int i = 0; i < x.l; i++){
					for(int j = 0; j < y.l; j++){
						e += gcd(x.get(i), y.get(j));
					}
				}
				
				BigInteger cur = f.multiply(BigInteger.valueOf(k).pow(e));
				
				for(int i = 0, c = 1; i < x.l; i++, c++){
					cur = cur.divide(BigInteger.valueOf(x.get(i)).multiply(BigInteger.valueOf(c)));
					if(i != x.l - 1 && x.get(i) != x.get(i + 1)) c = 0;
				} 
				for(int i = 0, c = 1; i < y.l; i++, c++){
					cur = cur.divide(BigInteger.valueOf(y.get(i)).multiply(BigInteger.valueOf(c)));
					if(i != y.l - 1 && y.get(i) != y.get(i + 1)) c = 0;
				} 
				
				ret = ret.add(cur);
			}
		}
		
		return ret.divide(f).toString();
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
		
    	int n = Integer.parseInt(st.nextToken());
    	int m = Integer.parseInt(st.nextToken());
    	int k = Integer.parseInt(st.nextToken());
    	
    	System.out.println(solution(n, m, k));
        
        //out.close();
    }

}