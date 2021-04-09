//
// Created by jakub on 08.04.2021.
//

#include "SSTF_Algorithm.hpp"

#include "Order.hpp"
#include <memory>

SSTF_Algorithm::SSTF_Algorithm(Hard_Drive& a_hard_drive)
: IAlgorithm(a_hard_drive)
{

//    }, m_blocks_on_tracks(m_hard_drive.get_number_of_blocks_on_tracks()), m_number_of_plates(m_hard_drive.get_number_of_plates()) {
    m_comp = [&](const std::unique_ptr<Order>& o1, const std::unique_ptr<Order>& o2) -> bool {
        double time1 = m_hard_drive.calculate_time_to_move_and_read_new_block(o1->get_block_address());
        double time2 = m_hard_drive.calculate_time_to_move_and_read_new_block(o2->get_block_address());
        return time1 > time2;
    };
}

std::unique_ptr<Order> SSTF_Algorithm::process_queue() {
    if (m_priority_queue->empty()) {
        throw std::runtime_error(
                "SSTF_Algorithm::process_queue():\nThere are no more orders to process!");
    }
    std::unique_ptr<Order> order = IAlgorithm::process_queue();
    while ((!m_priority_queue->empty()) && m_priority_queue->top()->get_block_address() == order->get_block_address()) {
        // remove same orders from queue. If it was needed process_queue() might return std::vector<std::unique_ptr<Order>> in te future
        m_priority_queue->pop();
    }
    return order;
}

