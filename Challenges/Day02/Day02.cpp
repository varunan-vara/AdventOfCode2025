#include "../Utils/AoCUtils.h"
#include <iostream>

long long getTenExp (int exp) {
    std::string outputString = "1";
    for (int i = 0; i < exp; i++) {
        outputString.append("0");
    }
    return stoll(outputString);
}

std::vector<std::string> splitInHalf (std::string inputString) {
    return std::vector<std::string>{inputString.substr(0,inputString.size() / 2), inputString.substr(inputString.size() / 2)};
}

std::vector<int> factors (int input) {
    std::vector<int> returnvec;
    for (int i = 0; i <= input/2; i++) {
        if (input % i == 0) {returnvec.push_back(i);}
    }
    return returnvec;
}

long long concatNumbers(long long number, int numberOfTimes) {
    std::string returnString;
    for (int i = 0; i < numberOfTimes; i++) {
        returnString = returnString + std::to_string(number);
    }
    return stoll(returnString);
}

int main (int argc, char *argv[]) {
    // This class handles your input
    // Make sure to replace the contents of 'input.txt' or modify the code below
    // Functions supported by this class can be found in `AoCUtils.h`
    std::string full_path = argv[0];
    size_t last_slash = full_path.find_last_of('/');
    std::string day_name = full_path.substr(last_slash + 1);
    AoCUtils::InputFile challengeInput = AoCUtils::InputFile("Challenges/" + day_name + "/input.txt");

    std::vector<std::string> rangeStrings = challengeInput.getDelimited2DArray(',')[0];
    std::vector<std::vector<std::string>> ranges = AoCUtils::InputFile::getDelimited2DArray(rangeStrings, '-');

    long long invalidSumP1 = 0, invalidSumP2 = 0, upperBound, lowerBound, lbfh, ubfh, testNum; // lbfh -> lower bound first half
    std::vector<int> numDigitsFactors;
    std::vector<long long> invalidSumP2vec;
    // Iterate over each range
    for (const std::vector<std::string> range : ranges) {
        // Split the ranges based on number of digits
        for (int x = range[0].size(); x <= range[1].size(); x++) {

            lowerBound = (range[0].size() == x) ? stoll(range[0]) : getTenExp(x - 1);
            upperBound = (range[1].size() == x) ? stoll(range[1]) : getTenExp(x) - 1;
            

            // Part 1:
            // Split the string version of the number into 2, then iterte over the first half. Recreate the
            // repeating digit number, check if in bounds, and add to invalid number counter
            if (x % 2 == 0) {
            lbfh = stoll(splitInHalf(std::to_string(lowerBound))[0]);
            ubfh = stoll(splitInHalf(std::to_string(upperBound))[0]);
                for (int y = lbfh; y <= ubfh; y++) {
                    testNum = stoll(std::to_string(y) + std::to_string(y));
                    if (testNum >= lowerBound && testNum <= upperBound) {
                        invalidSumP1 += testNum;
                    }
                }
            }

            // Part 2:
            // Find the factors of the number of digits - this is the number of digits that can repeat
            // in the total number. Then, repeat the approach for Part 1 - recreate the number, and check
            numDigitsFactors = factors(x);
            for (const int fac : numDigitsFactors) {
                lbfh = stoll(std::to_string(lowerBound).substr(0,fac));
                ubfh = stoll(std::to_string(upperBound).substr(0,fac));

                for (int z = lbfh; z <= ubfh; z++) {
                    testNum = concatNumbers(z,x/fac);
                    if (testNum >= lowerBound && testNum <= upperBound) {
                        std::cout << testNum << std::endl;
                        auto finder = std::find(invalidSumP2vec.begin(), invalidSumP2vec.end(), testNum);
                        if (finder == invalidSumP2vec.end()) {invalidSumP2vec.push_back(testNum);}
                    }
                }
            }
        }
    }  


    for (int a = 0; a < invalidSumP2vec.size(); a++) {
        invalidSumP2 += invalidSumP2vec[a];
    }

    std::cout << "Part 1: " << invalidSumP1 << std::endl;
    std::cout << "Part 2: " << invalidSumP2 << std::endl;
}