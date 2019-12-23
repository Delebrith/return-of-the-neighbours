#include "Dataset.h"
#include <stdexcept>
#include <istream>

template<class T> std::vector<std::vector<T>>& Dataset<T>::getFeatures()
{
	return this->features;
}

template<class T> std::vector<std::string>& Dataset<T>::getIds()
{
	return this->ids;
}

template<class T> bool Dataset<T>::hasIds()
{
	return this->_hasIds;
}

template<class T> Dataset<T> Dataset<T>::readCsv(
	std::istream& stream,
	bool headers,
	int idCol,
	const std::set<int>& ignoreCols,
	char delim,
	char enclosing)
{
	int size = -1;
	int nrow = 0;
	std::string buffer;

	std::vector<std::string> ids;
	std::vector<std::vector<T>> features;

	while (readCsvRow(stream, buffer, enclosing)) 
	{
		std::vector<std::string> fields = parseCsvRow(buffer, delim, enclosing);
		std::vector<T> row;

		if (size == -1)
			size = fields.size();
		else if (size != fields.size())
			throw std::length_error("Different numbers of fields in csv file");
			
		if (nrow > 0 || !headers)
		{
			for (int i = 0; i < fields.size(); ++i)
			{
				if (i == idCol)
					ids.push_back(fields[i]);
				else if (ignoreCols.find(i) == ignoreCols.end())
					row.push_back(std::stod(fields[i]));
			}


			features.push_back(std::move(row));
		}

		++nrow;
	}

	if (idCol == -1)
		return Dataset(std::move(features));
	else
		return Dataset(std::move(ids), std::move(features));
}

template<class T> bool Dataset<T>::readCsvRow(std::istream& stream, std::string& buffer, char enclosing)
{
	buffer.erase();
	std::string line;
	int nEnclosing = 0;

	while ((buffer.size() == 0 || nEnclosing % 2 != 0) && std::getline(stream, line))
	{
		if (line.size() > 1 && line[line.size() - 1] == '\r')
			line.resize(line.size() - 1);

		if (buffer.size() > 0)
			buffer += '\n';
		buffer += line;
		
		for (char c : line)
			if (c == enclosing)
				++nEnclosing;
	}

	return buffer.size() != 0;
}

template<class T> std::vector<std::string> Dataset<T>::parseCsvRow(std::string& line, char delim, char enclosing)
{
	std::string::iterator fieldStart = line.begin(), fieldEnd = line.begin();
	int nEnclosing = 0;

	std::vector<std::string> fields;
	
	while (fieldEnd != line.end())
	{
		if (*fieldEnd == enclosing)
			++nEnclosing;
		else if (*fieldEnd == delim && nEnclosing % 2 == 0)
		{
			fields.push_back(unescapeCsv(std::string(fieldStart, fieldEnd), enclosing));
			fieldStart = fieldEnd + 1;
		}

		++fieldEnd;
	}

	fields.push_back(unescapeCsv(std::string(fieldStart, fieldEnd), enclosing));

	return fields;
}

template<class T> std::string Dataset<T>::unescapeCsv(std::string field, char enclosing)
{
	std::string out;

	std::string::const_iterator current = field.begin();
	std::string::const_iterator end = field.end();

	if (field[0] == enclosing && field[field.size() - 1] == enclosing && field.size() > 1)
	{
		++current;
		--end;
	}

	bool escaped = false;
	for (; current != end; ++current)
	{
		if (!escaped && *current == enclosing)
			escaped = true;
		else
		{
			out.push_back(*current);
			escaped = false;
		}
	}

	return out;
}

template<> double Dataset<double>::parse(const std::string& str)
{
	return std::stod(str);
}

template<> int Dataset<int>::parse(const std::string& str)
{
	return std::stoi(str);
}

template class Dataset<double>;
template class Dataset<int>;
