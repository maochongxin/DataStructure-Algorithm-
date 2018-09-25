public class UnionFind {
   private Vector<int> pre;
   private int count;
   private int find(int n) {
       if (n != pre.get(n)) {
           pre.set(n, find(pre.get(n)));
       }
       return pre.get(n);
   }
   public UnionFind(int n) {
       pre = new Vector<int>(n);
       for (int i = 0; i < pre.size(); i++) {
           pre.set(i, i);
       }
       count = n;
   }
   public int getCount() {
       return count;
   }
   public boolean isConnected(int x,int y) {
       return pre.get(x) == pre.get(y);
   }
   public void join(int x,int y) {
       int fx = find(x);
       int fy = find(y);
       if (fx != fy) {
           pre.set(fx,pre.get(fy));
       }
       return;
   }
}

