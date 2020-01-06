import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class lasers {
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("lasers.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lasers.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        int n = Integer.parseInt(st.nextToken());
        int x1 = Integer.parseInt(st.nextToken()), y1 = Integer.parseInt(st.nextToken());
        int x2 = Integer.parseInt(st.nextToken()), y2 = Integer.parseInt(st.nextToken());
 
        Map<Line, Integer> dist = new HashMap<Line, Integer>();
		LinkedList<Line> q = new LinkedList<Line>();
 
		q.add(new Line(y1, true));
		dist.put(new Line(y1, true), 0);
		q.add(new Line(x1, false));
		dist.put(new Line(x1, false), 0);
 
		Map<Integer, ArrayList<Integer>> xtoY = new HashMap<Integer, ArrayList<Integer>>();
		Map<Integer, ArrayList<Integer>> ytoX = new HashMap<Integer, ArrayList<Integer>>();
 
        for(int i = 0; i < n; i++){
        	st = new StringTokenizer(f.readLine());
        	int x = Integer.parseInt(st.nextToken());
        	int y = Integer.parseInt(st.nextToken());
        	if(!xtoY.containsKey(x)){
        		xtoY.put(x, new ArrayList<Integer>());
        	}
        	xtoY.get(x).add(y);
        	if(!ytoX.containsKey(y)){
        		ytoX.put(y, new ArrayList<Integer>());
        	}
        	ytoX.get(y).add(x);
        }
 
        int ret = -1;
        while(!q.isEmpty()){
        	Line curr = q.removeFirst();
 
        	if(curr.horizontal && curr.val == y2){
        		ret = dist.get(curr);
        		break;
        	}
        	if(!curr.horizontal && curr.val == x2){
        		ret = dist.get(curr);
        		break;
        	}
 
        	Map<Integer, ArrayList<Integer>> source;
        	if(curr.horizontal) source = ytoX;
        	else source = xtoY;
 
        	if(source.containsKey(curr.val)){
        		for(int dest : source.get(curr.val)){
        			Line nextLine = new Line(dest, !curr.horizontal);
 
        			if(!dist.containsKey(nextLine)) {
        				dist.put(nextLine, dist.get(curr) + 1);
        				q.add(nextLine);
        			}
        		}
        	}
        }
 
        out.println(ret);
 
        out.close();
    }
 
    static class Line{
    	public int val;
    	public boolean horizontal;
 
    	public Line(int val, boolean horizontal){
    		super();
    		this.val = val;
    		this.horizontal = horizontal;
    	}
 
    	@Override
    	public int hashCode(){
    		return Objects.hash(horizontal, val);
    	}
    	@Override
    	public boolean equals(Object obj){
    		if(this == obj) return true;
    		if(obj == null) return false;
    		if(getClass() != obj.getClass()) return false;
    		Line other = (Line) obj;
    		if(horizontal != other.horizontal) return false;
    		if(val != other.val) return false;
    		return true;
    	}
    }
 
}