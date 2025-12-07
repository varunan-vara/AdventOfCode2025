#include "../Utils/AoCUtils.h"
#include <iostream>

#define NUMBER_ROWS 5

int main (int argc, char *argv[]) {
    // This class handles your input
    // Make sure to replace the contents of 'input.txt' or modify the code below
    // Functions supported by this class can be found in `AoCUtils.h`
    std::string full_path = argv[0];
    size_t last_slash = full_path.find_last_of('/');
    std::string day_name = full_path.substr(last_slash + 1);
    AoCUtils::InputFile challengeInput = AoCUtils::InputFile("Challenges/" + day_name + "/input.txt");

    std::vector<std::string> ciVec = challengeInput.getParsedInput();

    // Part 1 & 2 strategy:
    // To find columns (given they vary in width), find the next occurence of a '+' or '*'. Ommit the 
    // space in between each number, then use that number for calculations. Part 1 is straight forward.
    // For Part 2, create an array with n columns, where n is the number of character columns taken up
    // by this virtual column. Then, use modulos to add new digits, and perform necessary calculation.
    size_t t=0,t1,t2,ts;
    bool isMultiply = false;
    long long partOne = 0, partTwo = 0, tempOne, tempTwo;
    std::vector<int> tempTwoVec;
    std::string substring;

    while (t < ciVec[NUMBER_ROWS-1].size()) {
        t1 = ciVec[NUMBER_ROWS-1].find('+',t+1);
        t2 = ciVec[NUMBER_ROWS-1].find('*',t+1);

        ts = (t1 < t2) ? t1 - 1 : t2 - 1;
        isMultiply = ciVec[NUMBER_ROWS-1][t] == '*';

        if (ts >= ciVec[NUMBER_ROWS-1].size()) {ts = ciVec[NUMBER_ROWS-1].size();}

        tempOne = (isMultiply) ? 1 : 0;
        tempTwo = tempOne;
        tempTwoVec.clear(); tempTwoVec.resize(ts-t,0);
        for (int i = 0; i < NUMBER_ROWS - 1; i++) {
            substring = ciVec[i].substr(t,ts-t);
            tempOne = (isMultiply) ? tempOne * stoll(substring) : 
                                     tempOne + stoll(substring);

            for (int j = 0; j < substring.size(); j++) {
                if (substring[j] != ' ') {
                    tempTwoVec[j] = tempTwoVec[j] * 10 + (substring[j] - '0');
                }
            }
        }

        for (int item : tempTwoVec) {
            tempTwo = (isMultiply) ? tempTwo * item : tempTwo + item;
        }

        t = ts + 1;
        partOne += tempOne;
        partTwo += tempTwo;

    }

    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;

}