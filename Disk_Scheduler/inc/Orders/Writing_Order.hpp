//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_WRITING_ORDER_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_WRITING_ORDER_HPP
#include "Order.hpp"

class Hard_Drive;

class Writing_Order : public Order{
public:
    explicit Writing_Order(int a_block_address, int a_data = 0) : Order(a_block_address, a_data){}
    void process_order(Hard_Drive& a_hd) override;
};
#endif //HARD_DRIVE_ACCESS_ALGORITHMS_WRITING_ORDER_HPP
