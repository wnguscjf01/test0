#include<bits/stdc++.h>
#define MAXN 300001
using namespace std;
typedef long long int ll;
ll h[MAXN], t1[MAXN], t2[MAXN];
struct data{
	ll val; int ind;
};
struct data h1[MAXN], h2[MAXN];
bool cmp(const struct data &a, const struct data &b){
	if(a.val==b.val) return a.ind < b.ind;
	return a.val < b.val;
}
set<pair<int,ll> > s;
set<pair<int,ll> > s::iterator si;
int main()
{
	int t, n, i, j;
	cin >> t;
	for(i=1; i<=t; i++){
		scanf("%d",&n);
		for(j=1; j<=n; j++) scanf("%lld",&h[j]);
		for(j=1; j<=n; j++){
			h1[j].val=h[j]+j; h1[j].ind=j;
		}
		for(j=n; j>=1; j--){
			h2[j].val=h[j]+n-j+1; h2[j].ind=j;
		}
		sort(h1+1,h1+n+1,cmp);
		sort(h2+1,h2+n+1,cmp);
		s.clear();
		s.insert({h1[1].ind,h1[1].val});
		t1[h1[1].ind] = n*h1[1].val;
		for(j=2; j<=n; j++){
			si=s.upper_bound({h1[j],h1[j].val});
			if(si==s.begin()){
				t1[h1[j].ind]=h1[j].val*h1[j].ind;
				continue;
			}
			si--;
			
		}
	}
	
	return 0;
}

