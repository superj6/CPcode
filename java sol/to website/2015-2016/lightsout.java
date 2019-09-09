import java.io.*;
import java.util.*;
import java.lang.*;
 
 
public class lightsout {
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("lightsout.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lightsout.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
	int n = Integer.parseInt(f.readLine());
    	pair[] graph = new pair[n];
    	StringTokenizer s;
 
    	for(int i = 0; i < n; i++){
    		s = new StringTokenizer(f.readLine());
    		int a = Integer.parseInt(s.nextToken()), b = Integer.parseInt(s.nextToken());
 
    		graph[i] = new pair(a, b);
    	}
 
    	int[] st = new int[2 * n + 1];
    	st[0] = 0;
 
    	for(int i = 0; i < n; i++){
    		int a = 2 * i + 1, b = 2 * i + 2;
 
    		int j = (i + 1) % n, k = (i + 2) % n;
 
    		st[a] = Math.abs(graph[i].getx() - graph[j].getx()) + Math.abs(graph[i].gety() - graph[j].gety());
 
    		int cross = (graph[i].getx() - graph[j].getx()) * (graph[k].gety() - graph[j].gety()) - (graph[k].getx() - graph[j].getx()) * (graph[i].gety() - graph[j].gety());
    		if(cross > 0){
    			st[b] = -1;
    		}else{
    			st[b] = -2;
    		}
    	}
    	st[st.length - 1] = 0;
 
    	int[] opt = new int[n];
 
    	for(int i = 1; i < n; i++){
    		opt[i] = opt[i - 1] + st[2 * i - 1];
    	}
 
    	for(int i = n - 1; i > 0; i--){
    		opt[i] = Math.min(opt[i], opt[(i + 1) % n] + st[2 * i + 1]);
    	}
 
    	//System.out.println(Arrays.toString(opt));
 
        //System.out.println(Arrays.toString(st));
 
        HashMap<String, Integer> map = new HashMap<>();
 
        for(int i = 0; i < st.length; i += 2){
        	for(int ln = 1; i + ln <= st.length; ln += 2){
        		String hey = Arrays.toString(Arrays.copyOfRange(st, i, i + ln));
        		//System.out.println(hey);
        		//System.out.println(i + " " + ln);
        		if(map.containsKey(hey)){
        			map.put(hey, map.get(hey) + 1);
        		}else{
        			map.put(hey, 1);
        		}
        	}
        }
 
        int result = 0;
        for(int i = 2; i + 2 < st.length; i += 2){
        	int ln;
        	int cost = 0;
        	for(ln = 1; ; ln += 2){
        		String hey = Arrays.toString(Arrays.copyOfRange(st, i, i + ln));
        		if(map.get(hey) == 1){
        			break;
        		}
        		//System.out.println(i + " " + ln);
        		cost += st[i + ln];
        	}
 
        	result = Math.max(result, cost + opt[((i + ln)/2)%opt.length] - opt[i / 2]);
        }
 
        out.println(result);
 
        out.close();
    }
 
}
class pair{
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
}