#include "StreetMap.h"
#include <unordered_map>

class COpenStreetMap : public CStreetMap{
    private:
        struct SImplementation;
        std::unique_ptr<SImplementation> DImplementation;

    public:
        COpenStreetMap(std::shared_ptr<CXMLReader> src);
        ~COpenStreetMap();

        std::size_t NodeCount() const noexcept override;
        std::size_t WayCount() const noexcept override;
        std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const noexcept override;
        std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const noexcept override;
        std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const noexcept override;
        std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept override;
};

struct COpenStreetMap::SImplementation{

    struct SNode{
            TNodeID DID;
            TLocation DLocation;
            std::unordered_map<std::string, std::string> DAttributes;
            std::vector<std::string> DAttributeKeys;

            SNode(TNodeID id, TLocation location){
                DID = id;
                DLocation = location;
                
            }

            ~SNode(){

            }

            TNodeID ID() const noexcept override{
                return DID;

            }
            TLocation Location() const noexcept override{
                return DLocation;

            }
            std::size_t AttributeCount() const noexcept override{
                return DAttributeKeys.size();

            }
            std::string GetAttributeKey(std::size_t index) const noexcept override{
                if(index < DAttributeKeys.size()){
                    return DAttributeKeys[index];
                }
                return std::string();


            }
            bool HasAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                return DAttributes.end() != Search;

            }

        
            std::string GetAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                if(DAttributes.end() != Search){
                    return Search->second;
                }
                return std::string();

            }

            void SetAttribute(const std::string &key, const std::string &value){
                DAttributeKeys.push_back(key);
                DAttributes[key] = value;
            }
        };

        struct SWay{
            

            SWay(TWayID id, TLocation location, std::vector<CStreetMap::SNode> nodevector){
                
            }

            ~SWay(){

            }
            TWayID ID() const noexcept override{
            

            }
            std::size_t NodeCount() const noexcept override{
                

            }
            TNodeID GetNodeID(std::size_t index) const noexcept override{

            }
            std::size_t AttributeCount() const noexcept override{

            }
            std::string GetAttributeKey(std::size_t index) const noexcept override{

            }
            bool HasAttribute(const std::string &key) const noexcept override{

            }
            std::string GetAttribute(const std::string &key) const noexcept override{

            }
        };


    std::unordered_map<TNodeID, std::shared_ptr<CStreetMap::SNode>> DNodeIDToNode;
    std::vector<std::shared_ptr<CStreetMap::SNode>> DNodesByIndex;

    SImplementation(std::shared_ptr<CXMLReader> src){
        SXMLEntity TempEntity;

        while(src->ReadEntity(TempEntity, true)){
            if ((TempEntity.DNameData == "osm") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                break;
            }

            else if((TempEntity.DNameData = "node") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                TNodeID NewNodeID = std::stoull(TempEntity.AttributeValue("id"));
                double Lat = std::stod(TempEntity.AttributeValue("lat"));
                double Lon = std::stod(TempEntity.AttributeValue("lon"));
                TLocation NewNodeLocation = std::make_pair(Lat, Lon);
                auto NewNode = std::make_shared<SNode>(NewNodeID, NewNodeLocation);
                DNodesByIndex.push_back(NewNode);
                DNodeIDToNode[NewNodeID] = NewNode;
                while(src->ReadEntity(TempEntity, true)){
                    if ((TempEntity.DNameData == "node") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                        break;
                    }
                    else if ((TempEntity.DNameData == "tag") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                        NewNode->SetAttribute(TempEntity.AttributeValue("k"), TempEntity.AttributeValue("v"));
                    }
                }

            }
        }


    }

    std::size_t NodeCount() const{
        return DNodesByIndex.size();

    }


    std::size_t WayCount() const{


    }

    std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const{
        if(index < DNodesByIndex.size()){
            return DNodesByIndex[index];
        }
        return nullptr;

    }

    std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const{
        auto Search = DNodeIDToNode.find(id);
        if(DNodeIDToNode.end() != Search){
            return Search->second;
        }
        return nullptr;

    }

    std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const{


    }

    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const{

    }

}





COpenStreetMap(std::shared_ptr<CXMLReader> src){
    DImplementation = std::make_unique<SImplementation>(src);

}


~COpenStreetMap(){

}


std::size_t NodeCount() const{
    return DImplementation->NodeCount();
}


std::size_t WayCount() const{
    return DImplementation->WayCount();
}

std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const{
    return DImplemetation->NodeByIndex(std::size_t index);
}

std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const{
    return DImplementation->NodeByID(TNodeID id)
}

std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const{
    return DImplementation->WayByIndex(std::size_t index);
}

std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const{
    return DImplementation->WayByID(TWayID id);

}





