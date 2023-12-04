#include<iostream>
#include<fstream>
#include<string>
#include<vector>
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

struct game {
    int gameID = 0;
    std::vector<int> blocks = {0,0,0}; // Red, Green, Blue
};

int colorToNumber(std::string s){
    if (s == "red"){
        return 0;
    } else if (s == "green") {
        return 1;
    } else if (s == "blue") {
        return 2;
    } else {
        return -1;
    }
}


int main(int argc, char* argv[]) {
    // Check if file is passed
    if (parser(argc,argv) == 1) { // Call the parser
        return 0;
    }

    // Game Variables
    game aoc; // Advent of code!
    int sum = 0; // Keep count of sum of valid game IDs
    std::vector<int> maxBlocks = {12,13,14}; // Red, Green, Blue

    /* Read in the game records */
    std::string line; // Individual Lines
    std::string tempLine;
    std::vector<std::string> sample; 
    size_t pos; // Temp

    // Open and read File
    std::ifstream file(argv[1]);

    // Iterate through each Line
    while(std::getline(file,line)){
        // Extract Game ID
        tempLine = line; // Copy line over
        tempLine.erase(0,5); // Erase "Game "
        tempLine.erase(tempLine.begin() + tempLine.find(":"),tempLine.end()); // First : to end of string
        aoc.gameID = stoi(tempLine); // Grab Game ID
        //std::cout << "GAME " << aoc.gameID << std::endl;
        
        // Delete Game ID from each game run
        line.erase(line.begin(), line.begin() + line.find(":") + 2);

        // Delete the ; and , from the line
        line.erase(std::remove(line.begin(),line.end(),';'),line.end()); // Remove all ";"
        line.erase(std::remove(line.begin(),line.end(),','),line.end()); // Remove all ","

        // Push each whitespace delimited parts of string into a vector
        // ex: 1 green 2 blue -> {1,green,2,blue}
        std::string token;
        for (char letter : line){
            if (letter == ' '){
                sample.push_back(token);
                token.clear();
            } else {
                token += letter;
            }
        }
        // Grab last piece if it exists
        if (token.length() > 0){
            sample.push_back(token);
            token.clear();
        }

        // Grab number, then see which index of "blocks" it belongs to due to its color
        int idx = 0;
        int val = 0;
        int color = 0;
        for (std::string s : sample){
            if (idx % 2 == 0) { // If even index (this should be the digits)
                val = std::stoi(s); // Grab digit
            } else { // If odd index (this is the color)
                color = colorToNumber(s);
                // Set values into the struct but only if they are greater than current values
                if (val > aoc.blocks[color]) {
                    aoc.blocks[color] = val;
                }
            }
            idx++;
        }

        //std::cout << "GAME " << aoc.gameID << ": " << aoc.blocks[0] << " red " << aoc.blocks[1] << " green " << aoc.blocks[2] << " blue" << std::endl;
    
        // Difference in Part 2!
        sum += aoc.blocks[0]*aoc.blocks[1]*aoc.blocks[2];

        // Clear the Samples
        sample.clear();
        aoc.blocks = {0,0,0};
    }

    std::cout << "SUM: " << sum << std::endl;

    return 0;
}
