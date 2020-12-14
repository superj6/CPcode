import java.io.*;
import java.util.*;
import java.lang.*;


public class comps1 {
    public static int n, m, c;
    public static int[] t;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("convention.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("convention.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        c = Integer.parseInt(st.nextToken());
        t = new int[n];

        st = new StringTokenizer(f.readLine());
        for(int i = 0; i < n; i++){
          t[i] = Integer.parseInt(st.nextToken());
        }

        Arrays.sort(t);

        out.println(search(0, 1000000000));
        
        out.close();
    }
    
    public static int search(int min, int max){
      int mid = (min + max)/2;
      if(min == max) return min;
      if(min + 1 == max){
        if(possible(min)) return min; 
        return max;
      }
      if(possible(mid)) return search(min, mid);
      return search(mid + 1, max);

    }

    public static boolean possible(int time){
      int buses = 1;
      int firstArrival = t[0];
      int firstIndex = 0;

      for(int i = 1; i < n; i++){
        if(t[i] > firstArrival + time || i + 1 - firstIndex > c){
          buses += 1;
          firstArrival = t[i];
          firstIndex = i;
        }
      }

      return (buses <= m);
      
    }
    
}