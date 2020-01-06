import java.io.*;
import java.util.*;
import java.lang.*;

public class comps2 {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("convention2.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("convention2.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        
        int n = Integer.parseInt(f.readLine()), max = 0;
        int[][] array = new int[n][2];
        Integer[] index = new Integer[n];
        
        for(int i = 0; i < n; i++){
            st = new StringTokenizer(f.readLine());
            array[i][0] = Integer.parseInt(st.nextToken());
            array[i][1] = Integer.parseInt(st.nextToken());
            index[i] = i;
        }
        
        Arrays.sort(index, new Comparator<Integer>(){
            public int compare(Integer i1, Integer i2){
                return Double.compare(array[i1][0], array[i2][0]);
            }
        });
        
        int time = 0;
        
        ArrayList<Integer> in = new ArrayList<>();
        
        for(int i = 0; i < index.length; i++){
            in.add(index[i]);
        }
        
        while(in.size() > 0){
            if(time <= array[in.get(0)][0]){
                time = array[in.get(0)][0];
                time += array[in.get(0)][1];
                
                in.remove(0);
            }else{
                int pri = n;
                
                for(int i = 0; i < in.size(); i++){
                    if(array[in.get(i)][0] > time) break;
                    if(pri == n){
                        pri = i;
                    }else{
                        if(in.get(i) < in.get(pri)) pri = i;
                    }
                }
                
                max = Math.max(max, time - array[in.get(pri)][0]);
                
                time += array[in.get(pri)][1];
                
                in.remove(pri);
            }
            
            //System.out.println(Arrays.toString(in.toArray()) + " " + time);
            
        }
        
        out.println(max);
        
        out.close();
    }
}