//
// Created by jakub on 06.04.2021.
//

#include "Hard_Drive.hpp"
#include "IAlgorithm.hpp"
#include "FIFO_Algorithm.hpp"
#include "SSTF_Algorithm.hpp"
#include "Disk_Block.hpp"
#include "Order.hpp"
#include <memory>
#include <queue>
#include <vector>

Hard_Drive::Hard_Drive(const std::string& a_algorithm, double a_t1, double a_t2, int a_number_of_plates,
                       int a_number_of_blocks_per_plate, int a_size_of_block)
        : IHard_Drive(a_algorithm, *this), m_current_address(0), m_disk_plates_set(a_number_of_plates, a_number_of_blocks_per_plate,
                                                             a_size_of_block){
    if (a_t1 <= 0 || a_t2 <= 0) {
        std::ostringstream output(
                "Hard_Drive::Hard_Drive(const std::string&, double, double, int, int, int):\nGiven parameters are illegal!");
        output << "\n\tt1 = " << a_t1;
        output << "\n\tt2 = " << a_t2;
        throw std::invalid_argument(output.str());
    }
    m_t1 = a_t1;
    m_t2 = a_t2;
    m_t3 = m_t2 / m_disk_plates_set.get_number_of_outer_blocks();
    m_rotation = 0;
    m_head_track = 0;
}

const Disk_Block& Hard_Drive::get_block(int a_block_address) const {
    return m_disk_plates_set.get_block(a_block_address);
}

std::vector<int> Hard_Drive::get_number_of_blocks_on_each_track() const {
    return m_disk_plates_set.get_number_of_blocks_on_each_track();
}

int Hard_Drive::get_number_of_plates() const {
    return m_disk_plates_set.get_number_of_plates();
}

void Hard_Drive::set_block(int a_block_address, int a_data) {
    m_disk_plates_set.set_block(a_block_address, a_data);
}

int Hard_Drive::read_block(int a_block_address) const {
    return get_block(a_block_address).get_data();
}

void Hard_Drive::write_block(int a_block_address, int a_data) {
    set_block(a_block_address, a_data);
}

double Hard_Drive::move_to_new_pos(int a_move_to_address) {
    std::tuple<int, int, int> new_pos = m_disk_plates_set.read_address(a_move_to_address);
    int move_to_track = std::get<1>(new_pos);
    int move_to_block_index = std::get<2>(new_pos);

    // Number of blocks on the track head is supposed to move
    int blocks_on_new_track = m_disk_plates_set.get_number_of_blocks_on_track(move_to_track);

    double move_to_begin_rotation = calculate_begin_rotation_of_block(move_to_block_index, blocks_on_new_track);

    double move_and_read_block_time = calculate_time_to_move_and_read_new_block(move_to_begin_rotation, move_to_track,
                                                                                blocks_on_new_track);
    // calculating the next index of block on this track to know where head ends.
    int next_block_index = (move_to_block_index + 1) % blocks_on_new_track;

    // updating position as if the block was read and head was at its end,
    // which means that head ends at the begin of the next block
    update_positions(
            calculate_begin_rotation_of_block(next_block_index, blocks_on_new_track),
            move_to_track);
    m_current_address = a_move_to_address + std::max(0, next_block_index - move_to_block_index);

    // time required to read the block
    return move_and_read_block_time;
}

double Hard_Drive::calculate_time_to_move_and_read_new_block(int a_move_to_address) const {
    std::tuple<int, int, int> new_pos = m_disk_plates_set.read_address(a_move_to_address);
    int move_to_track = std::get<1>(new_pos);
    int move_to_block_index = std::get<2>(new_pos);
    int blocks_on_block_track = m_disk_plates_set.get_number_of_blocks_on_track(move_to_track);
    return calculate_time_to_move_and_read_new_block(
            calculate_begin_rotation_of_block(move_to_block_index, blocks_on_block_track),
            move_to_track,
            blocks_on_block_track);
}

void Hard_Drive::update_positions(double a_new_rotation, int a_new_track) {
    m_rotation = a_new_rotation;
    m_head_track = a_new_track;
}

double Hard_Drive::calculate_begin_rotation_of_block(int a_block_index, int a_blocks_on_block_track) const {
    // equals = block_index from [0, n-1] * degrees per one block on particular track
    double res = a_block_index * (360.0 / a_blocks_on_block_track);
    // reducing to [0, 360)
    res = res - 360 * ((int) (res / 360));
    return res;
}

double Hard_Drive::calculate_time_to_read_block_on_track(int a_blocks_on_block_track) const {
    return m_t2 / a_blocks_on_block_track;

}

double Hard_Drive::calculate_time_to_move_and_read_new_block(double a_begin_rotation_of_block, int a_new_track,
                                                             int a_blocks_on_block_track) const {
    double time_to_move_to_begin_of_block = calculate_time_to_move_to_begin_of_the_block(a_begin_rotation_of_block,
                                                                                         a_new_track,
                                                                                         a_blocks_on_block_track);
    double block_read_time = calculate_time_to_read_block_on_track(a_blocks_on_block_track);
    return time_to_move_to_begin_of_block + block_read_time;

}

double Hard_Drive::calculate_time_to_move_to_begin_of_the_block(double a_new_rotation, int a_new_track,
                                                                int a_blocks_on_block_track) const {
    // calculating time required to move the head to other track
    double track_move_time = std::abs(a_new_track - m_head_track) * m_t1;
    // case: head needs to be moved to other track
    if (track_move_time != 0) {
        // time required to move head over the right track + time required to read the block
        return track_move_time;
    }

    // case: head is already in the right place
    if (std::abs(a_new_rotation - m_rotation) <= 0) {
        return 0;
    }

    // first time required per one degree
    double disk_rotation_time = (m_t2 / 360);
    // calculating degrees necessary to rotate
    if (a_new_rotation - m_rotation <= 0) {
        disk_rotation_time *= (360 - m_rotation + a_new_rotation);
    } else {
        disk_rotation_time *= (a_new_rotation - m_rotation);
    }

    // case: head is on the right track but the plate needs to be rotated
    if (disk_rotation_time >= 0) {
        // time required to rotate the plate so the head be placed at the beginning of the block + time required to read the block
        return disk_rotation_time;
    }
    return -1;
}