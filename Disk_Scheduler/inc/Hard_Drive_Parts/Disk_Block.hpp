//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_DISK_BLOCK_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_DISK_BLOCK_HPP

#include "stdexcept"


class Disk_Block {
    friend class Disk_Track;

private:
    int m_size; // size in bytes
    int m_data;

    explicit Disk_Block(int a_size = 512) {
        if (a_size <= 0) {
            throw std::invalid_argument(std::string("Disk_Block::Disk_Block(int):\nGiven size is illegal!\n\tsize = ") + std::to_string(a_size));
        }
        m_size = a_size;
        m_data = 0;
    }

public:
    int get_size() const { return m_size; }

    void set_data(const int a_data) {
        m_data = a_data;
    }

    int get_data() const {
        return m_data;
    }

    void foo();
};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_DISK_BLOCK_HPP
