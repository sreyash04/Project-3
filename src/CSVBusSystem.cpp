#include <unordered_map>
#include "StringDataSource.h"
#include <vector>
#include <iostream>
#include "CCSVBusSystem.h"
#include "DSVReader.h"     // For reading CSV files
#include "BusSystem.h"     // For types related to the bus system
#include "StreetMap.h"     // For types related to the street map


struct CCSVBusSystem::SImplementation{
    struct SStop : public CBusSystem::SStop {
                    //DAttributes- Attribute:Value, DAttributeKeys- Index:attribute, manipulated by member funcs
            //DID, DLocation passed on obj creation
            TStopID DID;
            CStreetMap::TNodeID NodeID() DNodeID;
            std::unordered_map<std::string, std::string> DAttributes;
           

            //constructor
            SStop(TStopID id, CStreetMap::TNodeID NodeID): DID(id),DNodeID(nodeID){
                DID = id;
                DNodeID = nodeID;
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
       SRoute(string name){
                DID = id;
                DLocation = location;
                
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

        };
    

    std::shared_ptr<CDSVReader> StopSrc;
    std::shared_ptr<CDSVReader> RouteSrc;
    std::unordered_map<TStopID, std::shared_ptr<SStop>> Stops;
    std::unordered_map<std::string, std::shared_ptr<SRoute>> Routes;

    SImplementation(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc) {

    }
    std::size_t CCSVBusSystem::StopCount() const{


    }
    std::size_t CCSVBusSystem::RouteCount() const{

    }
    std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByIndex(std::size_t index) const{

    }
    std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByID(TStopID id) const{

    }
    std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const{

    }
    std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByName(const std::string& name) const{

    }


    
};
//Constructor
CCSVBusSystem(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr<CDSVReader > routesrc){
    DImplementation = std::make_unique<SImplementation>(src);
}
//Deconstructor
CCSVBusSystem::~CCSVBusSystem(){
}

std::size_t CCSVBusSystem::StopCount() const noexcept {
    }

std::size_t CCSVBusSystem::RouteCount() const noexcept {
}

std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByIndex(std::size_t index) const noexcept {
    
}

std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept {
    
}

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept {
    
}

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByName(const std::string& name) const noexcept {

   
}





