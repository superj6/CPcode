import java.io.*;
import java.util.*;
import java.lang.*;


public class pract1 {
    public static int[][][] array;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("billboard.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("billboard.out")));
        //BufferedReader t = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        
        array = new int[3][2][2];
        
        for(int i = 0; i < 3; i++){
            st = new StringTokenizer(f.readLine());
            array[i][0][0] = Integer.parseInt(st.nextToken());
            array[i][0][1] = Integer.parseInt(st.nextToken());
            array[i][1][0] = Integer.parseInt(st.nextToken());
            array[i][1][1] = Integer.parseInt(st.nextToken());
        }
        
        long outt = (array[0][1][0] - array[0][0][0]) * (array[0][1][1] - array[0][0][1]) + (array[1][1][0] - array[1][0][0]) * (array[1][1][1] - array[1][0][1]);
        
        outt -= overlap(0) + overlap(1);
            
        out.println(outt);
            
        out.close();
    }
    
    public static long overlap(int n){
        if(array[2][0][0] >= array[n][1][0] || array[2][1][0] <= array[n][0][0] || array[2][0][1] >= array[n][1][1] || array[2][1][1] <= array[n][0][1]) return 0;
        
        return (Math.min(array[2][1][1], array[n][1][1]) - Math.max(array[2][0][1], array[n][0][1])) * (Math.min(array[2][1][0], array[n][1][0]) - Math.max(array[2][0][0], array[n][0][0]));
    }
}