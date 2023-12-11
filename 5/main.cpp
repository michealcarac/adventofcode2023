#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cmath>
#include<stdint.h>
/* 
    Simple Parser
*/
int parser (int argc, char* argv[]) {
    // Check if an argument as been passed
    if (argc < 2) {
        // Pop an error if no arguments were passed
        std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
        return 1;
    }
    // Tell user the file was taken in
    std::cout << argv[0] << " has been given the file " << argv[1] << "!" << std::endl;

    return 0;
}   

// Process:
// Pull the Seed values from the file, push into vector "source"
// Check if the next line is empty, a map, or data
// If data, then we can update the "source" vector ONCE. 
// To ensure it does not get updated more than once, a "valid" vector is set to "1" for that seed pos
// The "source" vector has an equation based on the Advent of Code problem
// Every time we read in a new map, reset the "valid" vector to all "0".
int main(int argc, char* argv[]) {
    // Check if file is passed
    if (parser(argc,argv) == 1) { // Call the parser
        return 0;
    }

    // Variables
    int sum = UINT32_MAX; // Smallest
    

    /* Read in File */
    std::string line; // Individual Lines
    std::string type;
    std::string map;

    // U32 Data
    std::vector<u_int32_t> source; // Source vector, contains seeds then soil then fertilizer...
    std::vector<bool> valid; // Used to check if the source vector has been updated. Reset on each new map
    u_int32_t destRangeStart;
    u_int32_t sourceRangeState;
    u_int32_t range;

    u_int32_t num;
    int cnt = 0;
    bool toggleData = 0;

    // Open and read File
    std::ifstream file(argv[1]);

    // Read first line of file and grab seeds 
    if (file.good()){
        getline(file,line); // Grab line
        line.erase(line.begin(),line.begin() + line.find(":")+2);
        // Create stringstream
        std::stringstream seed(line);
        // Grab seed values
        while(seed >> num) {
            source.push_back(num);
        }
    }
    valid.assign(source.size(),false);
    
    // Iterate through each Line
    while(getline(file,line)){
        // Spin up stringstream!
        std::stringstream ss(line);
        // If line is empty, we know there will be a map next
        if (line.empty()){
            toggleData = false;
        }
        // If we read a map in, we know data is next
        else if (toggleData == false){
            // Read in Map
            ss >> type >> map;
            // Get ready to read Data!
            if(map == "map:"){
                toggleData = true;
                // Reset Valid Vector as new Data sequence
                valid.assign(source.size(),false);
            }
        // Read in the data
        } else if (toggleData == true){
            // Read in Date
            ss >> destRangeStart >> sourceRangeState >> range;
            for(int i = 0; i < source.size(); i++){
                // Does the source exist in the source range and has it not been changed previously?
                if (valid[i] == false && source[i] >= sourceRangeState && source[i] < sourceRangeState + range){
                    // From Advent Of Code problem, worked up equation!
                    source[i] = destRangeStart + (source[i]-sourceRangeState); 
                    // Tell system the value in source has been changed in this iteration of data
                    valid[i] = true;
                }
            }            
        }
    }

    // Calculate smallest value in source vector
    for (auto i : source){
        if (i < sum){
            sum = i;
        }
    }

    std::cout << "MIN: " << sum << std::endl;

    return 0;
}
