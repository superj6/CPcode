import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	static class frac{
		long n, d;
		
		public static long gcd(long a, long b){
			if(b == 0) return a;
			return gcd(b, a % b);
		}
		
		frac(long a, long b){
			n = a;
			d = b;
			
			if(d < 0){
				n *= -1;
				d *= -1;
			}
			
			n /= gcd(Math.abs(a), Math.abs(b));
			d /= gcd(Math.abs(a), Math.abs(b));
		}
		
		frac add(frac a){
			return new frac(n * a.d + a.n * d, d * a.d);
		}
		
		frac mult(frac a){
			return new frac(n * a.n, d * a.d);
		}
		
		frac recip(){
			return new frac(d, n);
		}
		
		public String toString(){
			return "(" + n + " / " + d + ")";
		}
	}
	
	static class matrix{
		int n, m;
		frac[][] f;
		
		matrix(int a, int b){
			n = a;
			m = b;
			f = new frac[a][b];
		}
		
		public static matrix I(int n){
			matrix f = new matrix(n, n);
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					f.set(i, j, i == j ? new frac(1, 1) : new frac(0, 1));
				}
			}
			return f;
		}
		
		void set(int a, int b, frac c){
			f[a][b] = c;
		}
		
		frac get(int a, int b){
			return f[a][b];
		}
		
		matrix add(matrix g){
			if(n != g.n || m != g.m) return new matrix(0, 0);
			matrix ret = new matrix(n, m);
			
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					ret.set(i, j, f[i][j].add(g.get(i, j)));
				}
			}
			
			return ret;
		}
		
		matrix mult(frac g){
			matrix ret = new matrix(n, m);
			
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					ret.set(i, j, f[i][j].mult(g));
				}
			}
			
			return ret;
		}
		
		matrix mult(matrix g){
			if(m != g.n) return new matrix(0, 0);
			matrix ret = new matrix(n, g.m);
			
			for(int i = 0; i < n; i++){
				for(int j = 0; j < g.m; j++){
					ret.set(i, j, new frac(0, 1));
					for(int k = 0; k < m; k++){
						ret.set(i, j, ret.get(i, j).add(f[i][k].mult(g.get(k, j))));
					}
				}
			}
			
			return ret;
		}
		
		matrix inv(){
			if(n != m) return new matrix(0, 0);
			matrix g = this, ret = I(n);
			
			frac chg;
			for(int j = 0; j < m; j++){
				chg = g.get(j, j).recip();
				for(int k = 0; k < n; k++){
						g.set(j, k, g.get(j, k).mult(chg));
						ret.set(j, k, ret.get(j, k).mult(chg));
				}
				
				for(int i = 0; i < n; i++){
					if(i == j) continue;
					chg = g.get(i, j).mult(g.get(j, j).recip()).mult(new frac(-1, 1));
					for(int k = 0; k < m; k++){
						g.set(i, k, g.get(i, k).add(g.get(j, k).mult(chg)));
						ret.set(i, k, ret.get(i, k).add(ret.get(j, k).mult(chg)));
					}
				}
			}
			
			return ret;
		}
		
		public String toString(){
			String s = "";
			for(int i = 0; i < n; i++){
				s += Arrays.toString(f[i]) + "\n";
			}
			return s;
		}
	}
	
	public static int[] solution(int[][] m){
		int n = m.length, k = 0;
		int[] s = new int[n];
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				s[i] += m[i][j];
			}
			if(s[i] > 0) k++;
		}
		
		if(s[0] == 0){
			int[] ret = new int[n - k + 1];
			ret[0] = ret[n - k] = 1;
			return ret;
		}
		
		matrix q = new matrix(k, k);
		matrix r = new matrix(k, n - k);
		for(int i = 0, ci = 0; i < n; i++){
			if(s[i] == 0) continue;
			for(int j = 0, cj = 0; j < n; j++){
				if(s[j] == 0){
					r.set(ci, j - cj, new frac(m[i][j], s[i]));
				}else{
					q.set(ci, cj, new frac(m[i][j], s[i]));
					cj++;
				}
			}
			ci++;
		}
		
		matrix p = matrix.I(k).add(q.mult(new frac(-1, 1))).inv().mult(r);
		
		int[] ret = new int[n - k + 1];
		ret[n - k] = 1;
		for(int i = 0; i < n - k; i++) ret[n - k] = (int)(ret[n - k] * p.get(0, i).d / frac.gcd(ret[n - k], p.get(0, i).d));
		for(int i = 0; i < n - k; i++) ret[i] = (int)(p.get(0, i).n * (ret[n - k] / p.get(0, i).d));
		
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        
        int[][] m1 = {{0, 1, 0, 0, 0, 1}, {4, 0, 0, 3, 2, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
        int[][] m2 = {{0, 2, 1, 0, 0}, {0, 0, 0, 3, 4}, {0, 0, 0, 0, 0}, {0, 0, 0, 0,0}, {0, 0, 0, 0, 0}};
        int[][] m3 = {{0, 0}, {0, 1}};
        
        System.out.println(Arrays.toString(solution(m1)));
        System.out.println(Arrays.toString(solution(m2)));
        System.out.println(Arrays.toString(solution(m3)));
        
        //out.close();
    }

}