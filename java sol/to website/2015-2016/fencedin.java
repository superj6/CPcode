import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class fencedin {
	public static int n, m;
	public static int[] p;
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("fencedin.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fencedin.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
 
        int a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
		int[] va = new int[n + 1], ha = new int[m + 1];
		for(int i = 0; i < n; i++){
			va[i] = Integer.parseInt(f.readLine());
		}
		for(int i = 0; i < m; i++){
			ha[i] = Integer.parseInt(f.readLine());
		}
 
		Arrays.sort(va);
		Arrays.sort(ha);
		for(int i = 0; i < n; i++){
			va[i] = va[i + 1] - va[i];
		}
		va[n] = b - va[n];
 
    	for(int i = 0; i < m; i++){
			ha[i] = ha[i + 1] - ha[i];
		}
		ha[m] = a - ha[m];

        Arrays.sort(va);
		Arrays.sort(ha);
		n++; m++;
 
		p = new int[n * m];
		for(int i = 0; i < n * m; i++){
			p[i] = i;
		}
 
		long result = 0;
		for(int vi = 0, hi = 0; vi < n || hi < m; ){
			//System.out.println();
			//System.out.println(vi + " " + hi + " " + result);
			//System.out.println(Arrays.toString(p));
			if(hi == m || (vi < n && va[vi] < ha[hi])){
				//System.out.println("a");
				for(int i = 0; i + 1 < m; i++){
					if(merge(nd(vi, i), nd(vi, i + 1))){
						//System.out.println(i);
						//System.out.println(Arrays.toString(p));
						result += va[vi];
					}
				}
				vi++;
			}else{
				//System.out.println("b");
				for(int i = 0; i + 1 < n; i++){
					if(merge(nd(i, hi), nd(i + 1, hi))){
						//System.out.println(i);
						//System.out.println(Arrays.toString(p));
						result += ha[hi];
					}
				}
				hi++;
			}
		}
	out.println(result);
 
        out.close();
    }
 
    public static int nd(int r, int c){
    	return r * m + c;
    }
 
    public static int find(int x){
    	if(x == p[x]){
    		return x;
    	}else{
    		p[x] = find(p[x]);
    		return p[x];
    	}
    }
 
	public static boolean merge(int x, int y){
		int X = find(x);
		int Y = find(y);
		if(X == Y) return false;
		p[X] = p[Y] = p[x] = p[y] = X;
		return true;
	}
}