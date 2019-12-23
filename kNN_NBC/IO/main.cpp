#include <nbc.h>
#include <cassert>
// check tclap parser inclusion
#include <tclap/CmdLine.h>

#include "Dataset.h"

#include <iostream>


int main(int argc, char** argv)
{
	TCLAP::CmdLine args("CLI for implementation of NBC algorithm with kNN and k+NN");
	TCLAP::ValueArg<char> delimArg("d", "csv-delim", "A delimiter for CSV file", false, ',', "char");
	TCLAP::SwitchArg delimTabArg("t", "csv-delim-tab", "Use tab as a delimiter for CSV file. Has priority over csv-delim");
	TCLAP::ValueArg<char> enclosingArg("e", "enclosing", "An enclosing character for CSV file", false, '"', "char");
	TCLAP::SwitchArg headersArg("r", "headers", "Indicates that csv file contains headers row that is to be ignored");
	TCLAP::ValueArg<int> idColArg("i", "id", "Indicates that csv file contains id column", false, -1, "int");
	TCLAP::MultiArg<int> ignoreColsArg("n", "ignore", "Specifies columns to be ignored by algorithm", false, "int");

	args.add(delimArg);
	args.add(delimTabArg);
	args.add(enclosingArg);
	args.add(headersArg);
	args.add(idColArg);
	args.add(ignoreColsArg);

	args.parse(argc, argv);

	char delim = delimTabArg.getValue() ? '\t' : delimArg.getValue();
	bool headers = headersArg.getValue();
	int idCol = idColArg.getValue();
	std::set<int> ignoreCols(ignoreColsArg.getValue().cbegin(), ignoreColsArg.getValue().cend());
	char enclosing = enclosingArg.getValue();

	Dataset<double> data(Dataset<double>::readCsv(std::cin, headers, idCol, ignoreCols, delim, enclosing));
	data.writeCsv(std::cout, delim, enclosing);
}

