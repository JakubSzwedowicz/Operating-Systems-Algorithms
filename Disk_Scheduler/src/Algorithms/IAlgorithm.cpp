//
// Created by jakub on 07.04.2021.
//

#include "IAlgorithm.hpp"
#include "Hard_Drive.hpp"
#include "Order.hpp"
#include <memory>
#include <iostream>


std::unique_ptr<Order> IAlgorithm::process_queue() {
    if (m_priority_queue->empty()) {
        throw std::runtime_error(
                "IAlgorithm::process_queue():\nThere are no more orders to process!");
    }
    // Evil casting. Comes from this weird fact that priority_queue::top() returns const T&
    std::unique_ptr<Order> order = std::move(const_cast<std::unique_ptr<Order>&>(m_priority_queue->top()));
    m_priority_queue->pop();
    int order_address = order->get_block_address();
    order->process_order(m_hard_drive);
    m_previous_operation_time = m_hard_drive.move_to_new_pos(order_address);
    m_working_time += m_previous_operation_time;
    return order;
}

IAlgorithm::IAlgorithm(Hard_Drive& a_hard_drive) : m_hard_drive(a_hard_drive), m_working_time(0)
        , m_previous_operation_time(0), m_hard_drive_time(
                a_hard_drive.get_times()) {
}
