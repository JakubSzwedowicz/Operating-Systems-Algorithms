//
// Created by jakub on 06.04.2021.
//

#include "Writing_Order.hpp"
#include "Hard_Drive.hpp"

void Writing_Order::process_order(Hard_Drive& a_hd) {
    a_hd.write_block(m_block_address, m_data);
}
