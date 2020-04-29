/*
 * we will use dp on tree to know the next node j the node i will go to 
 * using sparse table we will know the node j the node i will go to after 2^k moves
 * because of strict memory limit we will not fill a table sparse[N][60] then jump the node , instead we will use rolling table and jump the node during it 
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+9;
const ld pai=acos(-1);
int n ; ll k ;
vi v [300009] ;
int a [300009] , nxt [300009][2] ;
pi dpdn [300009] , dpup[300009] ;
pi Max ( pi x , pi y ) {
	if ( x.fi == y.fi ) {
		if ( x.se < y.se ) return x ;
		return y ;
	}
	if ( x.fi > y.fi ) return x ;
	return y ;
}
void dfs1 ( int node , int p ) {
	for ( auto u : v [node] ) {
		if ( u == p ) C ;
		dfs1 ( u , node ) ;
		pi cost = Max ( dpdn[u] , { a[u] , u } ) ;
		cost .fi -- ;
		dpdn [node] = Max ( dpdn[node] , cost ) ;
	}
}
void dfs2 ( int node , int p ) {
	pair < pi , int > mx1,mx2 ;
	mx1 = mx2 = { { -1e9 , -1e9 } , -1e9 } ;
	for ( auto u : v [node] ) {
		if ( u == p ) C ;
		pi cost = Max ( dpdn [u] , { a[u] , u } ) ;
		if ( Max ( cost , mx1.fi ) == cost ) {
			swap ( mx1 , mx2 ) ;
			mx1 = { cost , u } ;
		}
		else if ( Max ( cost , mx2.fi ) == cost ) {
			mx2 = { cost , u } ;
		}
	}
	mx1 .fi.fi -=2 ;
	mx2 .fi.fi -=2 ;
	for ( auto u : v [node] ) {
		if ( u == p ) C ;
		pi cost = Max ( dpup [node] , { a[node] , node } ) ;
		cost .fi -- ;
		if ( u != mx1.se ) cost = Max ( cost , mx1.fi ) ;
		else cost = Max ( cost , mx2.fi ) ;
		dpup [u] = cost ;
		dfs2 ( u , node ) ;
	}
}
int main () {
	scanf("%d%lld",&n,&k) ;
	for ( int i = 0 ; i < n ; i ++ ) scanf("%d",&a[i]) ; 
	for ( int i = 0 ; i < n-1 ; i ++ ) {
		int a , b ;
		scanf("%d%d",&a,&b);
		a -- , b -- ;
		v [a] .pb ( b ) ;
		v [b] .pb ( a ) ;
	}
	for ( int i = 0 ; i < n ; i ++ ) dpdn [i] = dpup [i] = { -1e9 , -1e9 } ;
	dfs1 ( 0 , 0 ) ;
	dfs2 ( 0 , 0 ) ;
	int node = 0 ;
	for ( int i = 0 ; i < n ; i ++ ) {
		int id = Max ( dpdn [i] , dpup [i] ) .se ;
		nxt [i][0] = id ;
		if ( !node && ( k & 1 ) ) node = nxt[node][0] ;
	}
	for ( ll j = 1 ; j <= 60 ; j ++ ) {
		int id1 = j % 2 ;
		int id2 = 1 - id1 ;
		int z = 0 ;
		for ( int i = 0 ; i < n ; i ++ ) {
			nxt [i][id1] = nxt [ nxt[i][id2] ][id2] ;
			if ( ( k & ( (ll)1 << j ) ) && i == node && !z ) node = nxt[i][id1] , z = 1 ;
		}
	}
	cout << node + 1 << endl ;
}

