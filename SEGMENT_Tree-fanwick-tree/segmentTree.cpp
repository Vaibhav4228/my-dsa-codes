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
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}
int query(int node, int st, int en, int l, int r){
    //yha 2 condition aarga ek complete and second is partial segment
    //base case
    //humara st aur end and l and r overlapp nhi karega toh ans = 0
    if(st > r || en<l) return 0;

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
  
   return q1 + q2;
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

    }
    return 0;
}

//input
// //8
// 5 3 2 4 1 8 6 10  <<-- array
// 1
// 1 5  << query in index 1 to 5
// -1 << -1 break ke liye

//output - 3+2+4+1+8 = 18