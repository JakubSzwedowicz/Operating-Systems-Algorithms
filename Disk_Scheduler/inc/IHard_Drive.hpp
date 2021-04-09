//
// Created by jakub on 08.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_IHARD_DRIVE_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_IHARD_DRIVE_HPP

#include "IAlgorithm.hpp"
#include "Order.hpp"

#include <memory>

class Hard_Drive;
//class Order;

class IHard_Drive {
private:
    Hard_Drive& m_hard_drive;
    std::unique_ptr<IAlgorithm> m_algorithm;
    std::unique_ptr<std::priority_queue<std::unique_ptr<Order>, std::vector<std::unique_ptr<Order>>, std::function<bool(
            const std::unique_ptr<Order>&, const std::unique_ptr<Order>&)>>> m_priority_queue;

public:
    IHard_Drive(const std::string& a_algorithm, Hard_Drive& a_hard_drive);

    virtual ~IHard_Drive() {};

    void add_order(std::unique_ptr<Order>&& a_order) {
        m_algorithm->add_process_to_queue(std::move(a_order));
    };

    auto& get_queue() {
        return m_priority_queue;
    }

    std::unique_ptr<Order> process_order() {
        return m_algorithm->process_queue();
    }

    double get_working_time() {
        return m_algorithm->get_working_time();
    }

    double get_previous_operation_time() {
        return m_algorithm->get_previous_operation_time();
    }

    bool is_empty() const {
        return m_priority_queue->empty();
    }

private:
    void build_priority_queue();
};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_IHARD_DRIVE_HPP
