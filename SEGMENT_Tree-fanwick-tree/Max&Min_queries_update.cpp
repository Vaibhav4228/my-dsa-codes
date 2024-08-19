#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2;

int a[N], tree[4 * N];

void build(int node, int st, int en) {
    if (st == en) {
        tree[node] = a[st];
        return;
    }
    int mid = (st + en) / 2;
    build(2 * node, st, mid);
    build(2 * node + 1, mid + 1, en);
    tree[node] = max(tree[2*node], tree[2*node + 1]);
}
int query(int node, int st, int en, int l, int r){
    //yha 2 condition aarga ek complete and second is partial segment
    //base case
    //humara st aur end and l and r overlapp nhi karega toh ans = 0
    if(st > r || en<l) return INT_MIN;

    //case 2
    // l and r ke beech mein st and ed aa rha hai like --->> l st en r
    if(l <=st && en <= r){
        return tree[node];
    }
    //now partial overlap
    //mtlb ki -->> st l  en r yha st aur en partail overlap hai or l st r en ye bhi ho skat hai
    // so iss case mein hum divide and conqure use karenge

    int mid = (st + en) / 2;
    int q1=  query(2 * node, st, mid, l, r);
   int q2=  query(2 * node + 1, mid + 1, en, l, r);
  
   return max(q1, q2);
}
// Updating an element in the segment tree is very similar to binary search. 
// We find out mid, and compare our index with mid and two conditions arise
// 1.	Idx <= mid, then we recursively call the left child of the tree’s node.
// 2.	Idx > mid, then we recursively call the right child of the tree’s node.

void update (int node, int st, int en, int idx, int val){
  if(st == en) {
    a[st] = val;
    tree[node] = val;
    return;
  }
  int mid = (st + en) / 2;
  if(idx<=mid){
  update(2 * node, st, mid, idx, val);
  }
  else{
      update(2 * node + 1, mid + 1, en, idx, val);
  }
  //backtrack
  tree[node] = max(tree[2*node], tree[2*node + 1]);
}
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(1, 0, n - 1);
    while(1){
        int type;
        cin>>type;
        if(type == -1)break;

        if(type ==1){
            int l,r;
            cin>>l>>r;
           int ans = query(1, 0, n-1, l, r);
           cout<<ans<<endl;
        }
        else if(type == 2){
           int idx, val;
           cin>>idx>>val;
           update(1,0,n-1, idx, val); 
           cout<<query(1, 0, n-1, 0, n-1) << endl;
        }

    }
    return 0;
}

// 9
// 6 8 -1 2 17 1 3 2 4
// 1
// 2 6 - ye query hai
// 2
// 7 18 - ye update krni hai 7 index par 18
// -1