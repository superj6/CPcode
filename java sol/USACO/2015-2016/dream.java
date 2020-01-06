import java.util.*;
import java.lang.*;
import java.io.*;
 
/* Name of the class has to be "Main" only if the class is public. */
public class dream {
	static final int N = 1005;
 
	static int[][] tile;
	static int[][][] visited;
	static int[][] dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	static int n, m;
 
	static PriorityQueue<Pair<Integer, Pair<Integer, Pair<Integer, Integer>>>> q;
 
	public static void main(String[] args) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("dream.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("dream.out")));
		StringTokenizer st = new StringTokenizer(f.readLine());
 
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		q = new PriorityQueue<>();
 
		tile = new int[N][N];
		visited = new int[N][N][2];
 
		for (int i=0; i<n; ++i) {
			st = new StringTokenizer(f.readLine());
			for (int j=0; j<m; ++j) {
				int color = Integer.parseInt(st.nextToken());
				tile[i][j] = color;
				visited[i][j][0] = visited[i][j][1] = 100000000;
			}
		}
		q.add(fromInts(0, 0, 0, 0));
 
		while (q.size() > 0) {
			Pair<Integer, Pair<Integer, Pair<Integer, Integer>>> front = q.remove();
			int dist = front.left;
			int x = front.right.left;
			int y = front.right.right.left;
			int isSmelly = front.right.right.right;
 
			if (x == m-1 && y == n-1) {
				out.println(dist);
				out.close();
				return;
			}
			if (visited[y][x][isSmelly] != 100000000) {
				continue;
			}
			visited[y][x][isSmelly] = dist;
 
			for (int i=0; i<dirs.length; ++i) {
				int nx = x + dirs[i][0];
				int ny = y + dirs[i][1];
				int nd = dist + 1;
				int nSmelly = isSmelly;
 
				if (!isPathable(nx, ny, isSmelly)) continue;
 
				if (tile[ny][nx] == 4) {
					while (isPathable(nx + dirs[i][0], ny + dirs[i][1], isSmelly) &&
							tile[ny][nx] == 4) {
						nx += dirs[i][0];
						ny += dirs[i][1];
						nd ++;
						nSmelly = 0;
					}
				}
				if (tile[ny][nx] == 2) {
					nSmelly = 1;
				}
				if (visited[ny][nx][nSmelly] <= nd) continue;
				q.add(fromInts(nd, nx, ny, nSmelly));
			}
		}
		out.println("-1");

		out.close();
	}
	public static boolean isPathable(int x, int y, int smellsNice) {
		if (x < 0 || x >= m || y < 0 || y >= n) return false;
		if (tile[y][x] == 0) return false;
		if (tile[y][x] == 3) return (smellsNice > 0);
 
		return true;
	}
	public static Pair<Integer, Pair<Integer, Pair<Integer, Integer>>> fromInts(int a, int b, int c, int d) {
		Pair<Integer, Integer> p1 = new Pair<>(c, d);
		Pair<Integer, Pair<Integer, Integer>> p2 = new Pair<>(b, p1);
		return new Pair<>(a, p2);
	}
}
class Pair<L extends Comparable<L>, R> implements Comparable<Pair<L, R>> {
	public L left;
	public R right;
 
	public Pair(L left, R right) {
		this.left = left;
		this.right = right;
	}
	public int compareTo(Pair<L, R> other) {
		return this.left.compareTo(other.left);
	}
}