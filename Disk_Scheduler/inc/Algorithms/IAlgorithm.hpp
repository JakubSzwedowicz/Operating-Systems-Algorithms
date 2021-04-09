//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_IALGORITHM_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_IALGORITHM_HPP
#pragma once

#include <queue>
#include <tuple>
#include <memory>
#include <functional>

class Order;
class Hard_Drive;

class IAlgorithm{
protected:
    Hard_Drive& m_hard_drive;
    std::function<bool(const std::unique_ptr<Order>& ptr, const std::unique_ptr<Order>&)> m_comp;
    std::priority_queue<std::unique_ptr<Order>, std::vector<std::unique_ptr<Order>>, decltype(m_comp)>* m_priority_queue;
    double m_working_time;
    double m_previous_operation_time;
    std::tuple<double, double, double> m_hard_drive_time;
public:
    explicit IAlgorithm(Hard_Drive& a_hard_drive);

    virtual ~IAlgorithm() = default;

    void add_process_to_queue(std::unique_ptr<Order>&& a_order) {
        m_priority_queue->push(std::move(a_order));
    }

    auto& get_comp(){
        return m_comp;
    }
    void link_queue(std::priority_queue<std::unique_ptr<Order>, std::vector<std::unique_ptr<Order>>, decltype(m_comp)>* a_queue){
        m_priority_queue = a_queue;
    }

    virtual std::unique_ptr<Order> process_queue();

    double get_previous_operation_time() const {
        return m_previous_operation_time;
    }

    double get_working_time() const {
        return m_working_time;
    }
};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_IALGORITHM_HPP
