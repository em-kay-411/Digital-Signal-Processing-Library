# include <stdio.h>
# include <stdlib.h>
# include <cmath>
# include <iostream>
# include <ctime>
# define PI 3.1415926
using namespace std;

typedef struct Complex
{
	double re;
	double im;
	Complex() {
		re = 0;
		im = 0;
	};
	Complex(double a,double b) {
		re = a;
		im = b;
	};
} complex;





// Multiplier
complex complexProduct(complex c1, complex c2)
{
	complex r;
	
	r.re = c1.re*c2.re - c1.im*c2.im;
	r.im = c1.re*c2.im + c1.im*c2.re;

	return r;
}

// Adder
complex complexAddition(complex c1, complex c2)
{
	complex r;
	
	r.re = c1.re + c2.re;
	r.im = c1.im + c2.im;
	
	return r;
}

// -c
complex ReverseComplex(complex c)
{
	c.re = -c.re;
	c.im = -c.im;
	
	return c;
}

// Reverse Bit
	// input: 
		// a decimal num, 
		// N-based reverse method
	// output: a decimal num
int bitReversal(int value, int N) {

	int ret = 0;
	int i = 0;

	while (i < N) {
		ret <<= 1;
		ret |= (value>>i) & 1;
		i++;
	}

	return ret;
}


// Other func


/********************************************************************/
// Append [seq_1] & [seq_2] to [seq_1,seq_2]
complex* appendSequences(complex seq_1[], complex seq_2[], int N) {
	complex* total_seq = new complex[N*2];
	for (int i = 0; i < N; i++) {
		total_seq[i] = seq_1[i];
	}
	for (int i = N; i < 2*N; i++) {
		total_seq[i] = seq_2[i-N];
	}
	return total_seq;
}


/********************************************************************/
// Reorder the input_seq to an order
complex* reorderSequence(complex input_seq[], int N) {

	cout << "Reorder the sequence ... \t";

	complex* reordered_seq = new complex[N];
	for (int i = 0; i < N; ++i)
	{
		int k = bitReversal(i, log2(N));
		reordered_seq[k] = input_seq[i];
	}

	return reordered_seq;
}


/********************************************************************/



/********************************************************************/
// Calc WN[], with N = input_N
complex* Calc_WN(int N) {

	cout << "Calculating WN[] of N = " << N << " ... \t";
	complex* WN = new complex[N];

	complex WN_unit; WN_unit.re = cos(2*PI/N); WN_unit.im = -sin(2*PI/N);
	WN[0].re=1; WN[0].im=0;

	for (int i = 1; i < N; ++i)
	{
		WN[i] = complexProduct(WN[i-1], WN_unit);
	}

	return WN;
}






complex* DIT_FFT(complex input_seq[], int N, complex WN[], int recur_time_count) {

	// cout << "\tDIF_FFT executed!\n"; // for validation
	// output seq
	complex* return_seq = new complex[N];

	if ( N != 2 ) {

		int k = pow(2,recur_time_count);

		// Split input_seq into 2
		complex* first_half_input_seq = new complex[N/2];
		complex* second_half_input_seq = new complex[N/2];
		for (int i = 0; i < N/2; ++i) {
			first_half_input_seq[i] = input_seq[i];
		}
		for (int i = 0; i < N/2; ++i) {
			second_half_input_seq[i] = input_seq[i+N/2];
		}


		// DFT recursive call
		complex* DFTed_first_half_seq = new complex[N/2];
		DFTed_first_half_seq = DIT_FFT(first_half_input_seq, N/2, WN, recur_time_count+1);
		complex* DFTed_second_half_seq = new complex[N/2];
		DFTed_second_half_seq = DIT_FFT(second_half_input_seq, N/2, WN, recur_time_count+1);


		// Calc
		complex* output_first_half_seq = new complex[N/2];
		complex* output_second_half_seq = new complex[N/2];
		for (int i = 0; i < N/2; ++i) {
			output_first_half_seq[i] = complexAddition(DFTed_first_half_seq[i], complexProduct(DFTed_second_half_seq[i], WN[i*k]) ) ;
		}
		for (int i = 0; i < N/2; ++i) {
			output_second_half_seq[i] = complexAddition(DFTed_first_half_seq[i], complexProduct( ReverseComplex(DFTed_second_half_seq[i]), WN[i*k] ) );
		}


		// Append [output_first_half_seq] & [output_second_half_seq]
		return_seq = appendSequences(output_first_half_seq, output_second_half_seq, N/2);
		return return_seq;

	} else if ( N == 2 ) { // Smallest Butterfly Unit

		// cout << "\tDIT_FFT N==2 triggered!\n"; // for validation
		return_seq[0] = complexAddition(input_seq[0], complexProduct(input_seq[1], WN[0]) );
		return_seq[1] = complexAddition(input_seq[0], complexProduct( ReverseComplex(input_seq[1]), WN[0] ) );
		return return_seq;
	
	}

	// return [return_seq] # unordered
	return return_seq;
}

/********************************************************************/
// DFT
	// input_seq[]: 
	// N: size of input_seq
complex* DFT(complex input_seq[], int N) {

	// Calc WN
	complex* WN = new complex[N];
	WN = Calc_WN(N);

	complex* DFTed_seq = new complex[N];
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			int k_mod = (i*j) % N;
			DFTed_seq[i] = complexAddition( DFTed_seq[i], complexProduct(input_seq[j], WN[k_mod]) );
		}
	}

	return DFTed_seq;
}

/********************************************************************/
// DIT-FFT
	// input_seq[]: 
	// N: size of input_seq
		// Must be a 2^k integer
complex* DIT_FFT_reordered(complex input_seq[], int N) {
	
	// Initialize
	complex* reordered_seq = new complex[N];
	
	// Calc WN
	complex* WN = new complex[N];
	WN = Calc_WN(N);

	// Reorder
	reordered_seq = reorderSequence(input_seq, N);
	// Calc DIF-FFT
	reordered_seq = DIT_FFT(reordered_seq, N, WN, 0);

	return reordered_seq;
}

/********************************************************************/


complex* DIF_FFT(complex input_seq[], int N, complex WN[], int recur_time_count) {

	// cout << "\tDIF_FFT executed!\n"; // for validation
	// output seq
	complex* return_seq = new complex[N];

	if ( N != 2 ) {

		complex* first_half_seq = new complex[N/2];
		complex* second_half_seq = new complex[N/2];

		int k = pow(2,recur_time_count);

		// Calc
		for (int i = 0; i < N/2; ++i) {
			first_half_seq[i] = complexAddition(input_seq[i], input_seq[i+N/2]) ;
		}
		for (int i = 0; i < N/2; ++i) {
			second_half_seq[i] = complexProduct( complexAddition(input_seq[i], ReverseComplex(input_seq[i+N/2])), WN[i*k] ) ;
		}

		// DFT
		complex* DFTed_first_half_seq = new complex[N/2];
		DFTed_first_half_seq = DIF_FFT(first_half_seq, N/2, WN, recur_time_count+1);
		complex* DFTed_second_half_seq = new complex[N/2];
		DFTed_second_half_seq = DIF_FFT(second_half_seq, N/2, WN, recur_time_count+1);

		// Append [DFTed_first_half_seq] & [DFTed_second_half_seq]
		return_seq = appendSequences(DFTed_first_half_seq, DFTed_second_half_seq, N/2);
		return return_seq;

	} else if ( N == 2 ) { // Smallest Butterfly Unit

		// cout << "\tDIF_FFT N==2 triggered!\n"; // for validation
		return_seq[0] = complexAddition(input_seq[0], input_seq[1]);
		return_seq[1] = complexProduct( complexAddition(input_seq[0], ReverseComplex(input_seq[1])), WN[0] );
		return return_seq;
	
	}

	// return [return_seq] # unordered
	return return_seq;
}

/********************************************************************/
// DIF-FFT
	// input_seq[]: 
	// N: size of input_seq
		// Must be a 2^k integer
complex* DIF_FFT_reordered(complex input_seq[], int N) {
	
	// Initialize
	complex* reordered_seq = new complex[N];
	
	// Calc WN
	complex* WN = new complex[N];
	WN = Calc_WN(N);

	// Calc DIF-FFT
	reordered_seq = DIF_FFT(input_seq, N, WN, 0);
	// Reorder
	reordered_seq = reorderSequence(reordered_seq, N);

	return reordered_seq;
}

/********************************************************************/

void validate_result(complex input_seq[], int N, int dft_dit_dif) {


	// DFT
	if (dft_dit_dif == 1 || dft_dit_dif == 4)
	{
		cout << "Calculating DFT..." << endl;

		// DFT
		complex* DFTed_seq = new complex[N];
		DFTed_seq = DFT(input_seq, N);

		// Validate
		cout << "\n\tValidating..." << endl;
		for (int i = 0; i < N; ++i) {
			cout << "\tX[" << i << "] = " << DFTed_seq[i].re << " + j*" << DFTed_seq[i].im << endl;
		}

		delete[] DFTed_seq;
	}

	// DIT-FFT
	if (dft_dit_dif == 2 || dft_dit_dif == 4)
	{
		cout << "Calculating DIT-FFT..." << endl;

		 // DIT_FFT
		complex* DIT_FFTed_seq = new complex[N];
		DIT_FFTed_seq = DIT_FFT_reordered(input_seq, N);

		// Validate
		cout << "\n\tValidating..." << endl;
		for (int i = 0; i < N; ++i) {
			cout << "\tX[" << i << "] = " << DIT_FFTed_seq[i].re << " + j*" << DIT_FFTed_seq[i].im << endl;
		}
		
		delete[] DIT_FFTed_seq;
	}

	// DIF-FFT
	if (dft_dit_dif == 3 || dft_dit_dif == 4)
	{
		cout << "Calculating DIF-FFT..." << endl;

		 // DIT_FFT
		complex* DIF_FFTed_seq = new complex[N];
		DIF_FFTed_seq = DIF_FFT_reordered(input_seq, N);

		// Validate
		cout << "\n\tValidating..." << endl;
		for (int i = 0; i < N; ++i) {
			cout << "\tX[" << i << "] = " << DIF_FFTed_seq[i].re << " + j*" << DIF_FFTed_seq[i].im << endl;
		}

		delete[] DIF_FFTed_seq;
	}
}


