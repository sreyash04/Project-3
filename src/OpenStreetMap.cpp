#include "StreetMap.h"
#include <unordered_map>
#include "StringDataSource.h"
#include "XMLReader.h"
#include "OpenStreetMap.h"
#include <vector>

struct COpenStreetMap::SImplementation{

    struct SNode : public CStreetMap::SNode{
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

        struct SWay : public CStreetMap::SWay{
            TWayID DID;
            std::vector<TNodeID> WayNodes;
            std::unordered_map<std::string, std::string> DAttributes;
            std::vector<std::string> DAttributeKeys;

            SWay(TWayID id){
                DID = id;
            }

            ~SWay(){

            }
            TWayID ID() const noexcept override{
                return DID;
            

            }
            std::size_t NodeCount() const noexcept override{
                return WayNodes.size();
                

            }
            TNodeID GetNodeID(std::size_t index) const noexcept override{
                if (WayNodes.size() > index){
                    return WayNodes[index];
                }
                return InvalidNodeID;

            }
            std::size_t AttributeCount() const noexcept override{
                return DAttributes.size();
                
            }

            std::string GetAttributeKey(std::size_t index) const noexcept override{
                if (DAttributeKeys.size() > index){
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

            void AddNode(TNodeID id){
                WayNodes.push_back(id);
            }

            void SetAttribute(const std::string &key, const std::string &value){
                DAttributeKeys.push_back(key);
                DAttributes[key] = value;

            }
        };


    std::unordered_map<TNodeID, std::shared_ptr<CStreetMap::SNode>> DNodeIDToNode;
    std::vector<std::shared_ptr<CStreetMap::SNode>> DNodesByIndex;
    std::unordered_map<TNodeID, std::shared_ptr<CStreetMap::SWay>> DWayIDToWay;
    std::vector<std::shared_ptr<CStreetMap::SWay>> DWaysByIndex;

    SImplementation(std::shared_ptr<CXMLReader> src){
        SXMLEntity TempEntity;

        while(src->ReadEntity(TempEntity, true)){
            if ((TempEntity.DNameData == "osm") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                break;
            }

            else if((TempEntity.DNameData == "node") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
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
            else if((TempEntity.DNameData == "way") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                TWayID NewWayID = std::stoull(TempEntity.AttributeValue("id"));
                //std::vector<CStreetMap::SNode> WayNodes;
                //std::unordered_map<std::string, std::string> WayAttributes;
                //auto NewWay = std::make_shared<SWay>(NewWayID, WayNodes, WayAttributes);
                auto NewWay = std::make_shared<SWay>(NewWayID);
                DWaysByIndex.push_back(NewWay);
                DWayIDToWay[NewWayID] = NewWay;

                while (src->ReadEntity(TempEntity, true)){
                    if ((TempEntity.DNameData == "way") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                        break;
                    }
                    else if ((TempEntity.DNameData == "nd") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                        //WayNodes.push_back(TempEntity.AttributeValue("ref"));
                        TNodeID DID = stoi(TempEntity.AttributeValue("ref"));
                        NewWay->AddNode(DID);
                    }
                    else if ((TempEntity.DNameData == "tag") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                        NewWay->SetAttribute(TempEntity.AttributeValue("k"), TempEntity.AttributeValue("v"));

                    }
                }
                
            }
        }


    }

    std::size_t NodeCount() const{
        return DNodesByIndex.size();

    }


    std::size_t WayCount() const{
        return DWaysByIndex.size();



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
        if (index < DWaysByIndex.size()){
            return DWaysByIndex[index];
        }
        return nullptr;


    }

    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const{
        auto Search = DWayIDToWay.find(id);
        if(DWayIDToWay.end() != Search){
            return Search->second;
        }
        return nullptr;

    }

};





COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src){
    DImplementation = std::make_unique<SImplementation>(src);

}


COpenStreetMap::~COpenStreetMap(){

}


std::size_t COpenStreetMap::NodeCount() const noexcept{
    return DImplementation->NodeCount();
}


std::size_t COpenStreetMap::WayCount() const noexcept{
    return DImplementation->WayCount();
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept{
    return DImplementation->NodeByIndex(index);
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept{
    return DImplementation->NodeByID(id);
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept{
    return DImplementation->WayByIndex(index);
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const noexcept{
    return DImplementation->WayByID(id);

}





