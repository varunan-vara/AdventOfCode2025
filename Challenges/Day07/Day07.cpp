#include "../Utils/AoCUtils.h"
#include <iostream>

long long recurseFunction(AoCUtils::InputFile ci, std::vector<std::vector<long long>> *cache, int line, int index) {
    // Assuming last line is nothing
    if (line == ci.numberOfLines() - 1) {
        return 1;
    }

    if (cache[0][line][index] != 0) {
        return cache[0][line][index];
    }

    if (ci.getGridValue(index, line) == '^') {
        long long t1 = recurseFunction(ci, cache, line+1, index+1), t2 = recurseFunction(ci, cache, line+1, index-1);
        cache[0][line][index] = t1 + t2;
        return t1 + t2;
    } else {
        long long t = recurseFunction(ci, cache, line+1, index);
        cache[0][line][index] = t;
        return t;
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

    std::cout << "Challenge code for " << argv[0] << std::endl;

    std::vector<int> beamColumnsBuf, beamColumns;
    std::vector<std::vector<long long>> cache(challengeInput.numberOfLines(), std::vector<long long>(challengeInput.numberOfChars(),0));

    beamColumnsBuf.push_back(challengeInput.getLine(0).find('S'));


    // For Part 2, use a recursive function that sort of acts like a DFS search algorithm, with a cache just in case
    long long num = recurseFunction(challengeInput, &cache, 1, beamColumnsBuf[0]);

    int numSplits = 0;

    // Part 1:
    // Strategy: Keep a queue of all the different columns with rays currently in them
    // Check if the ray would have hit a splitter, then add all possible combinations back into a new queue
    // If the value is already in the tail of the queue, disregard
    // Replace old queue with new queue
    for (int i = 1; i < challengeInput.numberOfLines(); i++) {

        for (int x = 0; x < beamColumnsBuf.size(); x++) {
            if (challengeInput.getLine(i)[beamColumnsBuf[x]] == '^') {
                numSplits++;
                if (beamColumns.size() <= 0 || beamColumns[beamColumns.size() - 1] != beamColumnsBuf[x] - 1) {
                    beamColumns.push_back(beamColumnsBuf[x] - 1);
                }
                beamColumns.push_back(beamColumnsBuf[x] + 1);
            } else {
                if (beamColumns.size() <= 0 || beamColumns[beamColumns.size() - 1] != beamColumnsBuf[x]) {
                    beamColumns.push_back(beamColumnsBuf[x]);
                }
            }
        }

        beamColumnsBuf = beamColumns;
        beamColumns.clear();
    }

    std::cout << "Part 1: " << numSplits << std::endl;
    std::cout << "Part 2: " << num << std::endl;
}
