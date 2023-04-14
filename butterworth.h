#include<iostream>
#include <math.h>
# define Pi 3.1415926
using namespace std;




// void display(vector <double> x){
//     for(int i=0; i<x.size(); i++){
//         cout<<x[i]<<" ";
//     }
//     cout<<endl;
// }

void butterworth(){

    double fp, fs, rp, rs;
    cout<<"Enter the passband frequency edge(in Hz) : ";
    cin>>fp;

    cout<<"Enter the stopband frequency edge(in Hz) : ";
    cin>>fs;

    cout<<"Enter passband ripple(in dB) : ";
    cin>>rp;

    cout<<"Enter stopband attenuation(in dB) : ";
    cin>>rs;

    double wp = 2 * Pi * fp;
    double ws = 2 * Pi * fs;

    int n = log(sqrt((pow(10, -(rs/10))-1)/(pow(10, -(rp/10))-1))) / (log(ws/wp));
    n = n + 1;

    double x = pow(10, (-rs/10)) - 1;
    // cout<<x<<endl;
    double y = double(1)/(2*n);
    // cout<<y<<endl;
    y = pow(x, y);
    double wc = ws/y;
    // cout<<wc<<endl;

    cout<<"         Order of the butterworth filter is "<<n<<endl;
    cout<<"         Cut off frequency of the filter is "<<wc<<endl;   
        
    
}