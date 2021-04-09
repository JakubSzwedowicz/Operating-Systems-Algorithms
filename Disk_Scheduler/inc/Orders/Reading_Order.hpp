//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_READING_ORDER_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_READING_ORDER_HPP

#include "Order.hpp"

class Hard_Drive;

class Reading_Order : public Order {
public:
    explicit Reading_Order(int a_block_address) : Reading_Order(a_block_address, 0) {}

    void process_order(Hard_Drive& a_hd) override;

private:
    explicit Reading_Order(int a_block_address, int a_data) : Order(a_block_address, a_data) {}
};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_READING_ORDER_HPP
