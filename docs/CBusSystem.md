## CBusSystem Class Documentation

### Class Description

The `CBusSystem` class provides an abstract interface for managing a bus system. It defines abstract methods for accessing information about stops and routes within the system.

### Class Members

#### SStop Struct

- **Description**: Represents a bus stop within the system.

#### Public Methods

- **ID**:
  - **Description**: Pure virtual method that returns the ID of the stop.
  - **Return Type**: `TStopID`

- **NodeID**:
  - **Description**: Pure virtual method that returns the node ID of the stop on the street map.
  - **Return Type**: `CStreetMap::TNodeID`

#### SRoute Struct

- **Description**: Represents a route within the system.

#### Public Methods

- **Name**:
  - **Description**: Pure virtual method that returns the name of the route.
  - **Return Type**: `std::string`

- **StopCount**:
  - **Description**: Pure virtual method that returns the number of stops on the route.
  - **Return Type**: `std::size_t`

- **GetStopID**:
  - **Description**: Pure virtual method that returns the ID of the stop at the specified index on the route.
  - **Parameters**:
    - `std::size_t index` - The index of the stop on the route.
  - **Return Type**: `TStopID`

### Public Methods

- **StopCount**:
  - **Description**: Pure virtual method that returns the total number of stops in the system.
  - **Return Type**: `std::size_t`

- **RouteCount**:
  - **Description**: Pure virtual method that returns the total number of routes in the system.
  - **Return Type**: `std::size_t`

- **StopByIndex**:
  - **Description**: Pure virtual method that returns a shared pointer to a stop object by its index in the system.
  - **Parameters**:
    - `std::size_t index` - The index of the stop.
  - **Return Type**: `std::shared_ptr<SStop>`

- **StopByID**:
  - **Description**: Pure virtual method that returns a shared pointer to a stop object by its ID.
  - **Parameters**:
    - `TStopID id` - The ID of the stop.
  - **Return Type**: `std::shared_ptr<SStop>`

- **RouteByIndex**:
  - **Description**: Pure virtual method that returns a shared pointer to a route object by its index in the system.
  - **Parameters**:
    - `std::size_t index` - The index of the route.
  - **Return Type**: `std::shared_ptr<SRoute>`

- **RouteByName**:
  - **Description**: Pure virtual method that returns a shared pointer to a route object by its name.
  - **Parameters**:
    - `const std::string &name` - The name of the route.
  - **Return Type**: `std::shared_ptr<SRoute>`
