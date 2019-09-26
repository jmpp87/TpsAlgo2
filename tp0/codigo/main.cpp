#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "cmdline.h"
#include "ComplexSignal.hpp"
#include "complex.hpp"
#include "DynamicArray.hpp"



#define tipo_dato_ double 

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
    {0, },
};

static size_t metodo =0 ;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;



int
main(int argc, char * const argv[])
{
    ComplexSignal csignal;
    ComplexSignal *tcsignal;
    cmdline cmdl(options);
    cmdl.parse(argc, argv);
       
    *iss >> csignal;
    
    if(metodo == 0)
		tcsignal = csignal.computeDFT();
	else	
		tcsignal = csignal.computeIDFT();
		
	*oss << *tcsignal;
	
	delete tcsignal;    
    
}



static void
opt_method(string const &arg)
{
    size_t flag = 1;
    if (arg == "-") {
        metodo = 0; ///mediana por default
    }else{
        if (arg == "dft"){
            metodo = 0;
            flag = 0;
        }
        if (arg == "idft"){
            metodo = 1;
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

    if (arg == "-") {
        iss = &cin;
    } else {
        ifs.open(arg.c_str(), ios::in);
        iss = &ifs;
    }
    
    if (!iss->good()) {
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

    if (arg == "-") {
        oss = &cout;
    } else {
        ofs.open(arg.c_str(), ios::out);
        oss = &ofs;
    }
    

    if (!oss->good()) {
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
    cout << "tp0 [-m idft / dft] [-i file] [-o file]"
    << endl;
    exit(0);
}


