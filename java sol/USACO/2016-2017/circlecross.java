import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class circlecross {
	static int maxn = (1 << 17);
	static int[] bt = new int[maxn];
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("circlecross.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("circlecross.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
 
    	int n = Integer.parseInt(f.readLine());
    	pair[] a = new pair[n];
 
    	for(int i = 0; i < n; i++) a[i] = new pair(-1, -1);
 
    	for(int i = 0; i < 2 * n; i++){
    		int d = Integer.parseInt(f.readLine()) - 1;
 
    		if(a[d].x == -1) a[d].x = i;
    		else a[d].y = i;
    	}
 
    	Arrays.sort(a);
 
    	int result = 0;
        for(int i = 0; i < a.length; i++){
        	result += bit_get(a[i].y) - bit_get(a[i].x);
        	bit_add(a[i].y, 1);
        }
 
        out.println(result);
 
        out.close();
    }
 
    public static void bit_add(int x, int v){
    	for(int i = x | maxn; i < (maxn << 1); i += i & -i){
    		bt[i ^ maxn] += v;
    	}
    }
 
    public static int bit_get(int x){
    	int ret = 0;
    	for(int i = x - 1; x != 0; i &= i - 1){
    		ret += bt[i];
    		if(i == 0) break;
    	}
    	return ret;
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