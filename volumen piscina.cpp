#include<iostream>
#include<math.h>

using namespace std;


int main(){
	
	double lote;
	double x,y;
	double vol;
	cout<<"Ingrese la cantidad de lotes (MT2): ";cin>>lote;
	
	
	x = 64/(2*(-8)) - sqrt(pow(64,2)-4*(-8)*(8*lote))/(2*(-8));
	

	cout<<"valor positivo: "<<x<<endl;
	
	
	y = lote/(4+x) - 4*x/(4+x);
	
	cout<<y<<endl;
	
	vol = 2*x*y;
	
	
	cout<<"volumen maximo: "<<vol;
	
	
	
}















