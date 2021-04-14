#pragma once

#include <iostream>
#include <fstream>
#include "BinaryIterator.hpp"

namespace OBD {

class File {
    char * content_;
    size_t size_;
public:
    File(const std::string & filename);

    ~File();

    bool LocateBinary(size_t pos) const;

    size_t size() const;
    size_t binary_size() const;

    static std::ifstream ReadBinary(std::string filename) {
        std::ifstream input(filename, std::ios::binary);
        return std::move(input);
    }

    static std::ofstream WriteBinary(std::string filename) {
        std::ofstream output(filename, std::ios::binary);
        return std::move(output);
    }

    char * GetContent() {
        return content_;
    }

    static size_t Len(std::string filename) {
        std::ifstream is(filename, std::ifstream::binary);
        is.seekg(0, is.end);
        size_t length = is.tellg();
        is.seekg(0, is.beg);
        is.close();

        return length;
    }
};

}


