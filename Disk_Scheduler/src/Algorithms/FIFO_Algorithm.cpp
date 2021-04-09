//
// Created by jakub on 06.04.2021.
//


#include "FIFO_Algorithm.hpp"
#include "Order.hpp"

#include <queue>
#include <stdexcept>

FIFO_Algorithm::FIFO_Algorithm(Hard_Drive& a_hard_drive) : IAlgorithm(a_hard_drive) {
    m_comp = [&](const std::unique_ptr<Order>& o1, const std::unique_ptr<Order>& o2) -> bool {
        return false;
    };
}

std::unique_ptr<Order> FIFO_Algorithm::process_queue() {
    if (m_priority_queue->empty()) {
        throw std::runtime_error(
                "FIFO_Algorithm::process_queue():\nThere are no more orders to process!");
    }
    return IAlgorithm::process_queue();
}
