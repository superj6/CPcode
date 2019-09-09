import java.io.*;
import java.util.*;
import java.lang.*;


public class comps3 {
    public static char[][] floor;
    public static int[][] rooms;
    public static int n, k;
    public static PrintWriter out;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("mooyomooyo.in"));
        out = new PrintWriter(new BufferedWriter(new FileWriter("mooyomooyo.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        n = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());
        floor = new char[n][10];
        rooms = new int[n][10];
        
        for(int i = 0; i < n; i++){
            floor[i] = f.readLine().toCharArray();
        }
        
        boolean change = true;
        
        while(change){
            change = false;
            
            delgroups();
            
            //printfloor();
            //System.out.println();
            
            for(int j = 0; j < 10; j++){
                int last = -2;
                
                for(int i = n - 1; i >= 0; i--){
                    if(last != -2) if(floor[i][j] != '0'){
                        change = true;
                        floor[last][j] = floor[i][j];
                        floor[i][j] = '0';
                        last--;
                    }
                    
                    if(last == -2 && floor[i][j] == '0'){
                        last = i;
                    }
                }
            }
            
            //printfloor();
            //System.out.println();
        }
        
        printfloor();
        
        out.close();
    }
    
    public static void delgroups(){
        int curr = 0;
        
        for(int i = 0; i < n; i++){
            Arrays.fill(rooms[i], -2);
        }
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 10; j++){
                if(rooms[i][j] == -2){
                    makegroup(i, j, curr);
                    curr++;
                }
            }
        }
        
        int[] count = new int[curr + 1];
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 10; j++){
                count[rooms[i][j]]++;
            }
        }
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 10; j++){
                if(count[rooms[i][j]] >= k){
                    floor[i][j] = '0';
                }
            }
        }
    }
    
    public static void makegroup(int i, int j, int curr){
        rooms[i][j] = curr;
        
        if(i > 0) if(floor[i - 1][j] == floor[i][j] && rooms[i - 1][j] == -2) makegroup(i - 1, j, curr);
        if(j > 0) if(floor[i][j - 1] == floor[i][j] && rooms[i][j - 1] == -2) makegroup(i, j - 1, curr);
        if(i < n - 1) if(floor[i + 1][j] == floor[i][j] && rooms[i + 1][j] == -2) makegroup(i + 1, j, curr);
        if(j < 10 - 1) if(floor[i][j + 1] == floor[i][j] && rooms[i][j + 1] == -2) makegroup(i, j + 1, curr);
    }
    
    public static void printfloor(){
        for(int i = 0; i < n; i++){
            String line = "";
            for(int j = 0; j < 10; j++){
                line += floor[i][j];
            }
            out.println(line);
        }
    }
}
