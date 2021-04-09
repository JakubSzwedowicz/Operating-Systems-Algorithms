//
// Created by jakub on 06.04.2021.
//
#include "Disk_Plate.hpp"
#include "Disk_Track.hpp"
#include <cmath>
#include <sstream>


Disk_Plate::Disk_Plate(int a_number_of_blocks, int a_size_of_blocks)
        : Disk_Plate(std::log2(a_number_of_blocks + 1),
                     (a_number_of_blocks + 1) / 2,
                     a_size_of_blocks) {

}

Disk_Plate::Disk_Plate(int a_number_of_tracks, int a_outer_number_of_blocks, int a_size_of_blocks) {
    if (a_number_of_tracks <= 0 || a_outer_number_of_blocks % 2 != 0 || a_size_of_blocks % 2 != 0 ||
        a_number_of_tracks != 1 + std::log2(a_outer_number_of_blocks)) {
        throw std::invalid_argument(std::string("Disk_Plate::Disk_Plate(int, int, int):\nGiven arguments are illegal!\n\t number of tracks = "
                                                + std::to_string(a_number_of_tracks)
                                                        .append("\n\touter number of blocks = ")
                                                + std::to_string(a_outer_number_of_blocks)
                                                        .append("\n\tsize of blocks = ")
                                                + std::to_string(a_size_of_blocks)));
    }
    m_number_of_tracks = a_number_of_tracks;
    m_size_of_blocks = a_size_of_blocks;
    m_outer_number_of_blocks = a_outer_number_of_blocks;
    m_disk_tracks.reserve(m_number_of_tracks);
    for (int i = 0; i < m_number_of_tracks; i++) {
        m_disk_tracks.push_back(Disk_Track(a_outer_number_of_blocks, m_size_of_blocks));
        a_outer_number_of_blocks /= 2;
    }
}

const Disk_Block& Disk_Plate::get_block(int a_track_index, int a_block_index) const {
    validate_track_and_block_indices(a_track_index, a_block_index);
    return m_disk_tracks[a_track_index].get_disk_block(a_block_index);
}

void Disk_Plate::set_block(int a_track_index, int a_block_index, int a_data) {
    validate_track_and_block_indices(a_track_index, a_block_index);
    m_disk_tracks[a_track_index].set_disk_block(a_block_index, a_data);
}

void Disk_Plate::validate_track_and_block_indices(int a_track_index, int a_block_index) const{
    if (a_track_index < 0 || a_track_index >= m_number_of_tracks || a_block_index < 0 ||
        a_block_index >= m_disk_tracks[a_track_index].get_number_of_blocks()) {
        std::ostringstream output;
        output << "Disk_Plate::validate_track_and_block_indices(int, int):\nGiven parameters are wrong!";
        output << "\n\ttrack index = " << a_track_index;
        output << "\n\tnumber of tracks = " << m_number_of_tracks;
        output << "\n\tblock index = " << a_block_index;
        if (a_track_index < m_number_of_tracks) {
            output << "\n\tmax block on this track = " << m_disk_tracks[a_track_index].get_number_of_blocks();
        }
        throw std::invalid_argument(output.str());
    }
}
