//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_DISK_PLATES_SET_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_DISK_PLATES_SET_HPP
//#pragma once

#include "Disk_Plate.hpp"
#include <tuple>
#include <vector>
#include <cmath>

class Disk_Block;

class Disk_Plates_Set {
private:
    std::vector<Disk_Plate> m_disk_plates;
    int m_number_of_blocks;
    int m_number_of_blocks_per_plate;
    int m_size_of_block;
public:
    Disk_Plates_Set(int a_number_of_plates, int a_outer_number_of_blocks, int a_size_of_blocks);

    const Disk_Block& get_block(int a_block_address) const;

    int get_number_of_tracks() const;

    int get_number_of_outer_blocks() const;

    int get_number_of_blocks_on_track(int a_track) const;

    int get_number_of_plates() const;

    int get_number_of_blocks_on_tracks() const {
        return m_number_of_blocks;
    }
    std::vector<int> get_number_of_blocks_on_each_track() const {
        std::vector<int> res;
        int tracks = get_number_of_tracks();
        int blocks = std::pow(2, tracks - 1);
        for(int i = 0; i < tracks; i++){
            res.push_back(blocks);
            blocks /= 2;
        }
        return res;
    }

    void set_block(int a_block_address, int a_data);

    std::tuple<int, int, int> read_address(int a_block_address) const;
};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_DISK_PLATES_SET_HPP
