//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_FIFO_ALGORITHM_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_FIFO_ALGORITHM_HPP
#pragma once

#include "IAlgorithm.hpp"

class Order;

class FIFO_Algorithm : public IAlgorithm {
public:
    explicit FIFO_Algorithm(Hard_Drive& a_hard_drive);

    std::unique_ptr<Order> process_queue() override;
};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_FIFO_ALGORITHM_HPP
