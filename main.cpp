#include "butterworth.h"
#include "fir_filter.h"
#include "fft_dft.h"

void takeInputs(complex input_seq[], int N){
    for(int i=0; i<N; i++){
        double real, image;
        cout<<"Enter X["<<i<<"] real and imaginary part seperated by a space : ";
        cin>>real>>image;        
        input_seq[i] = complex(real, image);
        cout<<endl;
    }
}

void help(){
    cout<<"                  DSP C++ LIBRARY PROGRAM\n"          
          "                 COLLEGE OF ENGINEERING PUNE\n"
          "         DEPT OF ELECTRONICS AND TELECOMMUNICATION ENGINEERING\n"
          "                 Developed By - MOHIT KUMBHARE\n"
          "                     MIS - 112007031\n"
            "           USE THE FOLLOWING COMMANDS: \n"
            "help                           Open helpdesk\n"
            "dft                            Calculate DFT of a sequence\n"
            "fft                            Calculate FFT of a sequence(Uses DIT as a default)\n"
            "fft-dit                        Calculate FFT of a sequence using DIT algorithm\n"
            "fft-dif                        Calculate FFT of a sequence using DIF algorithm\n"
            "fir-low                        Design a low pass FIR filter\n"
            "fir-high                       Design a high pass FIR filter\n"
            "butter                         To find order and cut off frequency of a butterworth filter\n"
            "exit                           Exit the program\n"<<endl;
}              
                    
int main(){
    string fun;
    cout<<"                  DSP C++ LIBRARY PROGRAM\n"          
          "                 COLLEGE OF ENGINEERING PUNE\n"
          "         DEPT OF ELECTRONICS AND TELECOMMUNICATION ENGINEERING\n"
          "                 Developed By - MOHIT KUMBHARE\n"
          "                     MIS - 112007031\n"
            "START ENTERING THE COMMANDS\n";

    
    cin>>fun;

    while(fun != "exit"){
        if(fun == "help"){
            help();
            cin>>fun;
        }

        else if(fun == "dft"){
            int dft_dit_dif = 1;
            int N_max;
            cout<<"     Enter the size of the sequence :    "<<endl;
            cin>> N_max;

            complex* input_seq = new complex[N_max];
            takeInputs(input_seq, N_max);

            validate_result(input_seq, N_max, dft_dit_dif);
            cin>>fun;
        }

        else if(fun == "fft" || fun == "fft-dit"){
            int dft_dit_dif = 2;
            int N_max;
            cout<<"     Enter the size of the sequence :    "<<endl;
            cin>> N_max;

            complex* input_seq = new complex[N_max];
            takeInputs(input_seq, N_max);

            validate_result(input_seq, N_max, dft_dit_dif);
            cin>>fun;
        }

        else if(fun == "fft-dif"){
            int dft_dit_dif = 3;
            int N_max;
            cout<<"     Enter the size of the sequence :    "<<endl;
            cin>> N_max;

            complex* input_seq = new complex[N_max];
            takeInputs(input_seq, N_max);

            validate_result(input_seq, N_max, dft_dit_dif);
            cin>>fun;
        }
        
        else if(fun == "fir-low"){
            fir_filter("low");
            cin>>fun;
        }

        else if(fun == "fir-high"){
            fir_filter("high");
            cin>>fun;
        } 

        else if(fun == "butter"){
            butterworth();
            cin>>fun;
        }       

        else{
            cout<<"         WRONG COMMAND ENTERED!!!!"<<endl;
            cout<<"     Type 'help' for commands or 'exit' to exit the program.";
        }
    }
             
    return 0;
}