import java.io.*;
import java.util.*;
import java.lang.*;


public class dining {
    public static int[] dist1, dist2;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("dining.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("dining.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        
        int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken()), ka = Integer.parseInt(st.nextToken());
        int[][] graph = new int[n][n];
        int[] hay = new int[n];
        Arrays.fill(hay, -100000);
        for(int i = 0; i < n; i++) Arrays.fill(graph[i], 1000000);
        for(int i = 0; i < n; i++) graph[i][i] = 0;
        dist1 = new int[n];
        dist2 = new int[n];
        
        for(int i = 0; i < m; i++){
            st = new StringTokenizer(f.readLine());
            int a = Integer.parseInt(st.nextToken()) - 1, b = Integer.parseInt(st.nextToken()) - 1, t = Integer.parseInt(st.nextToken());
            
            graph[a][b] = t;
            graph[b][a] = t;
        }
        
        for(int i = 0; i < ka; i++){
            st = new StringTokenizer(f.readLine());
            int a = Integer.parseInt(st.nextToken()) - 1, t = Integer.parseInt(st.nextToken());
            
            hay[a] = t;
        }
        
        dijkstra(graph, n-1, dist1);
        
        for(int i = 0; i < n - 1; i++){
            graph[n-1][i] = dist1[i] - hay[i];
            graph[i][n-1] = 100000;
        }
        
        //for(int i = 0; i < n; i++) System.out.println(Arrays.toString(graph[i]));
        
        dijkstra(graph, n-1, dist2);
        
        for(int i = 0; i < n - 1; i++){
            for(int j = 0; j < n - 1 ; j++){
                dist2[i] = Math.min(dist2[i], dist1[i] + 2*dist1[j] - hay[j]);
            }
        }
        
        
        //System.out.println();
        //System.out.println(Arrays.toString(dist1));
        //System.out.println(Arrays.toString(dist2));
        
        for(int i = 0; i < n - 1; i++){
            if(dist1[i] >= dist2[i]){
                out.println(1);
            }else{
                out.println(0);
            }
        }
        
        
        
        out.close();
    }
    
    public static void dijkstra(int[][] graph, int source, int[] dist){
        Arrays.fill(dist, 100000);
        dist[source] = 0;
        boolean[] visited = new boolean[dist.length];
        int previous = source;
        
        for(int i = 0; i < dist.length - 1; i++){
            visited[previous] = true;
            int min = 100000, index = -2;
            
            for(int j = 0; j < dist.length; j++){
                if(previous == j) continue;
                
                if(!visited[j]){
                    int test = dist[previous] + graph[previous][j];
                    if(dist[j] > test){
                        dist[j] = test;
                    }
                    
                    if(dist[j] < min){
                        min = dist[j];
                        index = j;
                    }
                }
                
            }
            
            previous = index;
        }
        
        
    }

}