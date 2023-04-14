#include<iostream>
#include <vector>
#include <math.h>
# define pi 3.1415926
using namespace std;

double sinc(double x){
    if(x == 0){
        return 1;
    }
    return sin(x)/x;
}

// CHeck the getHanningWindow function. Here 'n' and 'm' values probably need to be interchanged for the accurate results
vector<double> getHanningWindow(int n){
    vector<double>hann;
    int half, i, index;

    if(n%2 == 0){
        half = n/2;
        for(int i=0; i<half; i++){
            double val = 0.5 * (1 - cos(2 * pi * (i) / (n-1)));
            hann.push_back(val);
        }
        index = half - 1;
        for(int i = half; i < n; i++){
            hann.push_back(hann[index]);
            index--;
        }
    }
    else{
        half = (n+1)/2;
        for(int i=0; i<half; i++){
            double val = 0.5 * (1 - cos(2 * pi * (i) / (n-1)));
            hann.push_back(val);
        }
        index = half - 2;
        for(int i = half; i < n; i++){
            hann.push_back(hann[index]);
            index--;
        }
    }

    return hann;
}     

vector<double> getFIRhigh(int n, double wn, vector<double> hann){
    int m = hann.size();
    double t = wn/pi;
    vector<double> ans;
    int i;

    for(i=0; i<=((m-1)/2); i++){
        double val = hann[i] * (sinc(i*pi) - (t) * sinc(wn*(i - (m-1)/2)));
        ans.push_back(val);
    }
    i = i - 2;
    while(i>-1){
        ans.push_back(ans[i]);
        i--;
    }

    return ans;
}

vector<double> getFIRlow(int n, double wn, vector<double> hann){
    int m = hann.size();
    double t = wn/pi;
    vector<double> ans;
    int i;

    for(i=0; i<=((m-1)/2); i++){
        double val = hann[i] * (t) * sinc(wn*(i - (m-1)/2));
        ans.push_back(val);
    }
    i = i - 2;
    while(i>-1){
        ans.push_back(ans[i]);
        i--;
    }

    return ans;
}

void display(vector <double> x){
    for(int i=0; i<x.size(); i++){
        cout<<x[i]<<" ";
    }
    cout<<endl;
}

void fir_filter(string op){

    if(op != "low" && op != "high"){
        cout<<".....Error in the entered command....";
        return;
    }

    double fp, fs, rp, rs, f;
    cout<<"Enter the pass band frequency : ";
    cin>>fp;

    cout<<"Enter the stop band frequency : ";
    cin>>fs;

    cout<<"Enter the pass band attenuation : ";
    cin>> rp;

    cout<<"Enter the stop band attenuation : ";
    cin>>rs;

    cout<<"Enter the sampling frequency : ";
    cin>>f;

    // To calculate filter order
    double num = -20*log10(sqrt(rp*rs))-13;
    double dem = 14.6*(fs-fp)/f;
    int n = ceil(num/dem);
    n = abs(n);
    // cout<<n<<endl;

    // Normalizing the frequencies
    double wp = 2*(fp/f);
    double ws = 2*(fs/f);
    double wn = (ws+wp)/2;
    // cout<<wn<<endl;

    // Adjusting the filter order.
    // The order of window must be an odd number
    // The order of filter must be one less than that of the window
    int m;
    if(n%2 == 0){
        m = n + 1;
    }
    else{
        m = n;
        n = n-1;
    }    

    // Window Sequence Calculation
    vector<double> hann = getHanningWindow(m);
    // cout<<"These are the hanning window coefficients"<<endl;
    // display(hann);

    // Calculation of filter coefficients
    vector<double>hd;
    if(op == "low"){
        hd = getFIRlow(n, wn, hann);
    }
    else if(op == "high"){
        hd = getFIRhigh(n, wn, hann);
    }
    
    cout<<"These are the FIR filter coeefficients"<<endl;
    display(hd); 
}