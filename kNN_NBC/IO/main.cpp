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
	TCLAP::ValueArg<int> kArg("k", "k", "K value for algorithm", true, 3, "int");
	TCLAP::SwitchArg kPlusNNArg("+", "k-plus", "Use K+NN rather than KNN version of algorithm");
	TCLAP::ValueArg<int> strategyArg("s", "ref-point-strategy", 
		"Reference point creation strategy. Use -1 for none (disable TI), 0 for minimal values, 1 for maximal values", true, 0, "int");
	TCLAP::SwitchArg parallelArg("p", "parallel", "Use multithreaded implementation");

	args.add(delimArg);
	args.add(delimTabArg);
	args.add(enclosingArg);
	args.add(headersArg);
	args.add(idColArg);
	args.add(ignoreColsArg);
	args.add(kArg);
	args.add(kPlusNNArg);
	args.add(strategyArg);
	args.add(parallelArg);

	args.parse(argc, argv);


	char delim = delimTabArg.getValue() ? '\t' : delimArg.getValue();
	bool headers = headersArg.getValue();
	int idCol = idColArg.getValue();
	std::set<int> ignoreCols(ignoreColsArg.getValue().cbegin(), ignoreColsArg.getValue().cend());
	char enclosing = enclosingArg.getValue();

	Dataset<double> data(Dataset<double>::readCsv(std::cin, headers, idCol, ignoreCols, delim, enclosing));


	int k = kArg.getValue();
	int kPlus = kPlusNNArg.getValue();
	ReferenceStrategy strategy = static_cast<ReferenceStrategy>(strategyArg.getValue());

	std::vector<int> result = kPlus ?
		nbc_kpNN(k, strategy, data.getFeatures(), parallelArg.getValue()) :
		nbc_kNN(k, strategy, data.getFeatures(), parallelArg.getValue());


	std::vector<std::vector<int>> outputFeatures;
	outputFeatures.resize(result.size());

	for (int i = 0; i < result.size(); ++i)
		outputFeatures[i].push_back(result[i]);

	if (data.hasIds())
	{
		Dataset<int> output(std::move(std::vector<std::string>(data.getIds())), std::move(outputFeatures));
		output.writeCsv(std::cout, delim, enclosing);
	}
	else
	{
		Dataset<int> output(std::move(outputFeatures));
		output.writeCsv(std::cout, delim, enclosing);
	}
	return 0;
}	