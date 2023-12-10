#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

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
    int sum = 0; // Keep count
    

    /* Read in the Card */
    std::string line; // Individual Lines
    std::vector<std::string> winningCard;
    std::vector<std::string> myCard; 
    std::string winningStr; // Temp
    std::string myCardStr; // Temp
    std::string word;
    int cnt = 0;
    int card = 0;
    // This could be cleaner.. oh well
    std::vector<int> numCards(1000);
    numCards.assign(1000,1);

    // Open and read File
    std::ifstream file(argv[1]);

    // Iterate through each Line
    while(std::getline(file,line)){
        // Delete Card number from string
        line.erase(line.begin(),line.begin() + line.find(":")+2);
        
        // Grab first part
        winningStr = line.substr(0,line.find("|")-1);
        // Grab second part
        myCardStr = line.substr(line.find("|")+2);
        
        // Delimit First and Second parts by Spaces
        std::stringstream winningSS(winningStr);
        std::stringstream myCardSS(myCardStr);
        while(winningSS >> word) {
            winningCard.push_back(word);
        }
        while(myCardSS >> word){
            myCard.push_back(word);
        }

        // Cycle through my Card and see how many winning values!
        for (std::string val : myCard){
            for (std::string val2 : winningCard){
                if (val == val2) {
                    cnt+=1;
                }
            }
        }

        // If count of winnings is greater than 0
        if (cnt > 0) {
            // PART 2:
            // Spin up how many instances of cards
            for (int i = 0; i < numCards[card];i++){
                // For each instance, add cnt many cards
                for (int j = 0; j < cnt; j++){
                    numCards[card+j+1]+=1;
                }
            }
        }

        // Clear Vectors
        winningCard.clear();
        myCard.clear();
        cnt = 0;
        card += 1;
    }

    // Calculating sum
    for(int i = 0; i < card; i++){
        sum+=numCards[i];
    }

    std::cout << "SUM: " << sum << std::endl;
    return 0;
}