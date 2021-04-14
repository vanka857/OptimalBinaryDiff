#include <string>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <cstdlib>

#include "FileManager.hpp"

namespace OBD {

File::File(const std::string& filename) {
    int fd = open(filename.c_str(), O_RDONLY, 0640);
    if (fd == -1) {
//        throw 1;
        std::cerr << "asdsad";
    }

    size_ = Len(filename);

    content_ = static_cast<char *>(mmap(NULL, size_, PROT_READ, MAP_SHARED, fd, 0));
}

File::~File() {
    munmap(content_, size_);
}

bool File::LocateBinary(size_t pos) const {
    unsigned char ch = *(content_ + (pos >> 3));
    bool r = (ch >> (7 - pos % 8)) & 0b1;
    return r;
}

size_t File::size() const {
    return size_;
}

size_t File::binary_size() const {
    return size_ * 8;
}

}

