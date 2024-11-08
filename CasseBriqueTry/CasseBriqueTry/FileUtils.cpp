#include "FileUtils.h"
#include <fstream>

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}
