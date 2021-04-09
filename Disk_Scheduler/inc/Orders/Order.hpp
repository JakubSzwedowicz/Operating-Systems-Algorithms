//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_ORDER_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_ORDER_HPP

#include <memory>

class Hard_Drive;

class Order {
protected:
    int m_block_address;
    int m_data;
public:
    Order(int a_block_address,int a_data = 0);

    virtual ~Order() {}

    virtual void process_order(Hard_Drive& a_hd) = 0;

    int get_data() const {
        return m_data;
    }

    int get_block_address() const {
        return m_block_address;
    }
};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_ORDER_HPP
