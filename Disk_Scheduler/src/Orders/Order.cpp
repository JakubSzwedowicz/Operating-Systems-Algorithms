//
// Created by jakub on 06.04.2021.
//

#include "Order.hpp"
#include <stdexcept>

Order::Order(int a_block_address, int a_data) {
//    if (a_block_address < 0 || a_processing_length <= 0) {
//        throw std::invalid_argument(
//                "Illegal arguments passed!"
//                "\n\tblock address = "
//                + std::to_string(a_block_address)
//                        .append("\n\tprocessing length = ")
//                + std::to_string(a_processing_length));
//    }
    if (a_block_address < 0) {
        throw std::invalid_argument(
                "Order::Order(int, int):\nIllegal arguments passed!"
                "\n\tblock address = "
                + std::to_string(a_block_address));
    }
    m_block_address = a_block_address;
    m_data = a_data;
}

