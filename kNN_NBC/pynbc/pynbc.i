%module pynbc

//To allow usage of STL vector
%include <std_vector.i>
//To allow usage of dllimport
%include <windows.i>

//Instatiate vector<int> type
namespace std {
	%template(intvector) vector<int>;
}

//Include c++ file
%{
#include "nbc.h"
%}

//Generate wrapper for included symbols
%include "nbc.h"
