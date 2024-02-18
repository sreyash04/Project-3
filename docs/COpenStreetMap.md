#COpenStreetMap class documentation


#SNode
'''
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
'''
The SNode class inherits from the CStreetMap::SNode interface. It has 4 data members. DID and DLocation specify the ID and Location of the node,
which are both specified as attributes in the OSM data. DAttributes is a map that maps attribute keys to attribute values. DAttributeKeys is a vector that stores attribute keys, so that they can be accessed by index. The constructor sets the node's DID and DLocation to the values that are passed.

'''
            TNodeID ID() const noexcept override{
                return DID;

            }
'''
This function takes no parameters, and returns the value of the DID data member, representing the node's ID

'''
            TLocation Location() const noexcept override{
                return DLocation;

            }
'''
This function takes no parameters, and returns the value of the DLocation data member, representing the node's location

'''
            std::size_t AttributeCount() const noexcept override{
                return DAttributeKeys.size();

            }
'''
This function takes no parameters, and returns the number of attributes the node has. The nodes attribute keys are stored by index in the DAttributeKeys vector, so the vectors size is the number of attributes.

'''
            std::string GetAttributeKey(std::size_t index) const noexcept override{
                if(index < DAttributeKeys.size()){
                    return DAttributeKeys[index];
                }
                return std::string();

            }
'''
This function takes a parameter that is the index of the attribute key desired. If the index is in range of the DAttributeKeys vector, we return the attribute key at that index. If it is out of range, we return an empty string

'''
            bool HasAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                return DAttributes.end() != Search;

            }
'''
This function takes in an attribute key string as a parameter, and returns a boolean true/false depending on the attributes existence. We use .find() on the DAttributes map to search for the key. If it exists, Search will be an iterator at the first occurance of the desired key. Otherwise, Search will be an iterator at the end of the vector. In this case, Search will be equal to .end(), so return the boolean != of the two values.

'''
            std::string GetAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                if(DAttributes.end() != Search){
                    return Search->second;
                }
                return std::string();

            }
'''
This function takes an attribute key string as a parameter, and returns the attribute's value. We search for the attribute the same way as we do in HasAttribute. If the attribute exists, we return it's paired value. If it doesn't exist, we return an empty string.

'''
            void SetAttribute(const std::string &key, const std::string &value){
                DAttributeKeys.push_back(key);
                DAttributes[key] = value;
            }
'''
This function takes in attribute key and attribute value strings as parameters, and adds to the DAttributeKeys and DAttributes, so that this attribute formally exists in the node.


#SWay
'''
        struct SWay : public CStreetMap::SWay{
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
'''
The SWay class inherits from the CStreetMap::SWay interface. It has 4 data members. DID is the ID of the way. WayNodes is a vector holding the ID's of the nodes in the way. DAttributes is an unordered map mapping attribute keys to attribute values. DAttributeKeys is a vector indexing attribute keys
The constructor takes in the way id, and initializes the DID.

'''
            TWayID ID() const noexcept override{
                return DID;
        
            }
'''
This function takes no parameters, and returns the DID of the way, which is the ways ID specified in the OSM data

'''
            std::size_t NodeCount() const noexcept override{
                return WayNodes.size();
                
            }
'''
This function takes no parameters, and returns the number of nodes in the way. The WayNodes vector holds every node, so it's size is the number of nodes

'''
            TNodeID GetNodeID(std::size_t index) const noexcept override{
                if (WayNodes.size() > index){
                    return WayNodes[index];
                }
                return InvalidNodeID;

            }
'''
This function takes in an index, and returns the ID of the node of the given index. If the index is within the range of WayNodes.size(), we return the value at the index, since WayNodes stores the Nodes IDs. If it is out of range, we return the InvalidNodeID type

'''
            std::size_t AttributeCount() const noexcept override{
                return DAttributes.size();
                
            }
'''
This function takes no parameters, and returns the number of attributes the way has, which is given by DAttributes.size()

'''
            std::string GetAttributeKey(std::size_t index) const noexcept override{
                if (DAttributeKeys.size() > index){
                    return DAttributeKeys[index];
                }
                return std::string();

            }
'''
This function takes in an index, and returns the attribute key at the given index. If the index is in range od DAttributeKeys, which stores attributes by index, then we return the value at the index. Otherwise, we return an empty string

'''
            bool HasAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                return DAttributes.end() != Search;

            }
'''
This function takes in an attribute key, and returns a boolean true/false depending on it's existence. We use .find() to find the attribute key in the DAttributes map, and if it exists, Seach is an iterator starting from the first occurance. If it doesn't exist, it returns an iterator at the end of the vector, which is equal to DAttributes.End(). Then returning the boolean != of Search and DAttributes.End() will return the attributes existence boolean

'''
            std::string GetAttribute(const std::string &key) const noexcept override{
                auto Search = DAttributes.find(key);
                if(DAttributes.end() != Search){
                    return Search->second;
                }
                return std::string();

            }
'''
This function takes in a attribute key, and returns the associated attribute value. It searched for the attribute key the same way that HasAttribute does, and if it exists, it returns the attribute key's paired value in the DAttributes map. If it doesn't exist, we return an empty string.

'''
            void AddNode(TNodeID id){
                WayNodes.push_back(id);
            }
'''
This function takes a TNodeID, and pushes it to the WayNodes vector to formally add the node to the way

'''
            void SetAttribute(const std::string &key, const std::string &value){
                DAttributeKeys.push_back(key);
                DAttributes[key] = value;

            }
        };
'''
This function takes in attribute key and attribute value strings. It pushes the attribute key to the DAttributeKeys vector and adds the pair to the DAttributes map, formally adding the attribute to the way.

'''
    std::unordered_map<TNodeID, std::shared_ptr<CStreetMap::SNode>> DNodeIDToNode;
    std::vector<std::shared_ptr<CStreetMap::SNode>> DNodesByIndex;
    std::unordered_map<TWayID, std::shared_ptr<CStreetMap::SWay>> DWayIDToWay;
    std::vector<std::shared_ptr<CStreetMap::SWay>> DWaysByIndex;

    //create a new sxmlentity, read into it, and process the data based on the DNameData and DType values
    SImplementation(std::shared_ptr<CXMLReader> src){
        SXMLEntity TempEntity;

        while(src->ReadEntity(TempEntity, true)){
''' 
The COpenStreetMap has 4 data members. The DNodeIDToNode stores TNodeID:SNode pairs. The DNodesByIndex stores SNodes by index. The DWayIDToWay map stores TWayID:SWay pairs. The DWaysByIndex vector stores SWays by index.
The implementation of this class parses the OSM data, which is handled by a while loop, that executes as long as there are still lines to be read in from the data file

'''
if ((TempEntity.DNameData == "osm") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                break;
            }
'''
If we hit an </osm> tag, we have hit the end of the data, so we terminate the while loop

'''
            else if((TempEntity.DNameData == "node") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                TNodeID NewNodeID = std::stoull(TempEntity.AttributeValue("id"));
                double Lat = std::stod(TempEntity.AttributeValue("lat"));
                double Lon = std::stod(TempEntity.AttributeValue("lon"));
                TLocation NewNodeLocation = std::make_pair(Lat, Lon);
                auto NewNode = std::make_shared<SNode>(NewNodeID, NewNodeLocation);
                DNodesByIndex.push_back(NewNode);
                DNodeIDToNode[NewNodeID] = NewNode;
'''
If we hit a <node> tag, we have found a new node, and we create a new node object and parse the attributes as needed.

'''
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
'''
We create another while loop to handle attributes in the node tag. If we hit an ending node tag, there are no more attributes, so we break this while loop to continue reading. If we hit a starting tag tag, we have found an attribute, so we call the node's SetAttribute function to deal with it

'''
            else if((TempEntity.DNameData == "way") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                TWayID NewWayID = std::stoull(TempEntity.AttributeValue("id"));
                auto NewWay = std::make_shared<SWay>(NewWayID);
                DWaysByIndex.push_back(NewWay);
                DWayIDToWay[NewWayID] = NewWay;
'''
If we hit a <way> tag, we have found a way. We create a new way obj and add the new way to the COpenStreetMap data members as necessary.

'''
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
'''
We create another while loop to deal with attributes and way member nodes. If we hit a </way> tag, we end the while loop. If we hit a <nd> tag, we add the node to the way by calling the way's AddNode function. If we hit an attribute tag, we call the ways SetAttribute function

'''
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
'''
These functions return the number of nodes, number of ways, node by index/ID, way by index/ID, and are implemented identically as the SNode and SWay versions