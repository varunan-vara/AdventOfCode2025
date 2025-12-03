#include "../Utils/AoCUtils.h"
#include <iostream>
#include <cmath>

long long largestComboDigits (std::string inputString, int size) {
    size_t largestDigitIndex = 0;
    for (int i = 0; i <= inputString.size() - size; i++) {
        if (inputString[i] > inputString[largestDigitIndex]) {
            largestDigitIndex = i;
        }
    }

    if (size > 1) {
        long long nextInt = largestComboDigits(inputString.substr(largestDigitIndex + 1), size - 1);
        return nextInt + (inputString[largestDigitIndex]  - '0') * std::pow(10, size - 1);
    } else {

        return inputString[largestDigitIndex] - '0';
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

    std::string line;

    long long partOne = 0, partTwo = 0;

    for (int i = 0; i < challengeInput.numberOfLines(); i++) {
        line = challengeInput.getLine(i);
        partOne += largestComboDigits(line, 2);
        partTwo += largestComboDigits(line, 12);
    }

    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
}