import java.io.*;
import java.util.*;
import java.lang.*;


public class sleepy {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("sleepy.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sleepy.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(f.readLine());
        int[] array = new int[n], reverse = new int[n];
        StringTokenizer st = new StringTokenizer(f.readLine());
        
        for(int i = 0; i < n; i++){
            array[i] = Integer.parseInt(st.nextToken()) - 1;
            reverse[array[i]] = i;
        }
        
        int[] placement = new int[n];
        int[] change = new int[n];
        Arrays.fill(placement, -2);
        
        for(int i = n - 1; i > 1; i--){
            for(int j = 0; j < n; j++){
                if(reverse[j] < i && j > array[i] && placement[reverse[j]] == -2){
                    placement[reverse[j]] = i;
                }
            }

            if(array[i] < array[i - 1]){
                
                for(int j = 0; j < i; j++){
                    if(reverse[j] < i && j < array[i] && placement[reverse[j]] == -2){
                        placement[reverse[j]] = i - 1;
                    }
                }
                
                break;
            }
            
        }
        
        System.out.println(Arrays.toString(placement));
        
        for(int i = 0; i < n; i++){
            if(placement[i] != -2){
                change[i] = placement[i] - i;
            }
        }
        
        int[] newchange = new int[n];
        
        String output = "";
        
        for(int i = 0; i < n; i++){
            newchange[i] += change[i];
            for(int j = i + 1; j <= i + change[i]; j++){
                if(array[j] > array[i]) newchange[j] += 1;
            }
        }
        
        for(int i = 0; i < n; i++){
            if(newchange[i] == 0){
                out.println(i);
                break;
            }else if(i != 0) output+= " ";
            
            output += Integer.toString(newchange[i]);
        }
        
        out.println(output);
        
        out.close();
    }

}