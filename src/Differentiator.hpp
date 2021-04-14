#pragma once

#include <fstream>
#include <vector>
#include "FileManager.hpp"

namespace OBD {

class Differentiator {
    OBD::File file1_;
    OBD::File file2_;

    std::string content1;
    std::string content2;
public:
    Differentiator(const OBD::File & file1, const OBD::File & file2);

    bool WriteDiff(std::ofstream & output);

    void CalcDiff();

private:
    std::pair<std::string, std::string>
    Hirschberg(std::vector<char>::iterator & begin1, std::vector<char>::iterator & end1,
               std::vector<char>::iterator & begin2, std::vector<char>::iterator & end2);

    std::vector<int> NWScore(std::vector<char>::iterator & begin1, std::vector<char>::iterator & end1,
                             std::vector<char>::iterator & begin2, std::vector<char>::iterator & end2);

};

}
