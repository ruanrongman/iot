#include<bits/stdc++.h>
using namespace std;
double search(double a,double b){
	double c = (a+b)/2;
	if (b<0.673){
		cout<<a<<endl;
		cout<<b;
		return 0;
	}
	if((pow(c,3)+1.1*pow(c,2)+0.9*c-1.4)*(pow(b,3)+1.1*pow(b,2)+0.9*b-1.4)<0)
	  search(c,b);
	else search(a,c);
} 
int main()
{
	search(0,1);
	//cout<<pow(2.321222121,3);
	return 0;
}
