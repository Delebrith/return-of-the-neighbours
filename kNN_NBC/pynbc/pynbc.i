%module pynbc

//To allow usage of STL vector
%include <std_vector.i>
//To allow usage of dllimport
%include <windows.i>

//Instatiate vector<int> type and vector<vector<double>> type
namespace std {
	%template(intvector) vector<int>;
	%template(doublevector) vector<double>;
	%template(doublevectorvector) vector<vector<double>>;
}

//Include c++ file
%{
#include "nbc.h"
%}

//Generate wrapper for included symbols
%include "nbc.h"
