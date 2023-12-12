#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cmath>
#include<stdint.h>
#include<algorithm>
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
// Uses the following equation to calculate how long the button can be 
// pressed down to beat the record distance. 
// Equation: 
// Distance = (Total Time - Time Button Pushed)*(Time Button Pushed)
int main(int argc, char* argv[]) {
    // Check if file is passed
    if (parser(argc,argv) == 1) { // Call the parser
        return 0;
    }

    // Variables
    uint64_t sum = 0;
    uint64_t eqn;
    uint64_t timeVal;
    uint64_t distVal;
    

    /* Read in File */
    std::string line; // Individual Lines
    int num;

    // Open and read File
    std::ifstream file(argv[1]);

    // Read first two lines of file and grab seeds 
    if (file.good()){
        // Grab Times
        getline(file,line); // Grab line
        line.erase(line.begin(),line.begin() + line.find(":")+2); // Remove header
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); // Remove space
        std::stringstream ss(line); // Stringstream as u64..
        ss >> timeVal;

        // Grab Distances
        getline(file,line); // Grab line
        line.erase(line.begin(),line.begin() + line.find(":")+2); // Remove header
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); // Remove spaces
        std::stringstream ss1(line); // Stringstream as u64..
        ss1 >> distVal;
    }

    // Range 0 - times[i]
    for (int j = 0; j < timeVal; j++){
        eqn = (timeVal - j)*j;
        if(eqn > distVal){
            sum++; 
        }
    }
    
    std::cout << "sum: " << sum << std::endl;

    return 0;
}
