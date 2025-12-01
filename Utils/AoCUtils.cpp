#include "AoCUtils.h"

namespace AoCUtils {
    InputFile::InputFile(std::string fileName) {
        std::ios::sync_with_stdio(false);
        std::cin.tie(NULL);

        // Use fstream for reading lines
        std::ifstream file_stream(fileName);
    }
}