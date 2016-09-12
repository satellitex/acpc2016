#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> P;
int H,W;
char fie[20][20];

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

set<vector<P>> used;

bool isok(const vector<P>& v){
  for( P p : v ) 
    if( fie[p.first][p.second] == '@' ) return true;
  return false;
}

int isng( P p, const vector<P> &v ){
  if( p.first < 0 || p.second < 0 || p.first >= W || p.second >= H ) return -1;
  for(int i=0;i<(int)v.size();i++)
    if( v[i] == p ) return i+1;
  return 0;
}

vector<P> move( const vector<P> &v, int i, int d ){
  vector<P> ret = v;
  while( true ){
    P nx = ret[i];
    nx.first += dx[d]; nx.second += dy[d];
    int ng = isng( nx, v );
    if( ng ) {
      if( ng > 0 )
        return move( ret, ng-1, d );
      break;
    }
    ret[i] = nx;
  }
  return ret;
}

bool check(const vector<P> &v){
  if( used.count( v ) ) return false;
  if( isok( v ) ) return true;
  used.insert( v );  
  for(int i=0;i<(int)v.size();i++){
    for(int j=0;j<4;j++){
      vector<P> nx = move( v, i, j );
      sort( nx.begin(), nx.end() );
      if( check( nx ) ) return true;
    }
  }
  return false;
}

int main(){
  
  vector<P> ps;
  cin >> H >> W;
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      cin >> fie[j][i];
      if( fie[j][i] == 'o' )
        ps.push_back( P(j,i) );
    }    
  }
  sort( ps.begin(), ps.end() );
  if( H>1 && W>1 && ps.size() > 2 ){
    cout << "yes" << endl;
  } else if( check(ps) ) cout << "yes" << endl;
  else cout << "no" << endl;
  
  
}
