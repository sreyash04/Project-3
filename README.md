# Project-3

# Project-3
# ECS34Project2
Sreyash Ravinuthala (920484337)
# Project Status: Complete

# Known Issues: None

# Generative AI Use:

### Prompt 1
How do i  Returns the stop id specified by the index, returns InvalidStopID if inde is greater than or equal to StopCount()?

#### Response:
To implement a function that returns the stop ID specified by the index, returning InvalidStopID if the index is greater than or equal to StopCount(), you can follow these steps:

Determine the logic to retrieve the stop ID based on the index.
Check if the index is within the valid range using StopCount().
Return the appropriate stop ID or InvalidStopID based on the index validity.
Here's how you can implement this in your code:

cpp
Copy code
TStopID GetStopID(std::size_t index) const noexcept override {
    const TStopID InvalidStopID = -1;
    // Check if the index is within the valid range
    if (index < StopCount()) {
        // Return the stop ID at the specified index
        return ids[index];
    } else {
        // Return the InvalidStopID if index is out of range
        return InvalidStopID;
    }
}
This function ensures that it only tries to access the ids vector if the index is within the valid range (i.e., less than StopCount()). Otherwise, it returns the InvalidStopID.



#### How to Fix It:

The problem we faced was related to the const TStopID InvalidStopID = -1; and we hadnt intalized in our program so we realized this error and fixed this .

Our new code:

TStopID GetStopID(std::size_t index) const noexcept override{
        const TStopID InvalidStopID = -1;
            if (ids.size()>index) {
                return ids[index];
            } else {
                return InvalidStopID;  
            }
        }
 
