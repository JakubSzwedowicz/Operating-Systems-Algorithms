//
// Created by jakub on 09.04.2021.
//

#include <Hard_Drive.hpp>
#include <SCAN_Algorithm.hpp>

SCAN_Algorithm::SCAN_Algorithm(Hard_Drive& aHardDrive) : IAlgorithm(aHardDrive) {
    m_comp = [&](const std::unique_ptr<Order>& a_first, const std::unique_ptr<Order>& a_second) -> bool {
        return a_first->get_block_address() - a_second->get_block_address() > 0;
    };
}


std::unique_ptr<Order> SCAN_Algorithm::process_queue() {
    if (m_priority_queue->empty()) {
        throw std::runtime_error(
                "SCAN::process_queue():\nThere are no more orders to process!");
    }
    int head_address = m_hard_drive.get_current_address();
    double time_head_to_the_end = 0;
    if (head_address > m_priority_queue->top()->get_block_address()) {
        time_head_to_the_end = m_hard_drive.move_to_new_pos(m_hard_drive.get_number_of_blocks_on_tracks() - 1);
        time_head_to_the_end += m_hard_drive.move_to_new_pos(0);
    }
    std::unique_ptr<Order> order = IAlgorithm::process_queue();
    while ((!m_priority_queue->empty()) && m_priority_queue->top()->get_block_address() == order->get_block_address()) {
        // remove same orders from the top of the queue. If it were needed process_queue() might return std::vector<std::unique_ptr<Order>> in the future
        m_priority_queue->pop();
    }
    m_previous_operation_time += time_head_to_the_end;
    m_working_time += time_head_to_the_end;
    return order;
}