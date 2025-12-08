#include "../Utils/AoCUtils.h"
#include <iostream>
#include <cmath>

#define CONNECTIONS 1000

long long distance(std::vector<long long> pointOne, std::vector<long long> pointTwo) {
    return sqrt(
        pow(pointTwo[0] - pointOne[0], 2) + \
        pow(pointTwo[1] - pointOne[1], 2) + \
        pow(pointTwo[2] - pointOne[2], 2)
    );
}

class Distance {
    public:
        std::vector<long long> pointOne, pointTwo;
        long long d;
        Distance(std::vector<long long> pO, std::vector<long long> pT) {
            pointOne = pO, pointTwo = pT;
            d = distance(pointOne, pointTwo);
        }
};

// Used GeeksforGeeks to refresh what a heap looks like
class DistanceHeap {
    public:
        std::vector<Distance> heap;
        void swap(int indexOne, int indexTwo) {
            Distance temp = heap[indexOne];
            heap[indexOne] = heap[indexTwo];
            heap[indexTwo] = temp;
        }
        void insert(Distance d) {
            heap.push_back(d);
            int childIndex = heap.size() - 1;
            while (childIndex > 0 && heap[(childIndex - 1) / 2].d > heap[childIndex].d) {
                swap(childIndex, (childIndex - 1) / 2);
                childIndex = (childIndex - 1) / 2;
            }
        }
        void deleteMin() {
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();
            int si = 0;
            while (true) {
                int left = si * 2 + 1;
                int right = si * 2 + 2;
                int current = si;
                if (left < heap.size() - 1 && heap[left].d < heap[current].d) {
                    current = left;
                }
                if (right < heap.size() - 1 && heap[right].d < heap[current].d) {
                    current = right;
                }
                if (current != si) {
                    swap(current, si);
                    si = current;
                } else {break;}
            }
        }
};

int main (int argc, char *argv[]) {
    // This class handles your input
    // Make sure to replace the contents of 'input.txt' or modify the code below
    // Functions supported by this class can be found in `AoCUtils.h`
    std::string full_path = argv[0];
    size_t last_slash = full_path.find_last_of('/');
    std::string day_name = full_path.substr(last_slash + 1);
    AoCUtils::InputFile challengeInput = AoCUtils::InputFile("Challenges/" + day_name + "/input.txt");

    std::vector<std::vector<std::string>> coordinatesString = challengeInput.getDelimited2DArray(',');
    std::vector<std::vector<long long>> coordinates;
    std::vector<long long> temp;

    for (std::vector<std::string> coordinate : coordinatesString) {
        temp.clear();
        for (std::string number : coordinate) {
            temp.push_back(stoll(number));
        }
        coordinates.push_back(temp);
    }

    // Strategy: First, do all the calculations
    std::vector<Distance> distances;

    for (int i = 0; i < coordinates.size(); i++) {
        for (int j = i + 1; j < coordinates.size(); j++) {
            distances.push_back(Distance(coordinates[i], coordinates[j]));
        }
    }

    DistanceHeap dh;

    for (Distance d : distances) {
        dh.insert(d);
    }
    
    // for (Distance d : dh.heap) {
    //     std::cout << d.d << ",";
    // }
    std::vector<std::vector<std::vector<long long>>> circuits;
    int i = 0;


    while (dh.heap.size() > 0) {
        Distance tempD = (dh.heap[0]);
        dh.deleteMin();
        int circuitOne = -1, circuitTwo = -1;

        for (int m = 0; m < circuits.size(); m++) {
            auto itOne = std::find(circuits[m].begin(), circuits[m].end(), tempD.pointOne);
            auto itTwo = std::find(circuits[m].begin(), circuits[m].end(), tempD.pointTwo);
            if (itOne != circuits[m].end()) {
                circuitOne = m;
            }
            if (itTwo != circuits[m].end()) {
                circuitTwo = m;
            }
        }

        // Cases:
        // 1. If both are -1, create a new circuit
        if (circuitOne == -1 && circuitTwo == -1) {
            circuits.push_back(std::vector<std::vector<long long>>{tempD.pointOne, tempD.pointTwo});
        // 2A & B. If one is -1, and the other isn't
        } else if ((circuitOne == -1) != (circuitTwo == -1)) {
            if (circuitOne == -1) {
                circuits[circuitTwo].push_back(tempD.pointOne);
            } else {
                circuits[circuitOne].push_back(tempD.pointTwo);
            }
        // 3. Both are not -1, not equal -> merge
        } else if (circuitOne != circuitTwo) {
            circuits[circuitOne].insert(circuits[circuitOne].end(), circuits[circuitTwo].begin(), circuits[circuitTwo].end());
            circuits.erase(circuits.begin() + circuitTwo);
        // 4. Both are not -1, and equal -> do nothing
        }

        i++;
        if (i == CONNECTIONS) {
            // Screw it, I'm not making a heap for this
            std::sort(circuits.begin(), circuits.end(),[](const std::vector<std::vector<long long>>& a, const std::vector<std::vector<long long>>& b) {return a.size() > b.size(); });
            std::cout << "Part 1: " << circuits[0].size() * circuits[1].size() * circuits[2].size() << std::endl;
        }

        if (circuits.size() == 1 && circuits[0].size() == coordinates.size()) {
            std::cout << "Part 2: " << (long long) tempD.pointOne[0] * tempD.pointTwo[0] << std::endl;
            break;
        }
    }


    // for (std::vector<std::vector<long long>> circuit : circuits) {
    //     std::cout << circuit.size() << std::endl;
    // }

}