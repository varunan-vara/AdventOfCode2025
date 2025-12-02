#include "../Utils/AoCUtils.h"
#include <iostream>

int main (int argc, char *argv[]) {
    // This class handles your input
    // Make sure to replace the contents of 'input.txt' or modify the code below
    // Functions supported by this class can be found in `AoCUtils.h`
    std::string full_path = argv[0];
    size_t last_slash = full_path.find_last_of('/');
    std::string day_name = full_path.substr(last_slash + 1);
    AoCUtils::InputFile challengeInput = AoCUtils::InputFile("Challenges/" + day_name + "/input.txt");

    // Approach: Get instructions, instructions[x][0] will be the direction, [x][1] will be distance
    std::vector<std::vector<std::string>> instructions = challengeInput.getDelimited2DArray("(.)(\\d+)");

    int arrowValue = 50, dist, modulo;
    int zeroPointsP1 = 0;
    int zeroPointsP2 = 0;

    for (const std::vector<std::string> instruction : instructions) {
        // Reset arrowValue
        dist = (instruction[0] == "R") ? stoi(instruction[1]) : -1 * stoi(instruction[1]);
        
        zeroPointsP2 += (arrowValue + dist < 0) ? (arrowValue + dist) / -100 + 1 : (arrowValue + dist) / 100;
        modulo = ((arrowValue + dist) % 100 + 100) % 100;

        zeroPointsP2 += (arrowValue == 0 && instruction[0] == "L") ? -1 : 0;
        zeroPointsP2 += (modulo == 0 && arrowValue != 0 && instruction[0] == "L") ? 1 : 0;

        zeroPointsP1 += (modulo == 0) ? 1 : 0;
        std::cout << instruction[0] << instruction[1] << " " << arrowValue << " -> " << modulo << ": " << zeroPointsP2 << " (" << ((arrowValue + dist < 0) ? (arrowValue + dist) / -100 + 1 : (arrowValue + dist) / 100) << ")" << std::endl;

        arrowValue = modulo;
    }

    std::cout << "Part 1: " << zeroPointsP1 << std::endl;
    std::cout << "Part 2: " << zeroPointsP2 << std::endl;
}