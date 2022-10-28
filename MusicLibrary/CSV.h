#pragma once

#include <istream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

enum class CSVState {
	UnquotedField,
	QuotedField,
	QuotedQuote
};

typedef vector<string> TCSVRow;
typedef vector<TCSVRow> TCSVTbl;

class CSVReader {
protected:
	string aPath;

public:
	CSVReader(string pPath);

	TCSVTbl read(void);

private:
	TCSVRow readCSVRow(const string& row);
}; // CSVReader


class CSVWriter {
protected:
	string aPath;
	ofstream* aFile;

public:
	CSVWriter(string pPath);
	~CSVWriter(void);

	void write(string pVal);
	void writeeol(void);
	void writeln(TCSVRow& pRow);
}; // CSVWriter

