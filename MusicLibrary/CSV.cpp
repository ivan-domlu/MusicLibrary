#include "CSV.h"


CSVReader::CSVReader(string pPath)
{
	aPath = pPath;
} // Constructor

TCSVTbl CSVReader::read(void)
{
	ifstream in(aPath);
	TCSVTbl table;
	string row;	

	if (in.is_open()) {
		while (!in.eof()) {
			getline(in, row);
			if (in.bad() || in.fail()) {
				break;
			}
			/*auto*/ TCSVRow fields = readCSVRow(row);
			table.push_back(fields);
		}
		in.close();
	}

	return table;
} // read

TCSVRow CSVReader::readCSVRow(const string& row)
{
	CSVState state = CSVState::UnquotedField;
	TCSVRow fields{ "" };
	size_t i = 0; // index of the current field

	for (char c : row) {
		switch (state) {
		case CSVState::UnquotedField:
			switch (c) {
			case ',': // end of field
				fields.push_back(""); i++;
				break;
			case '"': state = CSVState::QuotedField;
				break;
			default:  fields[i].push_back(c);
				break;
			}
			break;
		case CSVState::QuotedField:
			switch (c) {
			case '"': state = CSVState::QuotedQuote;
				break;
			default:  fields[i].push_back(c);
				break;
			}
			break;
		case CSVState::QuotedQuote:
			switch (c) {
			case ',': // , after closing quote
				fields.push_back(""); i++;
				state = CSVState::UnquotedField;
				break;
			case '"': // "" -> "
				fields[i].push_back('"');
				state = CSVState::QuotedField;
				break;
			default:  // end of quote
				state = CSVState::UnquotedField;
				break;
			}
			break;
		}
	}
	return fields;
} // readCSVRow


//-----


CSVWriter::CSVWriter(string pPath)
{
	aFile = new ofstream(pPath);
} // Constructor

CSVWriter::~CSVWriter(void)
{
	if (aFile && (aFile->is_open())) {
		aFile->close();
		delete aFile;
	}
} // Destructor

void CSVWriter::write(string pVal)
{
	if (aFile && (aFile->is_open())) {
		(*aFile) << "\"" << pVal << "\",";
	}
} // write

void CSVWriter::writeeol(void)
{
	if (aFile && (aFile->is_open())) {
		(*aFile) << endl;
	}
} // write

void CSVWriter::writeln(TCSVRow& pRow)
{
	if (aFile && (aFile->is_open())) {
		for (size_t lCol = 0; lCol < pRow.size(); lCol++) {
			write(pRow[lCol]);
		}
		writeeol();
	}
} // writeln
