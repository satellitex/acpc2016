#include<bits/stdc++.h>
using namespace std;
int h,w;
bool chx(int a){return a==0||a==w-1;}
bool chy(int a){return a==0||a==h-1;}

int main(){
  char f;
  cin>>h>>w;
  int x[2],y[2],c=0,gx=-1,gy,a=-1,b=max(h,w),t=0;
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++){
      cin>>f;
      if(f=='o'){
	if(c<2)x[c]=j,y[c]=i;
	c++;
	if(gx==-1)a=max(i,j),t=c;
	if(gx!=-1)b=min(b,max(i,j));
      }
      if(f=='@')gx=j,gy=i;
    }
  if(w==1||h==1){
    if(b-t<=max(gx,gy)||a+c-t>=max(gx,gy))cout<<"yes"<<endl;
    else cout<<"no"<<endl;
    return 0;
  }
  if(c==1){
    if((chx(gx)||gx==x[0])&&(chy(gy)||gy==y[0]))cout<<"yes"<<endl;
    else cout<<"no"<<endl;
  }
  if(c==2){
    if(chx(gx)||chy(gy))cout<<"yes"<<endl;
    else if(x[0]==x[1]&&gx==x[0]){
      if(y[0]>y[1])swap(y[0],y[1]);
      if(gy==1||gy==h-2||gy==y[0]+1||gy==y[1]-1)cout<<"yes"<<endl;
      else cout<<"no"<<endl;
    }
    else if(y[0]==y[1]&&gy==y[0]){
      if(x[0]>x[1])swap(x[0],x[1]);
      if(gx==1||gx==w-2||gx==x[0]+1||gx==x[1]-1)cout<<"yes"<<endl;
      else cout<<"no"<<endl;
    }
    else cout<<"no"<<endl;
  }
  if(c>2) cout<<"yes"<<endl;
  return 0;
}

