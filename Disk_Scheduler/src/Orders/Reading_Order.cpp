//
// Created by jakub on 06.04.2021.
//

#include "Reading_Order.hpp"
#include "Hard_Drive.hpp"

void Reading_Order::process_order(Hard_Drive& a_hd) {
    m_data = a_hd.read_block(m_block_address);
}
