#include "XMLReader.h"
#include "StringDataSource.h"
#include <expat.h>
#include <queue>

struct CXMLReader::SImplementation{
    std:: shared_ptr < CDataSource > DDataSource;
    XML_Parser DXMLParser;
    std::queue<SXMLEntity> DEntityQueue;

    void StartElementHandler(const std::string &name, const std::vector<std::string> &attrs){
        SXMLEntity TempEntity;
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::StartElement;
        for(size_t Index = 0; Index < attrs.size(); Index +=2){
            TempEntity.SetAttribute(attrs[Index],attrs[Index+1]);
        }
        DEntityQueue.push(TempEntity);
    }

    void EndElementHandler(const std::string &name) {
        SXMLEntity entity;
        entity.DType = SXMLEntity::EType::EndElement;
        entity.DNameData = name;
        DEntityQueue.push(entity);
    }

    void CharacterDataHandler(const std::string &data) {
        if (!DEntityQueue.empty() && DEntityQueue.back().DType == SXMLEntity::EType::CharData) {
            DEntityQueue.back().DNameData += data; //merge consecutive char data
        } else {
            SXMLEntity entity;
            entity.DType = SXMLEntity::EType::CharData;
            entity.DNameData = data;
            DEntityQueue.push(entity);
        }
    }

    static void StartElementHandlerCallback(void *context, const XML_Char *name, const XML_Char **atts){
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        std::vector<std::string> Attributes;
        auto AttrPtr =atts;
        while(*AttrPtr){
            Attributes.push_back(*AttrPtr);
            AttrPtr++;
        }
        ReaderObject->StartElementHandler(name,Attributes);
    };

    static void EndElementHandlerCallback(void *context, const XML_Char *name){
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        ReaderObject->EndElementHandler(name);
    };

    static void CharacterDataHandlerCallback(void *context, const XML_Char *s, int len){
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        ReaderObject->CharacterDataHandler(std::string(s,len));
    }

    SImplementation(std::shared_ptr<CDataSource> src){
        DDataSource = src;
        DXMLParser = XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser, StartElementHandlerCallback);
        XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
        XML_SetCharacterDataHandler(DXMLParser, CharacterDataHandlerCallback);
        XML_SetUserData(DXMLParser, this);
    };

    bool End() const{
        return DDataSource->End() && DEntityQueue.empty();
    };

    bool ReadEntity(SXMLEntity &entity, bool skipcdata) {
    if (DEntityQueue.empty() && !DDataSource->End()) {
        std::vector<char> buffer(1024);
        // Corrected to pass the buffer vector itself
        bool success = DDataSource->Read(buffer, buffer.size());
        if (success) {
            XML_Parse(DXMLParser, buffer.data(), buffer.size(), 0);
        } else {
            XML_Parse(DXMLParser, nullptr, 0, XML_TRUE); //end if no data read
        }
    }
    while (!DEntityQueue.empty()) {
        const auto& frontEntity = DEntityQueue.front();
        if (skipcdata && frontEntity.DType == SXMLEntity::EType::CharData) {
            DEntityQueue.pop();
            continue;
        }
        entity = frontEntity;
        DEntityQueue.pop();
        return true;
    }
    return false;
}
};

CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src) {
    DImplementation = std::make_unique<SImplementation > (src);
}

CXMLReader::~CXMLReader() {//destructor

}

bool CXMLReader::End() const {
    return DImplementation->End();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata){
    return DImplementation->ReadEntity(entity,skipcdata);
}