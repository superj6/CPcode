import java.io.*;
import java.util.*;
import java.lang.*;


class lightson {

    static int[] dx = new int[]{0, 1, 0, -1};
    static int[] dy = new int[]{1, 0, -1, 0};

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("lightson.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lightson.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st = new StringTokenizer(f.readLine());

        int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken()); 
        ArrayList<pair>[][] edges = new ArrayList[n][n];    	

        for(int i = 0; i < m; i++){
            st = new StringTokenizer(f.readLine());
	    int x = Integer.parseInt(st.nextToken()) - 1, y = Integer.parseInt(st.nextToken()) - 1;
	    int a = Integer.parseInt(st.nextToken()) - 1, b = Integer.parseInt(st.nextToken()) - 1;
	
	    if(edges[x][y] == null) edges[x][y] = new ArrayList<pair>();

            edges[x][y].add(new pair(a, b));
      	  
        }
	boolean[][] graph = new boolean[n][n], litgraph = new boolean[n][n];
	litgraph[0][0] = true;
        graph[0][0] = true;
        
        int result = 1;

        LinkedList<pair> list = new LinkedList<>();
        list.add(new pair(0, 0));

        while(!list.isEmpty()){
        	//System.out.println(Arrays.toString(list.toArray()));
	        	
	        pair curr = list.poll();
	        if(edges[curr.x][curr.y] != null){
	        ArrayList<pair> test = edges[curr.x][curr.y];
	        for(pair now: test){
	            if(!litgraph[now.x][now.y]){
	            	result++;
	            	litgraph[now.x][now.y] = true;
	            	
	            	
	            	for(int i = 0; i < 4; i++){
			            int x0 = now.x + dx[i];
				    	int y0 = now.y + dy[i];
			
			            if(x0 >= 0 && y0 >= 0 && x0 < n && y0 < n){
				            if(graph[x0][y0]){
				            	list.add(new pair(now.x, now.y));
				            	graph[now.x][now.y] = true;
				        	}
			        	}
			        }
	            	
	            	
		    	}
	        }

        }
        
	        for(int i = 0; i < 4; i++){
	            int x0 = curr.x + dx[i];
		    	int y0 = curr.y + dy[i];
	
	            if(x0 >= 0 && y0 >= 0 && x0 < n && y0 < n){
		            if(litgraph[x0][y0] && !graph[x0][y0]){
		            	list.add(new pair(x0, y0));
		            	graph[x0][y0] = true;
		        	}
	        	}
	        }
        }
        out.println(result);
        //System.out.println();
        //for(int i = 0; i < n; i++) System.out.println(Arrays.toString(graph[i]));
        
       // System.out.println();
       // for(int i = 0; i < n; i++) System.out.println(Arrays.toString(litgraph[i]));
        
        out.close();
    }

    static class pair{
      	int x, y;

      	public pair(int x, int y){
            this.x = x;
	    this.y = y;
     	}
     	
     	public String toString(){
     		return "(" + x + ", " + y + ")";
     	}
    }

}