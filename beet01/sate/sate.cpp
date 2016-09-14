#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef complex<ld> P;
typedef pair<P,P> L;
int N,K;
const ld EPS = 1e-9;
ld area(vector<P> v){
  ld sum = 0.0;
  int n = v.size();
  for(int i=0;i<n;i++) sum += (real(v[i]) - real(v[(i+1)%n])) * (imag(v[i]) + imag(v[(i+1)%n]));
  return abs(sum) / 2.0;
};

ld cross(P a, P b){ return   a.real() * b.imag() - a.imag() * b.real(); }

P crossPoint(L l, L m){
  ld A = cross(l.second - l.first, m.second - m.first);
  ld B = cross(l.second - l.first, l.second - m.first);
  if(abs(A) < EPS && abs(B) < EPS) return m.first;
  else if(abs(A) >= EPS) return m.first + B / A * (m.second - m.first);
}

ld m_p( vector<P> &p ){
  L a = L( p[0], p[K] );
  L b = L( p[1], p[N+1-K] );
  P c = crossPoint( a, b );
  vector<P> s(3); s[0] = p[0]; s[1] = p[1]; s[2] = c;
  return area( s );
}

int main(){    
  cin >> N >> K;

  vector<P> pos;
  ld ang = 0.0;
  for(int i=0;i<N;i++){
    pos.push_back( P( cos(ang), sin(ang) ) );
    ang += 2.0 * M_PI / (ld)N;
  }
  //  cout << area( pos ) << " - " << m_p ( pos ) << " * " << N << endl;
  printf("%.8Lf\n", area( pos ) - m_p ( pos ) * (ld)N );    
}

