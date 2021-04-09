//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_DISK_PLATE_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_DISK_PLATE_HPP
#include "Disk_Track.hpp"
#include <vector>

class Disk_Block;

class Disk_Plate{
    friend class Disk_Plates_Set;
private:
    std::vector<Disk_Track> m_disk_tracks;
    int m_number_of_tracks; // each track is half size of the previous one
    int m_size_of_blocks;
    int m_outer_number_of_blocks;
    Disk_Plate(int a_number_of_blocks, int a_size_of_blocks);
    Disk_Plate(int a_number_of_tracks , int a_outer_number_of_blocks, int a_size_of_blocks);
    const Disk_Block& get_block(int a_track_index, int a_block_index) const;
    void set_block(int a_track_index, int a_block_index, int a_data);
    void validate_track_and_block_indices(int a_track_index, int a_block_index) const;
    int get_outer_number_of_blocks() const {
        return m_outer_number_of_blocks;
    }
};
#endif //HARD_DRIVE_ACCESS_ALGORITHMS_DISK_PLATE_HPP
