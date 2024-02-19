#include <unordered_map>
#include "StringDataSource.h"
#include <vector>
#include <iostream>
#include "CSVBusSystem.h"
#include "DSVReader.h"     // For reading CSV files
#include "BusSystem.h"     // For types related to the bus system
#include "StreetMap.h"     // For types related to the street map


struct CCSVBusSystem::SImplementation{
    struct SStop : public CBusSystem::SStop{
                    //DAttributes- Attribute:Value, DAttributeKeys- Index:attribute, manipulated by member funcs
            //DID, DLocation passed on obj creation
            TStopID DID;
            uint64_t DNodeID;
            std::unordered_map<std::string, std::string> DAttributes;
           

            //constructor
            SStop(TStopID id, CStreetMap::TNodeID NodeID){
                DID = id;
                DNodeID = NodeID;
            }
            
            //deconstructor
            ~SStop(){

            }

            //returns the Node's id (DID)
            TStopID ID() const noexcept override{
                return DID;

            }

        // Returns the node id of the bus stop
            CStreetMap::TNodeID NodeID() const noexcept override{
                return DNodeID;
            }

        // Assuming TNodeID is defined in a way similar to COpenStreetMap or elsewhere
       
    };
    struct SRoute : public CBusSystem::SRoute {
        // Additional functions to manage route stops if needed
        std::string name;
        std::vector<TStopID> ids;
            //constructor
       //notsure need to fill these both in 
        SRoute(std::string dname){
            name = dname;
            }
            
            //deconstructor
        ~SRoute(){

        }

        // Bus System Route member functions
        // Returns the name of the route
        std::string Name() const noexcept override{
            return name;
        }
        // Returns the number of stops on the route
        std::size_t StopCount() const noexcept override{
            return ids.size();
        }
        // Returns the stop id specified by the index, returns InvalidStopID if index
       // is greater than or equal to StopCount()
        TStopID GetStopID(std::size_t index) const noexcept override{
        const TStopID InvalidStopID = -1;
            if (ids.size()>index) {
                return ids[index];
            } else {
                return InvalidStopID;  
            }
        }

        //adds a stopID to the ids vector, formally adding a stop to the route
        void AddStopID(TStopID id){
            ids.push_back(id);
        }

    };
    

    std::shared_ptr<CDSVReader> StopSrc;
    std::shared_ptr<CDSVReader> RouteSrc;
    std::unordered_map<TStopID, std::shared_ptr<SStop>> Stop;       //STOPBYID
    std::unordered_map<std::string, std::shared_ptr<SRoute>> Routes;    //ROUTEBYNAME
    std::vector<std::shared_ptr<CBusSystem::SStop>> SStopByIndex;
    std::vector<std::shared_ptr<CBusSystem::SRoute>> SRouteByIndex;

    SImplementation(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc){
        std::vector<std::string> temp;

        //read first row cuz its data col headers, not data
        stopsrc->ReadRow(temp);

        //keep reading in rows, for each row create a new stop object, add it to SStopByIndex and Stop do it can be indexed and searhced
        while(stopsrc->ReadRow(temp)){
            TStopID NewStopID = stoull(temp[0]);
            uint64_t NewNodeID = stoull(temp[1]);
            auto NewStop = std::make_shared<SStop>(NewStopID, NewNodeID);
            SStopByIndex.push_back(NewStop);
            Stop[NewStopID] = NewStop;

        }

        //Read first row cuz it is column headers, and not data
        routesrc->ReadRow(temp);

        //keep reading in columns, grab route name and stop id from row
        while(routesrc->ReadRow(temp)){
            std::string NewRouteName = temp[0];
            TStopID ThisStopID = stoull(temp[1]);

            //if the route doesnt already exist in the bus system, create a new route, and add it to be indexed and searched
            if(Routes.count(NewRouteName) == 0){
                auto NewRoute = std::make_shared<SRoute>(NewRouteName);
                SRouteByIndex.push_back(NewRoute);
                Routes[NewRouteName] = NewRoute;
            }

            //find the current route in the Routes map, and call the route's AddStopID func to add the stop to the route
            auto thisRoute = Routes.find(NewRouteName)->second;
            thisRoute->AddStopID(ThisStopID);
        }

    }

    //return number of stops
    std::size_t StopCount() const{
        return SStopByIndex.size();
    }
    //return number of routes
    std::size_t RouteCount() const{
        return SRouteByIndex.size();
    }
    //if index in range, return shared ptr to SStop obj, otherwise nullptr
    std::shared_ptr<CBusSystem::SStop> StopByIndex(std::size_t index) const{
        if(index < SStopByIndex.size()){
            return SStopByIndex[index];
        }
        return nullptr;
    }
    //if id exists, return shared ptr to SStop obj, otherwise nullptr
    std::shared_ptr<CBusSystem::SStop> StopByID(TStopID id) const{
        auto Search = Stop.find(id);
        if(Stop.end() != Search){
            return Search->second;
        }
        return nullptr;
    }
    //if index in range, return shared ptr to SRoute obj, otherwise nullptr
    std::shared_ptr<CBusSystem::SRoute> RouteByIndex(std::size_t index) const{
        if(index < SRouteByIndex.size()){
            return SRouteByIndex[index];
        }
        return nullptr;
    }
    //if name exists, return shared ptr to SRoute obj, otherwise nullptr
    std::shared_ptr<CBusSystem::SRoute> RouteByName(const std::string& name) const{
        auto Search = Routes.find(name);
        if(Routes.end() != Search){
            return Search->second;
        }
        return nullptr;
    }


    
};



//Constructor
CCSVBusSystem::CCSVBusSystem(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr<CDSVReader > routesrc){
    DImplementation = std::make_unique<SImplementation>(stopsrc, routesrc);
}
//Deconstructor
CCSVBusSystem::~CCSVBusSystem(){
}

std::size_t CCSVBusSystem::StopCount() const noexcept {
    return DImplementation->StopCount();
}

std::size_t CCSVBusSystem::RouteCount() const noexcept {
    return DImplementation->RouteCount();
}

std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByIndex(std::size_t index) const noexcept {
    return DImplementation->StopByIndex(index);
}

std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept {
    return DImplementation->StopByID(id);
}

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept {
    return DImplementation->RouteByIndex(index);
}

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByName(const std::string& name) const noexcept {
    return DImplementation->RouteByName(name);
}





