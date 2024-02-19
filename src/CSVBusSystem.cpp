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
        TStopID DID;
        // Assuming TNodeID is defined in a way similar to COpenStreetMap or elsewhere
       
    };
    struct SRoute : public CBusSystem::SRoute {
        // Additional functions to manage route stops if needed
    };

    std::shared_ptr<CDSVReader> StopSrc;
    std::shared_ptr<CDSVReader> RouteSrc;
    std::unordered_map<TStopID, std::shared_ptr<SStop>> Stops;
    std::unordered_map<std::string, std::shared_ptr<SRoute>> Routes;

    SImplementation(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc) {

    }
    
};
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





