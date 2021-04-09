//
// Created by jakub on 06.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_OPERATING_SYSTEM_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_OPERATING_SYSTEM_HPP
#pragma once

#include "IHard_Drive.hpp"
#include <queue>


class Order;

class Operating_System {
private:
    std::unique_ptr<IHard_Drive> m_hard_drive;
public:
    Operating_System(const std::string& a_algorithm, double a_t1, double a_t2, int a_number_of_plates,
                     int a_number_of_blocks_per_plate, int a_size_of_block);

    std::unique_ptr<Order> process_one();

    double get_previous_operation_time() const;

    double get_whole_working_time() const;

    void add_order(std::unique_ptr<Order>&& a_order);

    void load_orders_from_file(const std::string& a_file);

    double run();

    double run_simulation(double a_chance);

    static void test_class();

private:

};

#endif //HARD_DRIVE_ACCESS_ALGORITHMS_OPERATING_SYSTEM_HPP
