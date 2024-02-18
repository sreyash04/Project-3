#include "StreetMap.h"
#include <unordered_map>
#include "StringDataSource.h"
#include "XMLReader.h"
#include "OpenStreetMap.h"
#include <vector>
#include <iostream>

struct COpenStreetMap::SImplementation{

    struct SNode : public CStreetMap::SNode{
            //DAttributes- Attribute:Value, DAttributeKeys- Index:attribute, manipulated by member funcs
            //DID, DLocation passed on obj creation
            TNodeID DID;
            TLocation DLocation;
            std::unordered_map<std::string, std::string> DAttributes;
            std::vector<std::string> DAttributeKeys;

            //constructor
            SNode(TNodeID id, TLocation location){
                DID = id;
                DLocation = location;
                
            }
            
            //deconstructor
            ~SNode(){

            }

            //returns the Node's id (DID)
            TNodeID ID() const noexcept override{
                return DID;

            }

            //returns the Node's location (DLocation)
            TLocation Location() const noexcept override{
                return DLocation;

            }
            //returns the size of the vector that attribute keys are stored in
            std::size_t AttributeCount() const noexcept override{
                return DAttributeKeys.size();

            }
            //given an index within range, returns the attribute from that index. otherwise, returns ""
            std::string GetAttributeKey(std::size_t index) const noexcept override{
                if(index < DAttributeKeys.size()){
                    return DAttributeKeys[index];
                }
                return std::string();

            }
            //returns T/F is attribute exists for this node. .find() returns an iterator to equiv obj, or returns last if attribute doesnt exist
            //return val of last is equivalent to .end() func, so if search and .end() are equal, the attribute was not found
            bool HasAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                return DAttributes.end() != Search;

            }

            //searches for attribute existence same way as HasAttribute. If exists, returns Search->second, which will be attribute's value, since
            //DAttributes is a map, which stores pairs. If doesnt exist, return ""
            std::string GetAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                if(DAttributes.end() != Search){
                    return Search->second;
                }
                return std::string();

            }
            //inputs new attributes into the node, pushes key into vector to be indexed and creates new pair in map
            void SetAttribute(const std::string &key, const std::string &value){
                DAttributeKeys.push_back(key);
                DAttributes[key] = value;
            }
        };

        struct SWay : public CStreetMap::SWay{
            //DID specified upon obj creation
            //WayNodes, DAttributes, and DAttributeKeys are created and modified by the obj member functions
            TWayID DID;
            std::vector<TNodeID> WayNodes;
            std::unordered_map<std::string, std::string> DAttributes;
            std::vector<std::string> DAttributeKeys;

            //constructor
            SWay(TWayID id){
                DID = id;
            }

            //deconstructor
            ~SWay(){

            }

            //returns ID of the way, specified when way obj was created
            TWayID ID() const noexcept override{
                return DID;
        
            }
            //returns number of nodes in the way, tracked in WayNodes vector
            std::size_t NodeCount() const noexcept override{
                return WayNodes.size();
                
            }
            //returns ID of requested node in the way. If index is within WayNodes size, we return the value at the index, as Node ID's are stored in WayNodes
            //otherwise, return InvalidNodeID
            TNodeID GetNodeID(std::size_t index) const noexcept override{
                if (WayNodes.size() > index){
                    return WayNodes[index];
                }
                return InvalidNodeID;

            }
            //returns the number of attributes the way has, tracked in DAttributes
            std::size_t AttributeCount() const noexcept override{
                return DAttributes.size();
                
            }
            //returns the atribute key at a given index. Checks if index within DAttributeKeys, and returns value at index
            //otherwise, returns empty string
            std::string GetAttributeKey(std::size_t index) const noexcept override{
                if (DAttributeKeys.size() > index){
                    return DAttributeKeys[index];
                }
                return std::string();

            }
            //return T/F if way has given attribute. .find() returns iterator if attribute exists, and last if not. last is equal to .end(),
            //so if the attribute doesnt exist, Search == DAttributes.end() == False. Otherwise, they are not equal and the attribute exists
            bool HasAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                return DAttributes.end() != Search;

            }
            //returns attribute value given attribute key. searches for key and checks existence same way as HasAttribute, and returns Search->second if exists
            //since DAttribute is a map, mapping attribute key to attribute value, so the second value of a pair is the attribute value
            std::string GetAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                if(DAttributes.end() != Search){
                    return Search->second;
                }
                return std::string();

            }
            //adds a node to the way by pushing it to the WayNodes vector so that it is indexed and tracked
            void AddNode(TNodeID id){
                WayNodes.push_back(id);
            }
            //adds a new attribute to the way, by pushing it's key to the DAttributeKeys vec so it can be indexed, and pushing key/value pair to map
            void SetAttribute(const std::string &key, const std::string &value){
                DAttributeKeys.push_back(key);
                DAttributes[key] = value;

            }
        };


    //DNodeIDToNode stores TNodeID:SNode pair
    //DNodesByIndex is a vector storing SNodes so that they are indexed
    //DWayIDToWay stores TWayID:SWay pair
    //DWaysByIndex is a vector storing SWays so that they are indexed
    std::unordered_map<TNodeID, std::shared_ptr<CStreetMap::SNode>> DNodeIDToNode;
    std::vector<std::shared_ptr<CStreetMap::SNode>> DNodesByIndex;
    std::unordered_map<TWayID, std::shared_ptr<CStreetMap::SWay>> DWayIDToWay;
    std::vector<std::shared_ptr<CStreetMap::SWay>> DWaysByIndex;

    //create a new sxmlentity, read into it, and process the data based on the DNameData and DType values
    SImplementation(std::shared_ptr<CXMLReader> src){
        SXMLEntity TempEntity;

        while(src->ReadEntity(TempEntity, true)){

            //if we have reached a </osm> tag, we are at end of input, so break while loop
            if ((TempEntity.DNameData == "osm") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                break;
            }

            //if we read a node start tag, create a new node. The TNodeID, Lat, Lon, are stored as attributes in the sxmlentity, so we create a new node
            //with those attributes. push the new node to DNodesByIndex and add its TNodeID:Node pair to DNodeIDToNode map so it can be searched and indexed
            else if((TempEntity.DNameData == "node") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                TNodeID NewNodeID = std::stoull(TempEntity.AttributeValue("id"));
                double Lat = std::stod(TempEntity.AttributeValue("lat"));
                double Lon = std::stod(TempEntity.AttributeValue("lon"));
                TLocation NewNodeLocation = std::make_pair(Lat, Lon);
                auto NewNode = std::make_shared<SNode>(NewNodeID, NewNodeLocation);
                DNodesByIndex.push_back(NewNode);
                DNodeIDToNode[NewNodeID] = NewNode;

                //continue reading to read in any potential attributes
                while(src->ReadEntity(TempEntity, true)){
                    //if we hit a ending node tag, break this while loop bc there are no more attributes
                    if ((TempEntity.DNameData == "node") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                        break;
                    }
                    //if we hit a starting "tag" tag, it means we have hit an attribute, so we call the node's SetAttribute func to handle the data.
                    else if ((TempEntity.DNameData == "tag") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                        NewNode->SetAttribute(TempEntity.AttributeValue("k"), TempEntity.AttributeValue("v"));
                    }
                }

            }
            //if we have hit a starting way tag, we create a new way obj given the way id attribute, and push it to DWaysByIndex and add the ID:Way pair to
            //DWayIDToWay map so it can be indexed and searched
            else if((TempEntity.DNameData == "way") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                TWayID NewWayID = std::stoull(TempEntity.AttributeValue("id"));
                auto NewWay = std::make_shared<SWay>(NewWayID);
                DWaysByIndex.push_back(NewWay);
                DWayIDToWay[NewWayID] = NewWay;

                //continute reading to process any potential attributes
                while (src->ReadEntity(TempEntity, true)){
                    //if we hit an ending way tag, break the while loop
                    if ((TempEntity.DNameData == "way") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                        break;
                    }
                    //if we hit a nd tag, we are dealing with a member node of this way. grab the node id attribute and call the way's AddNode func to handle it
                    else if ((TempEntity.DNameData == "nd") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                        TNodeID DID = stoull(TempEntity.AttributeValue("ref"));
                        NewWay->AddNode(DID);
                    }
                    //if we hit a startng "tag" tag, we are dealing with an attribute. call the way's SetAttribute func to handle the attribute
                    else if ((TempEntity.DNameData == "tag") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                        NewWay->SetAttribute(TempEntity.AttributeValue("k"), TempEntity.AttributeValue("v"));

                    }
                }
                
            }
        }


    }

    //returns the number of nodes in the map
    std::size_t NodeCount() const{
        return DNodesByIndex.size();

    }

    //returns the number of ways in the map
    std::size_t WayCount() const{
        return DWaysByIndex.size();



    }

    //returns the node at a given index if in range
    std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const{
        if(index < DNodesByIndex.size()){
            return DNodesByIndex[index];
        }
        return nullptr;

    }

    //returns the node of a given ID if node w ID exists
    std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const{
        auto Search = DNodeIDToNode.find(id);
        if(DNodeIDToNode.end() != Search){
            return Search->second;
        }
        return nullptr;

    }

    //returns the way of an index if index is in range
    std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const{
        if (index < DWaysByIndex.size()){
            return DWaysByIndex[index];
        }
        return nullptr;


    }

    //returns the way of an ID if a way w ID exists 
    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const{
        auto Search = DWayIDToWay.find(id);
        if(DWayIDToWay.end() != Search){
            return Search->second;
        }
        return nullptr;

    }

};




//constructor
COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src){
    DImplementation = std::make_unique<SImplementation>(src);

}

//deconstructor
COpenStreetMap::~COpenStreetMap(){

}


//the following functions use the PIMPL concept, and calls the function implemented in the class obj. 

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





