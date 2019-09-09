import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class sleepy {
	public static int maxn = 100100;
	public static int[] t = new int[maxn];
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("sleepy.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sleepy.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(f.readLine());
        int[] p = new int[n];
        StringTokenizer st = new StringTokenizer(f.readLine());
 
        for(int i = 0; i < n; i++){
        	p[i] = Integer.parseInt(st.nextToken());
        	p[i]--;
        }
 
        int j = n -1;
 
        while(j > 0 && p[j-1] < p[j]) j--;
        out.println(j);
 
        for(int i = j; i < n; i++){
        	inc(p[i]);
        	//System.out.println(Arrays.toString(t));
        }
        for(int i = 0; i < j; i++){
        	out.print(((j - 1 - i) + getSum(p[i])));
        	if(i < j-1) out.print(" ");
        	inc(p[i]);
        	//System.out.println(Arrays.toString(t));
        }
 
        out.println();
 
 
 
        out.close();
    }
 
    public static void inc(int i){
    	for(i++; i < maxn; i+=(i&-i)){
    		t[i]++;
    	}
    }
 
    public static int getSum(int i){
    	int c = 0;
    	for(i++; i > 0; i-= (i & -i)){
    		c += t[i];
    	}
    	return c;
    }
 
}