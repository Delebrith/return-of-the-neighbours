#include <nbc.h>
#include <cassert>
// check csv header inclusion
#include <csv.h>
// check tclap parser inclusion
#include <tclap/CmdLine.h>



int main()
{
	assert(fun(1) == 1);
	assert(fun_negate({ 1, 2, 3 }).size() == 3);

	return 0;
}	