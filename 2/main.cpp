#include<iostream>
#include<fstream>
#include<string>
#include<vector>

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

