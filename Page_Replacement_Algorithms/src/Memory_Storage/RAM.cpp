//
// Created by JakubSzwedowicz on 26.04.2021.
//
#include <stdexcept>

#include "RAM.hpp"

RAM::RAM(int a_frame_size, int a_frame_number)
        : Memory_Container(0, a_frame_size, a_frame_number, true) {
    if (a_frame_size <= 0 || a_frame_size % 2 != 0 || a_frame_number <= 0) {
        throw std::invalid_argument("Ram::Ram(int, int)"
                                    "\n\tframe size = " + std::to_string(a_frame_size)
                                            .append("\n\tframes number = ") + std::to_string(a_frame_number));
    }
}