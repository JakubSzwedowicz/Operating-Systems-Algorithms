//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_DISK_TRACK_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_DISK_TRACK_HPP
#pragma once

#include "Disk_Block.hpp"
#include <memory>
#include <vector>

class Disk_Block;

class Disk_Track{
    friend class Disk_Plate;
public:
    Disk_Track(Disk_Track&&) = default;
private:
    int m_number_of_blocks;
    int m_blocks_size;
    std::vector<Disk_Block> m_disk_blocks;
    Disk_Track(int a_number_of_blocks, int a_sectors_size);
    int get_number_of_blocks() const {return m_number_of_blocks;}
    int get_block_size() const {return m_blocks_size;}
    const Disk_Block& get_disk_block(int) const;
    void set_disk_block(int, int);
};
#endif //HARD_DRIVE_ACCESS_ALGORITHMS_DISK_TRACK_HPP
