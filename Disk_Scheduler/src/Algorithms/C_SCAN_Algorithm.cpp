//
// Created by jakub on 09.04.2021.
//

#include "C_SCAN_Algorithm.hpp"
#include "Order.hpp"
#include <stdexcept>

C_SCAN_Algorithm::C_SCAN_Algorithm(Hard_Drive& a_hard_drive) : IAlgorithm(a_hard_drive) {
    m_comp = [&](const std::unique_ptr<Order>& a_first, const std::unique_ptr<Order>& a_second) -> bool {
        return a_first->get_block_address() - a_second->get_block_address() > 0;
    };
}

std::unique_ptr<Order> C_SCAN_Algorithm::process_queue() {
    if (m_priority_queue->empty()) {
        throw std::runtime_error(
                "C_SCAN::process_queue():\nThere are no more orders to process!");
    }
    std::unique_ptr<Order> order = IAlgorithm::process_queue();
    while ((!m_priority_queue->empty()) && m_priority_queue->top()->get_block_address() == order->get_block_address()) {
        // remove same orders from the top of the queue. If it were needed process_queue() might return std::vector<std::unique_ptr<Order>> in the future
        m_priority_queue->pop();
    }
    return order;
}
