// Advent of Code Day 1, Pt 1
// Micheal Caracciolo

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


int main(int argc, char* argv[]) {
    // Check if file is passed
    if (parser(argc,argv) == 1) { // Call the parser
        return 0;
    }

    // Variables
    std::vector<std::string> v; // Vector of File Lines
    std::string line; // Individual Lines
    std::string digits = ""; // Numbers for summation
    std::string num = ""; // First and last integers of line in a string ("ad3g4ls7f" -> 37)
    int sum = 0; // Summation

    // Open and read File
    std::ifstream file(argv[1]);

    // Iterate through each Line
    while(file >> line){
        // Check each line for digits, append these digits to a string
        for(int i = 0; i < line.size(); i++){
            if (isdigit(line[i])) {
                digits += line[i];
            }
        }
        /* Add to summation first and last digits of the line. 
        ex: "ad3g4ls7f" -> 37 added to summation */
        num += digits.front(); // Append first Digit to num
        num += digits.back();  // Append last Digit to num
        sum = sum + stoi(num);  // Update summation
        // Clear Strings
        digits.clear();
        num.clear();
        // Create v vector
        v.push_back(line);
    }
    std::cout << "TOTAL: " << sum << std::endl;

    // For reading out the file
    // for(std::string i : v){
    //     std::cout << i << std::endl;
    // }
    
    return 0;
}
