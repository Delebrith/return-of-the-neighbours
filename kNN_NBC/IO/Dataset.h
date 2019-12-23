#pragma once

#include <vector>
#include <set>
#include <string>


template<class T> class Dataset
{
public:
	Dataset(Dataset&& d) noexcept
		: ids(std::move(d.ids)), features(std::move(d.features)), _hasIds(d._hasIds) {}
	explicit Dataset(std::vector<std::vector<T>>&& features)
		: features(features), _hasIds(false) {}
	Dataset(std::vector<std::string>&& ids, std::vector<std::vector<T>>&& features)
		: ids(ids), features(features), _hasIds(true) {}

	std::vector<std::vector<T>>& getFeatures();
	std::vector<std::string>& getIds();
	bool hasIds();

	static Dataset readCsv(
		std::istream& stream,
		bool headers = true,
		int idCol = -1,
		const std::set<int>& ignoreCols = {},
		char delim = ',',
		char enclosing = '"');

	void writeCsv(
		std::ostream& stream,
		char delim = ',',
		char enclosing = '"');

private:
	Dataset() {}
	Dataset(Dataset&) {}
	std::vector<std::string> ids;
	std::vector<std::vector<T>> features;
	bool _hasIds;

	static bool readCsvRow(std::istream& stream, std::string& buffer, char enclosing);
	static std::vector<std::string> parseCsvRow(std::string& line, char delim, char enclosing);
	static std::string unescapeCsv(std::string field, char enclosing);
	static std::string escapeCsv(std::string field, char delim, char enclosing);
	static T parse(const std::string&);
};
