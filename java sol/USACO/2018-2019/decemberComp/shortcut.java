
import java.io.*;
import java.util.*;
import java.lang.*;


public class shortcut {
    public static long totaltime = 0;
    public static int[] cowamount;
    public static String[] path; 
    public static int[] change;
    public static int[] dista;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("shortcut.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shortcut.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        
        int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken()), t = Integer.parseInt(st.nextToken());
        
        int[][] graph = new int[n][n];
        cowamount = new int[n];
        path = new String[n];
        st = new StringTokenizer(f.readLine());
        for(int i = 0; i < n; i++){
            cowamount[i] = Integer.parseInt(st.nextToken());
        }
        
        for(int i = 0; i < n; i++){
            Arrays.fill(graph[i], 100000);
            graph[i][i] = 0;
        } 
        
        change = new int[n];
        
        for(int i = 0; i < m; i++){
            st = new StringTokenizer(f.readLine());
            int a = Integer.parseInt(st.nextToken()) - 1, b = Integer.parseInt(st.nextToken()) - 1, ter = Integer.parseInt(st.nextToken());
            
            graph[a][b] = ter;
            graph[b][a] = ter;
        }
        
        /*
        for(int i = 0; i < n; i++){
            System.out.println(Arrays.toString(graph[i]));
        } 
        */
        
        totaltime = dijkstra(graph, 0);
        
        long output = 0;
        
        newdist2(graph, t);
        
        for(int i = 1; i < n; i++){
            long test = change[i];
            output = Math.max(output, test);
        }
        
        //System.out.println(Arrays.toString(change));
        
        out.println(output);
     
        
        out.close();
    }
    
    public static void newdist2(int[][] graph, int shortlen){
        StringTokenizer st;
        
        for(int i = 1; i < graph.length; i++){
            st = new StringTokenizer(path[i]);
            
            while(st.hasMoreTokens()){
                int in = Integer.parseInt(st.nextToken());
                
                if(shortlen < dista[in]){
                    change[in] += (dista[in] - shortlen) * (cowamount[in]);
                }
            }
        }
        
    }

    
    public static long dijkstra(int[][] graph, int source){
        int[] dist = new int[graph.length];
        Arrays.fill(dist, 100000);
        dist[source] = 0;
        boolean[] visited = new boolean[dist.length];
        int previous = source;
        int[] prev = new int[dist.length];
        Arrays.fill(prev, -2);
        
        path[0] = "0";
        
        for(int i = 0; i < dist.length - 1; i++){
            visited[previous] = true;
            int min = 100000, index = -2;
            
            for(int j = dist.length - 1; j >= 0; j--){
                if(previous == j) continue;
                
                if(!visited[j]){
                    int test = dist[previous] + graph[previous][j];
                    if(dist[j] >= test){
                        if(dist[j] == test){
                            if(previous < prev[j]) prev[j] = previous;
                        }else{
                            prev[j] = previous;
                        }
                        
                        dist[j] = test;
                    }
                    
                    if(dist[j] < min){
                        min = dist[j];
                        index = j;
                    }
                }
                
            }
            
            previous = index;
            
            path[index] = path[prev[index]] + " " + Integer.toString(index);
        }
        
        long sum = 0;
        
        dista = dist.clone();
        
        //System.out.println(Arrays.toString(dist));
        
        for(int i = 0; i < dist.length; i++) sum += dist[i] * cowamount[i];
        
        return sum;
        
        
    }

}
