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

void print2dVector(std::vector<std::vector<char>> vec){
    for ( const auto &row : vec )
    {
        for ( const auto &s : row ) std::cout << s << ' ';
        std::cout << std::endl;
    }
}

struct pos {
    std::vector<int> x = {-1,0,1};
    std::vector<int> y = {-1,0,1};
};

struct stars {
    int val;
    int x,y;

    stars(int v, int px, int py) : val(v), x(px), y(py) {}
};

// Checks if new star coords already exists. Return element if it does.
int findPositionIndex(std::vector<stars>& star, int px, int py) {
    for (size_t i = 0; i < star.size(); ++i) {
        if (star[i].x == px && star[i].y == py) {
            return static_cast<int>(i);  // Return the index if position exists
        }
    }
    return -1;  // Return -1 if position not found in the vector
}

// Boundary Checking
bool validPosition(std::vector<std::vector<char>> map, int x, int y){
    // Is x valid?
    if (x >= 0 && x < map[0].size()){
        // is y valid?
        if (y >= 0 && y < map.size()){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    // Check if file is passed
    if (parser(argc,argv) == 1) { // Call the parser
        return 0;
    }

    // Variables
    int sum = 0; // Keep count sum of part numbers
    pos pos_;
    std::vector<stars> star;

    /* Read in the part numbers */
    std::string line; // Individual Lines
    std::vector<std::vector<char>> map;
    std::vector<char> mapTemp;
    std::string numStr = "";
    bool validNum = false;
    int starIdx;
    int tempX;
    int tempY;


    // Open and read File
    std::ifstream file(argv[1]);

    // Iterate through each Line
    while(std::getline(file,line)){
        for (char letter : line){
            mapTemp.push_back(letter);
        }
        map.push_back(mapTemp);
        mapTemp.clear();
    }


    // Run through the map. If you find a digit, check around it for any symbols.
    // EACH ROW
    for (int i = 0; i < map.size(); i++) {
        // EACH COLUMN
        for (int j = 0; j < map[i].size(); j++){
            // Check if element is a digit
            if (isdigit(map[i][j])){
                numStr += map[i][j]; // Add to string number
                // Look around element to see if there is a symbol adjacent. Also do boundary checking..
                //std::cout << "VALID POINTS: (" << j << "," << i << ")" << std::endl;
                for (int k = 0; k < pos_.y.size(); k++){
                    for (int l = 0; l < pos_.x.size(); l++){
                        if(validPosition(map,j+pos_.x[l],i+pos_.y[k])) {
                            //std::cout << "CHECKED POINTS: (" << j+pos_.x[l] << "," << i+pos_.y[k] << ")" << std::endl;
                            if(map[i+pos_.y[k]][j+pos_.x[l]] == '*'){
                                // Does star exist? -1 if no, some index if yes
                                starIdx = findPositionIndex(star,j+pos_.x[l],i+pos_.y[k]);
                                // Store Star info for later when we propogate it with numStr
                                tempX = j+pos_.x[l];
                                tempY = i+pos_.y[k];
                                validNum = true;    
                            }
                        }
                    }
                }
            // If it is not a digit, stop recording into numStr.
            } else {
                // If valid number is set, then there is a adjacent symbol to the numStr. Add to sum
                if(validNum){
                    // If star exists already, grab the existing Value to multiply with
                    if (starIdx >= 0) {
                        sum += stoi(numStr)*star[starIdx].val;
                    // Otherwise add new star data 
                    } else {
                        star.push_back(stars(stoi(numStr),tempX,tempY));
                    }
                }
                // Reset number being valid
                validNum = false;
                numStr.clear();
            }
        }
        // END OF ROW CASE: If valid number is set, then there is a adjacent symbol to the numStr. Add to sum
        if(validNum){
            // If star exists already, grab the existing Value to multiply with
            if (starIdx >= 0) {
                std::cout << "numStr: " << numStr << " star: " << star[starIdx].val << std::endl;
                sum += stoi(numStr)*star[starIdx].val;
            // Otherwise add new star data 
            } else {
                star.push_back(stars(stoi(numStr),tempX,tempY));
            }
        }
        // Reset number being valid
        validNum = false;
        numStr.clear();
    }

    print2dVector(map);

    std::cout << "SUM: " << sum << std::endl;
    return 0;
}
