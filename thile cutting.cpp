#include<bits/stdc++.h>
#define MAXN 500001
using namespace std;
typedef long long int ll;
const double pi = acos(-1);
ll k;
pair<ll,int> d[4*MAXN];
int spf[MAXN];
vector<int> pr;
int FFT(vector<complex<double> > &v, complex<double> w){
	int len=v.size(), i;
	if(len==1) return 0;
	vector<complex<double> > even(len/2), odd(len/2);
	for(i=0; i<len; i++){
		if(i%2==0) even[i/2]=v[i];
		else odd[i/2]=v[i];
	}
	FFT(even, w*w);
	FFT(odd, w*w);
	complex<double> wp(1,0);
	for(i=0; i<len/2; i++){
		v[i]=even[i] + wp*odd[i];
		v[i+len/2] = even[i] - wp*odd[i];
		wp*=w;
	}
	return 0;
}
pair<ll,int> maxp(pair<ll,int> a, pair<ll,int> b){
	if(a.first==b.first){
		if(a.second < b.second) return a;
		return b;
	}
	if(a.first<b.first) return b;
	return a;
}
pair<ll,int> gmax(int l, int r){
	l=k-1+l; r=k-1+r;
	pair<ll,int> ret=d[l];
	while(l<=r){
		if(l%2==1) ret=maxp(ret,d[l++]);
		if(r%2==0) ret=maxp(ret,d[r--]);
		l/=2; r/=2;
	}
	return ret;
}
int main()
{
	int n, i, j;
	for(i=2; i<MAXN; i++){
		if(spf[i]==0){
			pr.push_back(i); spf[i]=i;
		}
		for(j=0; i*pr[j]<MAXN; j++){
			spf[i*pr[j]]=pr[j];
			if(pr[j]==spf[i]) break;
		}
	}
	
	k=1;
	while(k<2*MAXN) k*=2;
	vector<complex<double> > v1(k,{0,0}), v2(k,{0,0});
//	printf("done1\n");
	for(i=1; i<MAXN; i++){
		ll tmp=1, ii=i, cnt=0, prv=0;
		while(ii>1){
			if(spf[ii]!=prv){
				tmp*=cnt+1;
				cnt=0;
				prv=spf[ii];
			}
			cnt++;
			ii/=spf[ii];
		}
		tmp*=cnt+1;
		v1[i]={tmp,0}; v2[i]={tmp,0};
	}
//	printf("done2\n");
	complex<double> w(cos(2*pi/k), sin(2*pi/k));
	FFT(v1,w);
	FFT(v2,w);
	vector<complex<double> > mul(k,{0,0});
	for(i=0; i<k; i++) mul[i] = v1[i]*v2[i];
	complex<double> wbar;
	wbar={w.real(),-w.imag()};
	FFT(mul,wbar);
	for(i=0; i<k; i++) mul[i]={mul[i].real()/k,mul[i].imag()};
//	printf("done3\n");
	k=1;
	while(k<MAXN) k*=2;
	for(i=1; i<MAXN; i++){
	//	printf("%d\n",i);
		d[k-1+i] = {(ll) (mul[i].real()+0.3),i};
	}
//	printf("done4\n");
	for(i=k-1; i; i--) d[i]=maxp(d[i*2],d[i*2+1]);
	cin >> n;
	for(i=1; i<=n; i++){
		int l, r;
		scanf("%d%d",&l,&r);
		pair<ll,int> tmp=gmax(l,r);
		printf("%d %lld\n",tmp.second, tmp.first);
	}
	
	return 0;
}

