//
// Created by jakub on 08.04.2021.
//

#include "IHard_Drive.hpp"
#include "IAlgorithm.hpp"
#include "FIFO_Algorithm.hpp"
#include "SSTF_Algorithm.hpp"
#include "SCAN_Algorithm.hpp"
#include "C_SCAN_Algorithm.hpp"

#include "Order.hpp"

#include <string>
#include <queue>
#include <memory>
#include <stdexcept>

IHard_Drive::IHard_Drive(const std::string& a_algorithm, Hard_Drive& a_hard_drive)
        : m_hard_drive(a_hard_drive) {
    if (a_algorithm == "FIFO" || a_algorithm == "FCFS") {
        m_algorithm = std::make_unique<FIFO_Algorithm>(m_hard_drive);
    } else if (a_algorithm == "SSTF") {
        m_algorithm = std::make_unique<SSTF_Algorithm>(m_hard_drive);
    } else if (a_algorithm == "SCAN") {
        m_algorithm = std::make_unique<SCAN_Algorithm>(m_hard_drive);
    } else if (a_algorithm == "C_SCAN") {
        m_algorithm = std::make_unique<C_SCAN_Algorithm>(m_hard_drive);
    } else if (a_algorithm == "EDF") {
        throw std::invalid_argument(
                "Hard_Drive::Hard_Drive(const std::string&, double, double, int, int, int):\nEDF algorithm not implemented yet!");
    } else if (a_algorithm == "FD_SCAN") {
        throw std::invalid_argument(
                "Hard_Drive::Hard_Drive(const std::string&, double, double, int, int, int):\nFD-SCAN algorithm not implemented yet!");
    } else {
        throw std::invalid_argument(std::string(
                "Hard_Drive::Hard_Drive(const std::string&, double, double, int, int, int):\nWrong algorithm was chosen!\n\talgorithm = ").append(
                a_algorithm));
    }
    build_priority_queue();
}

void IHard_Drive::build_priority_queue(){
    m_priority_queue = std::make_unique<std::priority_queue<std::unique_ptr<Order>, std::vector<std::unique_ptr<Order>>, std::function<bool(
            const std::unique_ptr<Order>&, const std::unique_ptr<Order>&)>>>(
            m_algorithm->get_comp());
    m_algorithm->link_queue(m_priority_queue.get());
}