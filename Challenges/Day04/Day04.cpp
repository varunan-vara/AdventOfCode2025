#include "../Utils/AoCUtils.h"
#include <iostream>
#include <tuple>

int threeCachedItems (AoCUtils::InputFile challengeInput, int yIndex, int xIndex) {
    // First int is line index (y), second int is along the line (x)
    int returnValue = 0;
    if (xIndex > 0 && challengeInput.getGridValue(xIndex - 1, yIndex) == '@') {
        returnValue ++;
    }
    if (challengeInput.getGridValue(xIndex, yIndex) == '@') {
        returnValue ++;
    }
    if (xIndex < challengeInput.numberOfChars() - 1 && challengeInput.getGridValue(xIndex + 1, yIndex) == '@') {
        returnValue ++;
    }

    return returnValue;
}

int main (int argc, char *argv[]) {
    // This class handles your input
    // Make sure to replace the contents of 'input.txt' or modify the code below
    // Functions supported by this class can be found in `AoCUtils.h`
    std::string full_path = argv[0];
    size_t last_slash = full_path.find_last_of('/');
    std::string day_name = full_path.substr(last_slash + 1);
    AoCUtils::InputFile challengeInput = AoCUtils::InputFile("Challenges/" + day_name + "/input.txt");

    int partOneCounter = 0, partTwoCounter = 0, temp;
    bool rollRemoved = true, isFirstTime = true;


    while (rollRemoved) {
        rollRemoved = false;
        for (int y = 0; y < challengeInput.numberOfLines(); y++) {
            for (int x = 0; x < challengeInput.numberOfChars(); x++) {
                if (challengeInput.getGridValue(x,y) == '.') {continue;}
                temp = threeCachedItems(challengeInput, y, x);

                if (y > 0) {
                temp += threeCachedItems(challengeInput, y-1, x);
                }
                if (y < challengeInput.numberOfLines() - 1) {
                temp += threeCachedItems(challengeInput, y+1, x);
                }
                // std::cout << "(" << y << "," << x << "): " << temp << std::endl;
                temp -= (challengeInput.getGridValue(x,y) == '@') ? 1 : 0;

                if (temp < 4) {
                    partTwoCounter ++;
                    if (!isFirstTime) {
                        challengeInput.setGridValue(x,y,'.');
                    }
                    rollRemoved = true;
                }

            }
        }
        if (isFirstTime) {
            partOneCounter = partTwoCounter;
            partTwoCounter = 0;
            isFirstTime = false;
        }
    }

    std::cout << "Part 1: " << partOneCounter << std::endl;
    std::cout << "Part 2: " << partTwoCounter << std::endl;
}