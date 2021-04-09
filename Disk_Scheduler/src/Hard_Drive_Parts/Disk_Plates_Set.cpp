//
// Created by jakub on 06.04.2021.
//

#include "Disk_Plates_Set.hpp"
#include <stdexcept>
#include <cmath>

Disk_Plates_Set::Disk_Plates_Set(int a_number_of_plates, int a_number_of_blocks_per_plate, int a_size_of_blocks) {
    if (a_number_of_plates <= 0 || (a_number_of_blocks_per_plate + 1) % 2 != 0 || a_size_of_blocks % 2 != 0) {
        throw std::invalid_argument(std::string("Disk_Plates_Set::Disk_Plates_Set(int, int, int):\nGiven arguments are illegal!\n\t number of plates = "
                                                + std::to_string(a_number_of_plates)
                                                        .append("\n\tnumber of blocks per plate = ")
                                                + std::to_string(a_number_of_blocks_per_plate)
                                                        .append("\n\tsize of blocks = ")
                                                + std::to_string(a_size_of_blocks)));
    }
    m_number_of_blocks_per_plate = a_number_of_blocks_per_plate;
    m_number_of_blocks = a_number_of_plates * a_number_of_blocks_per_plate;
    m_size_of_block = a_size_of_blocks;
    m_disk_plates.reserve(a_number_of_plates);
    for (int i = 0; i < a_number_of_plates; i++) {

        m_disk_plates.push_back(Disk_Plate(m_number_of_blocks_per_plate, m_size_of_block));
    }
}

const Disk_Block& Disk_Plates_Set::get_block(int a_block_address) const {
    if (a_block_address < 0 || a_block_address >= m_number_of_blocks) {
        throw std::out_of_range(std::string("Disk_Plates_Set::get_block(int):\ngiven address doesn't exist!")
                                        .append("passed block address = ")
                                + std::to_string(a_block_address)
                                        .append("Max address = ")
                                + std::to_string(m_number_of_blocks));
    }
    std::tuple<int, int, int> plate_track_block = read_address(a_block_address);
    return m_disk_plates[std::get<0>(plate_track_block)]
            .get_block(std::get<1>(plate_track_block), std::get<2>(plate_track_block));
}

int Disk_Plates_Set::get_number_of_tracks() const {
    return m_disk_plates[0].m_number_of_tracks;
}
int Disk_Plates_Set::get_number_of_outer_blocks() const {
    return m_disk_plates[0].get_outer_number_of_blocks();
}

int Disk_Plates_Set::get_number_of_blocks_on_track(int a_track) const {
    return std::pow(2, m_disk_plates[0].m_number_of_tracks - 1 - a_track);
}

int Disk_Plates_Set::get_number_of_plates() const {
    return m_disk_plates.size();
}

void Disk_Plates_Set::set_block(int a_block_address, int a_data) {
    if (a_block_address < 0 || a_block_address >= m_number_of_blocks) {
        throw std::out_of_range(std::string("Disk_Plates_Set::set_block(int, int):\nGiven block address either exceeds max or is negative!")
                                        .append("passed block address = ")
                                + std::to_string(a_block_address)
                                        .append("Max address = ")
                                + std::to_string(m_number_of_blocks - 1));
    }
    std::tuple<int, int, int> plate_track_block = read_address(a_block_address);
    m_disk_plates[std::get<0>(plate_track_block)]
            .set_block(std::get<1>(plate_track_block), std::get<2>(plate_track_block), a_data);
}

// returns <plate number, track_number, block_number>
std::tuple<int, int, int> Disk_Plates_Set::read_address(int a_block_address) const {
//    std::tuple<int, int, int> res_plate_track_block;
    int blocks_on_track = m_disk_plates[0].get_outer_number_of_blocks();
    int plate = 0;
    int track = 0;
    int block = 0;
    int address = -1; // Offset from the fact that first address starts at 0 and ends at n - 1, when n = number of elements
    int number_of_plates = m_disk_plates.size();
    while (address != a_block_address) {
        address += blocks_on_track * number_of_plates;
        if (address >= a_block_address) {
            plate = (number_of_plates - 1) - (address - a_block_address) / blocks_on_track;
            // a_block_address + blocks_on track is for first n elements [0, n-1], where n = blocks_on_track
            block = (a_block_address + blocks_on_track) % blocks_on_track;
            return std::make_tuple(plate, track, block);
        } else if (address < a_block_address) {
            track++;
            blocks_on_track /= 2;
        }
    }
    return std::make_tuple(plate, track, block);
}
