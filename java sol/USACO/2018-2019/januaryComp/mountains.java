import java.io.*;
import java.util.*;
import java.lang.*;


public class mountains {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("mountains.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mountains.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int n = Integer.parseInt(f.readLine());
        int count = n;
        int[] x = new int[n], y = new int[n];
        boolean[] use = new boolean[n];
        Arrays.fill(use, true);
        
        for(int i = 0; i < n; i++){
            st = new StringTokenizer(f.readLine());
            x[i] = Integer.parseInt(st.nextToken());
            y[i] = Integer.parseInt(st.nextToken());
        }
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
               if(i == j || !use[i] || !use[j]) continue;
                if(within(x[i], y[i], x[j], y[j])){
                    count--;
                    use[i] = false;
                    break;
                }
            }
        }
        
        out.println(count);
        
        out.close();
    }
    
    public static boolean within(int x, int y, int xcompare, int ycompare){
        return ((y <= x - xcompare + ycompare) && (y <= -1 * x + xcompare + ycompare));
    }

}