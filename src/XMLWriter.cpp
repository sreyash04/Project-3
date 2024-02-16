#include "XMLWriter.h"
#include "StringDataSink.h"
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include "StringUtils.h"

struct CXMLWriter::SImplementation {
    std::shared_ptr<CDataSink> Sink;
    SImplementation(std::shared_ptr<CDataSink> sink) : Sink(sink) {

    }
    void HandleSpecial(std::ostream& os, const std::string& value) { //handles special escape characters
        for (char ch : value) {
            switch (ch) {//Utilized C++ switch method see code documentation 5
                case '&':  os << "&amp;"; break;
                case '<':  os << "&lt;"; break;
                case '>':  os << "&gt;"; break;
                case '\"': os << "&quot;"; break;
                case '\'': os << "&apos;"; break;
                default:   os << ch; break;
            }
        }
    }

    void StartElement(const std::string& name, const std::vector<SXMLEntity::TAttribute>& attributes) {
        std::stringstream ss;
        ss << "<";
        HandleSpecial(ss, name);
        for (const auto& attr : attributes) {
            ss << " ";
            HandleSpecial(ss, attr.first);
            ss << "=\"";
            HandleSpecial(ss, attr.second);
            ss << "\"";
        }
        ss << ">";
        std::string temp = ss.str();
        Sink->Write(std::vector<char>(temp.begin(), temp.end()));
    }

    void EndElement(const std::string& name) {
        std::stringstream ss;
        ss << "</";
        HandleSpecial(ss, name);
        ss << ">";
        std::string temp = ss.str();
        Sink->Write(std::vector<char>(temp.begin(), temp.end()));
    }

    void CompleteElement(const std::string& name, const std::vector<SXMLEntity::TAttribute>& attributes) {
        std::stringstream ss;
        ss << "<";
        HandleSpecial(ss, name);
        for (const auto& attr : attributes) {
            ss << " ";
            HandleSpecial(ss, attr.first);
            ss << "=\"";
            HandleSpecial(ss, attr.second);
            ss << "\"";
        }
        ss << "/>";
        std::string temp = ss.str();
        Sink->Write(std::vector<char>(temp.begin(), temp.end()));
    }

    void CharData(const std::string& data) {
        std::stringstream ss;
        HandleSpecial(ss, data);
        std::string temp = ss.str();
        Sink->Write(std::vector<char>(temp.begin(), temp.end()));
    }
};

CXMLWriter::CXMLWriter(std::shared_ptr<CDataSink> sink)
: DImplementation(std::make_unique<SImplementation>(sink)) {

}

CXMLWriter::~CXMLWriter() {

}

bool CXMLWriter::Flush() {
    return true; //didnt use a buffer
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity) { //Utilized C++ switch method see code documentation 5
    switch (entity.DType) {
        case SXMLEntity::EType::StartElement:
            DImplementation->StartElement(entity.DNameData, entity.DAttributes);
            break;
        case SXMLEntity::EType::EndElement:
            DImplementation->EndElement(entity.DNameData);
            break;
        case SXMLEntity::EType::CompleteElement:
            DImplementation->CompleteElement(entity.DNameData, entity.DAttributes);
            break;
        case SXMLEntity::EType::CharData:
            DImplementation->CharData(entity.DNameData);
            break;
        default:
            return false; 
    }
    return true;
}
