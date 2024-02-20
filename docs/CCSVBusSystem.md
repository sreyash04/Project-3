# CCSVBusSystem Class Documentation
## Class Description

The `CCSVBusSystem` class implements a bus system using data read from CSV files. It manages bus stops and routes, allowing users to query information about stops and routes within the system.

## Constructor and Destructor
### CCSVBusSystem Constructor

**Purpose** : Constructs a CCSVBusSystem instance, initializing it with data sources for stops and routes.

**Parameters** :

std::shared_ptr<CDSVReader> stopsrc: A shared pointer to a CDSVReader object for reading stop data from a CSV file.
std::shared_ptr<CDSVReader> routesrc: A shared pointer to a CDSVReader object for reading route data from a CSV file.
CCSVBusSystem Destructor
Purpose: Destroys the CCSVBusSystem instance, performing necessary cleanup of resources.

Document Methods
StopCount Method

**Purpose**: Retrieves the total number of stops in the bus system.

**Parameters**: None

**Return Type**:
 std::size_t

Returns the number of stops in the system.
RouteCount Method
**Purpose**: Retrieves the total number of routes in the bus system.

**Parameters**::
 None

#**Return Type**:
 std::size_t

Returns the number of routes in the system.
StopByIndex Method

**Purpose**:
 Retrieves a shared pointer to a stop object by its index in the system.

**Parameters**:

std::size_t index: The index of the stop.

**Return Type**:
 std::shared_ptr<CBusSystem::SStop>

Returns a shared pointer to the stop object if the index is valid, otherwise returns nullptr.
StopByID Method

**Purpose**: 
Retrieves a shared pointer to a stop object by its ID.

**Parameters**:
TStopID id: The ID of the stop.

**Return Type**:
 std::shared_ptr<CBusSystem::SStop>

Returns a shared pointer to the stop object if the ID exists, otherwise returns nullptr.
RouteByIndex Method

**Purpose**:
 Retrieves a shared pointer to a route object by its index in the system.

**Parameters**:
std::size_t index: The index of the route.
Return Type: std::shared_ptr<CBusSystem::SRoute>

Returns a shared pointer to the route object if the index is valid, otherwise returns nullptr.
RouteByName Method

**Purpose**: Retrieves a shared pointer to a route object by its name.

**Parameters**:
const std::string& name: The name of the route.

**Return Type**:
 std::shared_ptr<CBusSystem::SRoute>

Returns a shared pointer to the route object if the name exists, otherwise returns nullptr.

## Example Usage

``` cpp #include "CSVBusSystem.h"
#include "DSVReader.h"
#include <iostream>

int main() {
    // Assume 'stopReader' and 'routeReader' are instances of CDSVReader initialized with appropriate data sources.

    // Create a CCSVBusSystem instance with data sources for stops and routes.
    CCSVBusSystem busSystem(stopReader, routeReader);

    // Retrieve and print the total number of stops and routes in the system.
    std::cout << "Total number of stops: " << busSystem.StopCount() << std::endl;
    std::cout << "Total number of routes: " << busSystem.RouteCount() << std::endl;

    // Example: Retrieve and print information about a stop by its index.
    std::size_t stopIndex = 0;
    auto stop = busSystem.StopByIndex(stopIndex);
    if (stop) {
        std::cout << "Stop ID: " << stop->ID() << std::endl;
        std::cout << "Stop Node ID: " << stop->NodeID() << std::endl;
    } else {
        std::cout << "Invalid stop index." << std::endl;
    }

    // Example: Retrieve and print information about a route by its name.
    std::string routeName = "Route1";
    auto route = busSystem.RouteByName(routeName);
    if (route) {
        std::cout << "Route Name: " << route->Name() << std::endl;
        std::cout << "Number of Stops: " << route->StopCount() << std::endl;
    } else {
        std::cout << "Route not found." << std::endl;
    }

    return 0;
}
```
