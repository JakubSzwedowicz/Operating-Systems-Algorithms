//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_HARD_DRIVE_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_HARD_DRIVE_HPP
#pragma once


#include "Disk_Plates_Set.hpp"
#include "IAlgorithm.hpp"
#include "Order.hpp"
#include "IHard_Drive.hpp"


#include <memory>
#include <sstream>
#include <tuple>
#include <cmath>
#include <functional>

//class IAlgorithm;
class Disk_Block;

class Hard_Drive : public IHard_Drive {
private:
    double m_t1;   // time required to move the head for one track
    double m_t2;   // time required to rotate the plate in 360 degrees
    double m_t3;   // time required to read a single block
    int m_head_track;   // number of a trace heads are above
    double m_rotation;     // rotation in degrees the disk is positioned
    int m_current_address;
    Disk_Plates_Set m_disk_plates_set;
public:
    Hard_Drive(const std::string& a_algorithm, double a_t1, double a_t2, int a_number_of_plates,
               int a_number_of_blocks_per_plate, int a_size_of_block);

public:
    const Disk_Block& get_block(int a_block_address) const;

    std::vector<int> get_number_of_blocks_on_each_track() const;

    int get_number_of_plates() const;

    void set_block(int a_block_address, int a_data);

    int read_block(int a_block_address) const;

    void write_block(int a_block_address, int a_data);


    std::tuple<double, double, double> get_times() {
        return std::make_tuple(m_t1, m_t2, m_t3);
    }

    int get_current_address() const {
        return m_current_address;
    }

    int get_current_track() const {
        return m_head_track;
    }

    int get_number_of_blocks_on_tracks() const {
        return m_disk_plates_set.get_number_of_blocks_on_tracks();
    }


    // moves the head to the new address and returns time it took
    double move_to_new_pos(int a_move_to_address);

    // returns the time it takes to move the head to new address
    double calculate_time_to_move_and_read_new_block(int a_move_to_address) const;

private:
    void update_positions(double a_new_rotation, int a_new_track);

    double calculate_time_to_move_and_read_new_block(double a_begin_rotation_of_block, int a_new_track,
                                                     int a_blocks_on_block_track) const;

    double calculate_begin_rotation_of_block(int a_block_index, int a_blocks_on_block_track) const;

    double calculate_time_to_read_block_on_track(int a_blocks_on_block_track) const;

    double calculate_time_to_move_to_begin_of_the_block(double a_new_rotation, int a_new_track,
                                                        int a_blocks_on_block_track) const;
};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_HARD_DRIVE_HPP
