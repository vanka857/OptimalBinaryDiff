#include <iostream>
#include <fstream>
#include "tests/tests.cpp"
#include "src/FileManager.hpp"
#include "src/Differentiator.hpp"

int main() {
    std::cout << "Hello, 1C! Let's run all tests..." << std::endl;

    tests::runAllTests();

    OBD::File file("old");

    for (size_t i = 0; i < file.size() * 8; ++i) {
        std::cout << file.LocateBinary(i);
    }

//    auto diff_os = OBD::File::WriteBinary("diff");

    return 0;
}
