#include "DSVWriter.h"
#include <memory>
#include "StringDataSink.h"
#include <vector>
#include <string>
#include <sstream>

struct CDSVWriter::SImplementation {
    std::shared_ptr<CDataSink> Sink;
    char Delimiter;
    bool QuoteAll;

    SImplementation(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
        : Sink(sink), Delimiter(delimiter), QuoteAll(quoteall) {
    }

};

CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
    : DImplementation(std::make_unique<SImplementation>(sink, delimiter, quoteall)) {
}

CDSVWriter::~CDSVWriter() { //destructor

}

bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {
    std::stringstream string;
    for (size_t index = 0; index < row.size(); ++index) {
        if (index != 0) {
            string << DImplementation->Delimiter; //add delimiter between fields
        }
        std::string field = row[index];
        bool needsQuotes = DImplementation->QuoteAll || 
                           field.find(DImplementation->Delimiter) != std::string::npos || 
                           field.find('\"') != std::string::npos || 
                           field.find('\n') != std::string::npos;

        if (needsQuotes) {
            string << '\"';
            for (char c : field) {
                if (c == '\"') string << "\"\""; // double all double quotes
                else string << c;
            }
            string << '\"';
        } else {
            string << field;
        }
    }
    string << '\n'; // end with newline
    std::string outputRow = string.str();
    return DImplementation->Sink->Write(std::vector<char>(outputRow.begin(), outputRow.end())); //write to sink
}
