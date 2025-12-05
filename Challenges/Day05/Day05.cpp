#include "../Utils/AoCUtils.h"
#include <iostream>
#include <sstream>

// To challenge myself, I made the sorting and such from scratch
std::vector<std::pair<long long, long long>> insertionSortIDPairs (std::vector<std::pair<long long, long long>> inputList) {
    if (inputList.size() == 1) {
        return inputList;
    } else {
        std::vector<std::pair<long long, long long>> returnVec;
        std::vector<std::pair<long long, long long>> firstPart = \
            insertionSortIDPairs(std::vector<std::pair<long long, long long>>(inputList.begin(), inputList.begin() + inputList.size() / 2));
        std::vector<std::pair<long long, long long>> secondPart = \
            insertionSortIDPairs(std::vector<std::pair<long long, long long>>(inputList.begin() + inputList.size() / 2, inputList.end()));

        while (firstPart.size() > 0 && secondPart.size() > 0) {
            if (firstPart[0].first < secondPart[0].first) {
                returnVec.push_back(firstPart[0]);
                firstPart.erase(firstPart.begin());
            } else {
                returnVec.push_back(secondPart[0]);
                secondPart.erase(secondPart.begin());
            }
        }

        if (firstPart.size() > 0) {
            returnVec.insert(returnVec.end(), firstPart.begin(), firstPart.end());
        }
        if (secondPart.size() > 0) {
            returnVec.insert(returnVec.end(), secondPart.begin(), secondPart.end());
        }

        return returnVec;
    }
}


int main (int argc, char *argv[]) {
    // This class handles your input
    // Make sure to replace the contents of 'input.txt' or modify the code below
    // Functions supported by this class can be found in `AoCUtils.h`
    std::string full_path = argv[0];
    size_t last_slash = full_path.find_last_of('/');
    std::string day_name = full_path.substr(last_slash + 1);
    AoCUtils::InputFile challengeInput = AoCUtils::InputFile("Challenges/" + day_name + "/input.txt");

    std::vector<std::string> challengeInputVec = challengeInput.getParsedInput();
    std::vector<std::pair<long long, long long>> llVec;
    std::string temp;
    std::pair<long long, long long> tempTwo;
    int count = 0;
    for (std::string line : challengeInputVec) {
        if (line == "") {break;}
        std::stringstream ci(line);
        std::getline(ci, temp, '-');
        tempTwo.first = stoll(temp);
        std::getline(ci, temp, '-');
        tempTwo.second = stoll(temp);
        llVec.push_back(tempTwo);
        count ++;
    }

    count ++; // this is the line at which individual ids begin


    llVec = insertionSortIDPairs(llVec);

    // Combine unnecessary pairs
    for (int i = 0; i < llVec.size() - 1; NULL) {
        if (llVec[i].second >= llVec[i+1].first) {
            if (llVec[i].second < llVec[i+1].second) {llVec[i].second = llVec[i+1].second;};
            llVec.erase(llVec.begin() + i + 1);
        } else {
            i++;
        }
    }

    int partOneCount = 0;

    for (int j = count; j < challengeInputVec.size(); j++) {
        for (int k = 0; k < llVec.size(); k++) {
            if (stoll(challengeInputVec[j]) >= llVec[k].first && stoll(challengeInputVec[j]) <= llVec[k].second) {
                partOneCount++;
                break;
            }
        }
    }
    long long partTwoCount = 0;
    for (int l = 0; l < llVec.size(); l++) {
        partTwoCount += llVec[l].second - llVec[l].first + 1;
    }

    std::cout << "Part One: " << partOneCount << std::endl;
    std::cout << "Part Two: " << partTwoCount << std::endl;
}