// Advent of Code Day 1, Pt 2
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



/*
    Finds strings in a string and replaces them with other strings..
*/
void stringFindReplaceAll(std::string &s, std::vector<std::string> &toReplace, std::vector<std::string> &replaceWith){
    // Go through the toReplace array
    for(int i = 0; i < toReplace.size(); i++){
        // Find hits in the string
        while (s.find(toReplace[i]) != std::string::npos){
            // Replace those hits with replaceWith
            s.replace(s.find(toReplace[i]),toReplace[i].size(),replaceWith[i]);
        }
    }
}



int main(int argc, char* argv[]) {
    // Look Up Tables
    std::vector<std::string> ones {"one","two","three","four","five","six","seven","eight","nine"};
    std::vector<std::string> char_ones {"o1e","t2o","th3ee","f4ur","f5ve","s6x","se7en","ei8th","n9ne"};
    // Using stuff like o1e, t2o is quite funny. Basically imagine we had oneight. 
    // Since they both share that e, replacing "one" with "1" would result in "1ight".
    // However, we want it in the end to turn into 18. So instead we can do the above substitution.
    // -> "o1ei8th" which preserves the length and gives us that 1 and 8 which we can pick up later!

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
        // Find instances of spelled out digits in each line and replace them with digits
        stringFindReplaceAll(line,ones,char_ones);

        // Check each line for digits, append these digits to a string
        for(int i = 0; i < line.size(); i++){
            if (isdigit(line[i])) {
                digits += line[i];
            }
        }

        /* Add to summation first and last digits of the line. ex: "ad3g4ls7f" -> 37 added to summation */
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
