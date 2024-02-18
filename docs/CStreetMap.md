#StreetMap class documentation

'''
        using TNodeID = uint64_t;
        using TWayID = uint64_t;
        using TLocation = std::pair<double, double>;
'''
creates 3 types that will be used in implementation

'''
        static const TNodeID InvalidNodeID = std::numeric_limits<TNodeID>::max();
        static const TWayID InvalidWayID = std::numeric_limits<TWayID>::max();
'''
creates special types to return in Index Out of Range scenarios

'''
        struct SNode{
            virtual ~SNode(){};
            virtual TNodeID ID() const noexcept = 0;
            virtual TLocation Location() const noexcept = 0;
            virtual std::size_t AttributeCount() const noexcept = 0;
            virtual std::string GetAttributeKey(std::size_t index) const noexcept = 0;
            virtual bool HasAttribute(const std::string &key) const noexcept = 0;
            virtual std::string GetAttribute(const std::string &key) const noexcept = 0;
        };
'''
The definions of the SNode class:
    ~Snode(): the deconstructor
    ID(): returns the ID of the node, which is specified as an attribute in the OSM data
    Location(): returns the Lat/Lon double, which is specifiec as an attribute in the OSM data
    AttributeCount(): returns the number of attributes a given node has
    GetAttributeKey(std::size_t index): returns the attribute key at a given index, if it exists
    HasAttribute(const std::string &key): returns true/false depending on the existence of the given attribute
    GetAttribute(const std::string &key): returns the attribute value of the given attribute key, if it exists

'''
        struct SWay{
            virtual ~SWay(){};
            virtual TWayID ID() const noexcept = 0;
            virtual std::size_t NodeCount() const noexcept = 0;
            virtual TNodeID GetNodeID(std::size_t index) const noexcept = 0;
            virtual std::size_t AttributeCount() const noexcept = 0;
            virtual std::string GetAttributeKey(std::size_t index) const noexcept = 0;
            virtual bool HasAttribute(const std::string &key) const noexcept = 0;
            virtual std::string GetAttribute(const std::string &key) const noexcept = 0;
        };
'''
The definitions of the SWay class:
    ~SWay(): the deconstructor
    ID(): returns the ID of the way, specified as an attribute in the OSM data
    NodeCount(): returns the number of nodes in the Way
    GetNodeID(std::size_t index): returns the NodeID at a specific index, if it exists
    AttributeCount(): returns the number of attributes in the given Way
    GetAttributeKey(std::size_t index): returns the attribute key associated with the given index, if it exists
    HasAttribute(const std::string &key): returns true/false depending on the existence of the given attribute key
    GetAttribute(const std::string &key): returns the attribute value of the given attribute key, if it exists

'''
        virtual ~CStreetMap(){};

        virtual std::size_t NodeCount() const noexcept = 0;
        virtual std::size_t WayCount() const noexcept = 0;
        virtual std::shared_ptr<SNode> NodeByIndex(std::size_t index) const noexcept = 0;
        virtual std::shared_ptr<SNode> NodeByID(TNodeID id) const noexcept = 0;
        virtual std::shared_ptr<SWay> WayByIndex(std::size_t index) const noexcept = 0;
        virtual std::shared_ptr<SWay> WayByID(TWayID id) const noexcept = 0;
'''
The definitions of the CStreetMap class:
    ~CStreetMap(): the deconstructor
    NodeCount(): returns the number of nodes in the CStreetMap
    WayCount(): returns the number of ways in the CStreetMap
    NodeByIndex(std::size_t index): returns the node at the given index, if it exists
    NodeByID(TNodeID id): returns a pointer to the SNode object with the given TNodeID
    WayByIndex(std::size_t index): returns the Way at the given index, if it exists
    WayByID(TWayID id): reutrns a pointer to the SWay object with the given TNodeID