#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "cmdline.h"
#include "ComplexSignal.h"
#include "complex.h"
#include "DynamicArray.h"


enum method_t
{
		DFT_METHOD = 0,
		IDFT_METHOD = 1,
		FFT_METHOD = 2,
		IFFT_METHOD = 3
};

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_help(string const &);
static void opt_method(string const &);


static option_t options[] = {
    {1, "i", "input",  "-", opt_input,  OPT_DEFAULT},
    {1, "o", "output", "-", opt_output, OPT_DEFAULT},
    {1, "m", "method", "-", opt_method, OPT_DEFAULT},
    {0, "h", "help",  NULL, opt_help,   OPT_DEFAULT},
    {0, }
};

static method_t metodo = DFT_METHOD ;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

int
main(int argc, char * const argv[])
{
    ComplexSignal csignal;
    ComplexSignal * tcsignal;
    size_t inputLength = 0;
    double expValue = 0;
    cmdline cmdl(options);
    cmdl.parse(argc, argv);
    
    while(true)
    {		
		if( !(*iss >> csignal) )
		{			
			if( !( iss->eof() ) )
			{
				cerr << "Corrupt input" << endl;
				return EXIT_FAILURE;
			}
			break;		
		}
		
		inputLength = csignal.getLength(); // inputLength < 2^(expValue)
		expValue = log(inputLength) / log(2); // expValue = log_2(inputLength)
    
		if( expValue < pow(2, ceil(expValue) ) ) // Si expValue < 2^( ⌈expValue⌉ ) 
			csignal.increaseLength( pow( 2, ceil(expValue) ) );
			// Cambiar tamaño a 2^( ⌈expValue⌉ )
		
		if(metodo == DFT_METHOD)
			tcsignal = csignal.computeDFT();
		else if(metodo == IDFT_METHOD)	
			tcsignal = csignal.computeIDFT();	
		else if(metodo == FFT_METHOD)
			tcsignal = csignal.computeFFT();
		else if(metodo == IFFT_METHOD)
			tcsignal = csignal.computeIFFT();
		
		*oss << *tcsignal;
		delete tcsignal;
	}
	
   return EXIT_SUCCESS;
}

static void
opt_method(string const &arg)
{
    size_t flag = 1;
    if (arg == "-") {
        metodo = FFT_METHOD; ///metodo por default
    }else{
        if (arg == "dft"){
            metodo = DFT_METHOD;
            flag = 0;
        }
        if (arg == "idft"){
            metodo = IDFT_METHOD;
            flag = 0;
        }
        if (arg == "fft"){
            metodo = FFT_METHOD;
            flag = 0;
        }
        if (arg == "ifft"){
            metodo = IFFT_METHOD;
            flag = 0;
        }
        if (flag) {
            cerr << "Unknown method "
            << arg
            << "."
            << endl;
            exit(1);
        }
    }
}

static void
opt_input(string const &arg)
{

    if (arg == "-") 
    {
        iss = &cin;
    } 
    else 
    {
        ifs.open(arg.c_str(), ios::in);
        iss = &ifs;
    }
    
    if (!iss->good()) 
    {
        cerr << "cannot open "
        << arg
        << "."
        << endl;
        exit(1);
    }
}

static void
opt_output(string const &arg)
{
    if (arg == "-") 
    {
        oss = &cout;
    } 
    else 
    {
        ofs.open(arg.c_str(), ios::out);
        oss = &ofs;
    }    

    if (!oss->good()) 
    {
        cerr << "cannot open "
        << arg
        << "."
        << endl;
        exit(1);
    }
}

static void
opt_help(string const &arg)
{
    cout << "tp0 [-m idft / dft / ifft / fft] [-i file] [-o file]"
    << endl;
    exit(0);
}
