//
// Created by jakub on 06.04.2021.
//

#include "Disk_Track.hpp"
#include "Disk_Block.hpp"
#include <stdexcept>
#include <memory>

Disk_Track::Disk_Track(int a_number_of_blocks, int a_blocks_size) {
    if(a_number_of_blocks <= 0 || a_blocks_size % 2 != 0){
        throw std::invalid_argument(std::string("Disk_Track::Disk_Track(int, int):\nGiven arguments are illegal!\n\tnumber of blocks = ") + std::to_string(a_number_of_blocks));
    }
    m_number_of_blocks = a_number_of_blocks;
    m_blocks_size = a_blocks_size;
    m_disk_blocks.resize(m_number_of_blocks, Disk_Block(m_blocks_size));
}

const Disk_Block& Disk_Track::get_disk_block(int a_index) const {
    if(a_index < 0 || a_index >= m_number_of_blocks){
        throw std::out_of_range(std::string("Disk_Track::get_disk_block(int):\nGiven index is out of range!\n\t index = ") + std::to_string(a_index));
    }
    return m_disk_blocks[a_index];
}

void Disk_Track::set_disk_block(int a_index, int a_data) {
    auto& diskblock = const_cast<Disk_Block&>(get_disk_block(a_index));
    diskblock.set_data(a_data);
}
