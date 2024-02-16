#include "DSVReader.h"
#include <memory>
#include "StringDataSource.h"
#include <vector>
#include <string>
#include <sstream>

struct CDSVReader::SImplementation {
    std::shared_ptr<CDataSource> Src;
    char Delimiter;
    std::string chunk;
    bool EndOfData = false;
    SImplementation(std::shared_ptr<CDataSource> src, char delimiter) : Src(src), Delimiter(delimiter) {

    }

    bool FillChunk() {
        chunk.clear();
        char ch;
        while (Src->Get(ch)) { //no more data when get is false
            chunk.push_back(ch);
            if (ch == '\n') {
                break;
            }
        }
        EndOfData = chunk.empty() && !Src->Get(ch); //true when no data but more available
        return !EndOfData;
    }
};
CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delimiter) //constructor
    : DImplementation(std::make_unique<SImplementation>(src, delimiter)) {
}

CDSVReader::~CDSVReader() { //destructor

}

bool CDSVReader::End() const {
    return DImplementation->EndOfData;
}

bool CDSVReader::ReadRow(std::vector<std::string>& row) {
    row.clear();
    if (DImplementation->EndOfData){
         return false;
    }
    std::string field;
    bool quoted = false;
    bool fieldCompleted = false;

    while (!DImplementation->EndOfData && !fieldCompleted) {
        if (DImplementation->chunk.empty() && !DImplementation->FillChunk()) {
            DImplementation->EndOfData = true; //no more data to read
            break;
        }

        for (size_t i = 0; i < DImplementation->chunk.size(); ++i) {
            char ch = DImplementation->chunk[i];
            bool isLastChar = (i == DImplementation->chunk.size() - 1);
            if (ch == '"' && quoted && !isLastChar && DImplementation->chunk[i + 1] == '"') {
                field += ch; 
                ++i; 
            } else if (ch == '"') {
                quoted = !quoted; 
            } else if (!quoted && ch == DImplementation->Delimiter) {
                row.push_back(field);
                field.clear();
            } else if (!quoted && ch == '\n') {
                row.push_back(field);
                field.clear();
                fieldCompleted = true;
                DImplementation->chunk.erase(DImplementation->chunk.begin(), DImplementation->chunk.begin() + i + 1);
                break; 
            } else {
                field += ch;
            }

            if (isLastChar && !fieldCompleted) {
                DImplementation->chunk.clear();
            }
        }
    }
    if (!fieldCompleted) {
        row.push_back(field);
    }
    if (DImplementation->chunk.empty()) {
        DImplementation->FillChunk();
    }
    return !row.empty();
}