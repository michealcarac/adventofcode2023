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
    int sum = 1;
    int eqn;
    int sumWins = 0;
    

    /* Read in File */
    std::string line; // Individual Lines
    int num;
    std::vector<int> times;
    std::vector<int> dists;

    // Open and read File
    std::ifstream file(argv[1]);

    // Read first two lines of file and grab seeds 
    if (file.good()){
        // Grab Times
        getline(file,line); // Grab line
        line.erase(line.begin(),line.begin() + line.find(":")+2);
        // Create stringstream
        std::stringstream ss(line);
        // Grab seed values
        while(ss >> num) {
            times.push_back(num);
        }

        // Grab Distances
        getline(file,line); // Grab line
        line.erase(line.begin(),line.begin() + line.find(":")+2);
        // Create stringstream
        std::stringstream ss1(line);
        // Grab seed values
        while(ss1 >> num) {
            dists.push_back(num);
        }
    }

    // Grab each time value, calculate distance and compare to record distance
    for(int i = 0; i < times.size(); i++){
        // Range 0 - times[i]
        for (int j = 0; j < times[i]; j++){
            eqn = (times[i] - j)*j;
            if(eqn > dists[i]){
                sumWins++; 
            }
        }
        // Check if there were wins, if so, multiply it to the sum
        if(sumWins > 0){
            sum = sum*sumWins;
        }
        sumWins = 0;
    }

    std::cout << "sum: " << sum << std::endl;

    return 0;
}
