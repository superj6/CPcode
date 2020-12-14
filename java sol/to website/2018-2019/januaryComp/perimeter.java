import java.io.*;
import java.util.*;
import java.lang.*;


public class perimeter {
    public static char[][] array;
    public static int[][] blobs;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("perimeter.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("perimeter.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(f.readLine());
        array = new char[n][n];
        
        for(int i = 0; i < n; i++){
            array[i] = f.readLine().toCharArray();
            //System.out.println(Arrays.toString(array[i]));
        }
        
        blobs = new int[n][n];
        
        for(int i = 0; i < n; i++) Arrays.fill(blobs[i], -2);
        
        int count = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(blobs[i][j] == -2 && array[i][j] == '#'){
                    fill(i, j, count, array[i][j]);
                    count++;
                }
            }
        }
        
        //for(int i = 0; i < n; i++) System.out.println(Arrays.toString(blobs[i]));
        
        int[] areas = new int[count], perimeters = new int[count];
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int curr = blobs[i][j];
                if(curr != -2){ 
                    
                    areas[curr]++;
                    
                    if(i == 0){
                        perimeters[curr]++;
                    }else if(blobs[i - 1][j] != blobs[i][j]){
                        perimeters[curr]++;
                    }
                    
                    if(j == 0){
                        perimeters[curr]++;
                    }else if(blobs[i][j - 1] != blobs[i][j]){
                        perimeters[curr]++;
                    }
                    
                    if(i == array.length - 1){
                        perimeters[curr]++;
                    }else if(blobs[i + 1][j] != blobs[i][j]){
                        perimeters[curr]++;
                    }
                    
                    if(j == array.length - 1){
                        perimeters[curr]++;
                    }else if(blobs[i][j + 1] != blobs[i][j]){
                        perimeters[curr]++;
                    }
                }
            }
        }
        
        int area = 0, perimeter = 0;
        
        for(int i = 0; i < areas.length; i++){
            if(areas[i] > area || (areas[i] == area && perimeters[i] < perimeter)){
                area = areas[i];
                perimeter = perimeters[i];
            }
        }
        
        out.println(area + " " + perimeter);
        
        out.close();
    }
    
    public static void fill(int x, int y, int num, char type){
        if(x >= array.length || x < 0 || y >= array.length || y < 0) return;
        if(blobs[x][y] != -2 || array[x][y] != type) return;
        
        blobs[x][y] = num;
        
        fill(x + 1, y, num, type);
        fill(x - 1, y, num, type);
        fill(x, y + 1, num, type);
        fill(x, y - 1, num, type);
    }

}
