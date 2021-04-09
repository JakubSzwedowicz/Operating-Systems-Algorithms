//
// Created by jakub on 06.04.2021.
//

#include "Operating_System.hpp"
#include "Hard_Drive.hpp"
#include "IHard_Drive.hpp"
#include "IAlgorithm.hpp"
#include "Order.hpp"
#include "Writing_Order.hpp"
#include "Reading_Order.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <random>

Operating_System::Operating_System(const std::string& a_algorithm, double a_t1, double a_t2, int a_number_of_plates,
                                   int a_number_of_blocks_per_plate, int a_size_of_block)
        : m_hard_drive(
        std::make_unique<Hard_Drive>(a_algorithm, a_t1, a_t2, a_number_of_plates, a_number_of_blocks_per_plate,
                                     a_size_of_block)) {
}

void Operating_System::add_order(std::unique_ptr<Order>&& a_order) {
    m_hard_drive->add_order(std::move(a_order));
}

double Operating_System::get_whole_working_time() const {
    return m_hard_drive->get_working_time();
}

std::unique_ptr<Order> Operating_System::process_one() {
    std::unique_ptr<Order> order;
    if (!m_hard_drive->is_empty()) {
        order = m_hard_drive->process_order();
//        std::cout << "operation took: " << m_hard_drive->get_previous_operation_time() << " time units" << std::endl;
//        std::cout << "whole working time equals: " << m_hard_drive->get_working_time() << " time units" << std::endl;
    }
    return order;
}

double Operating_System::get_previous_operation_time() const {
    return m_hard_drive->get_previous_operation_time();
}

double Operating_System::run() {
//    int i = 0;
    while (!m_hard_drive->is_empty()) {
        std::unique_ptr<Order> order = m_hard_drive->process_order();
//        std::cout << order->get_block_address() << std::endl;
//        std::cout << "Iteration " << (i++) << ":" << std::endl;
//        std::cout << "operation took: " << m_hard_drive->get_previous_operation_time() << " time units" << std::endl;
//        std::cout << "whole working time equals: " << m_hard_drive->get_working_time() << " time units" << std::endl;
    }
    return m_hard_drive->get_working_time();
}

double Operating_System::run_simulation(double a_chance) {
    if(a_chance < 0 || a_chance > 100){
        throw std::invalid_argument("Operating_System::run_simulation(double):\nGiven chance percent is illegal!\nchance = " + std::to_string(a_chance));
    }
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution_double(0, 100);
    std::uniform_int_distribution<int> distribution_int(0, 44);
    auto random_double = [&distribution_double, &generator] { return distribution_double(generator); };
    auto random_int = [&distribution_int, &generator] { return distribution_int(generator); };

    while(process_one()){
        double chance = random_double();
        if(chance < a_chance){
            add_order(std::make_unique<Reading_Order>(random_int()));
        }
    }
    return m_hard_drive->get_working_time();
}
void Operating_System::load_orders_from_file(const std::string& a_file) {
    std::ifstream file(a_file);
    if (file.is_open()) {
        char type;
        int address;
        int data;
        while (file >> type) {
            file >> address;
            if (type == 'W') {
                file >> data;
                add_order(std::make_unique<Writing_Order>(address, data));
            } else {
                add_order(std::make_unique<Reading_Order>(address));
            }
        }
    }
    file.close();
}

void Operating_System::test_class(){
    double fifo = 0;
    double sstf = 0;
    double scan = 0;
    double cscan = 0;
    double chance = 20;
    for (int i = 0; i < 10; i++) {

        {
            Operating_System os("FIFO", 1000, 1, 3, 15, 512);
            os.load_orders_from_file("Prepared_Orders.txt");
            fifo += os.run_simulation(chance);
        }
        {
            Operating_System os("SSTF", 1000, 1, 3, 15, 512);
            os.load_orders_from_file("Prepared_Orders.txt");
            sstf += os.run_simulation(chance);
        }
        {
            Operating_System os("SCAN", 1000, 1, 3, 15, 512);
            os.load_orders_from_file("Prepared_Orders.txt");
            scan += os.run_simulation(chance);
        }
        {
            Operating_System os("C_SCAN", 1000, 1, 3, 15, 512);
            os.load_orders_from_file("Prepared_Orders.txt");
            cscan += os.run_simulation(chance);
        }
    }
    std::cout << "FIFO: " << fifo << std::endl;
    std::cout << "SSTF: " << sstf << std::endl;
    std::cout << "SCAN: " << scan << std::endl;
    std::cout << "CSCAN: " << cscan << std::endl;
//    os.add_order(std::make_unique<Writing_Order>(Writing_Order(1, 1)));
//    os.add_order(std::make_unique<Writing_Order>(Writing_Order(18, 1)));
//    os.add_order(std::make_unique<Writing_Order>(Writing_Order(3, 1)));
//    os.add_order(std::make_unique<Reading_Order>(Reading_Order(6)));
//    os.add_order(std::make_unique<Reading_Order>(Reading_Order(1)));

//    os.add_order(std::make_unique<Writing_Order>(Writing_Order(1, 1)));
//    os.add_order(std::make_unique<Writing_Order>(Writing_Order(18, 1)));
//    os.add_order(std::make_unique<Writing_Order>(Writing_Order(3, 1)));
//    os.add_order(std::make_unique<Reading_Order>(Reading_Order(19)));
//    os.add_order(std::make_unique<Reading_Order>(Reading_Order(6)));
//    os.add_order(std::make_unique<Reading_Order>(Reading_Order(13)));
//    os.add_order(std::make_unique<Reading_Order>(Reading_Order(1)));
//    os.add_order(std::make_unique<Reading_Order>(Reading_Order(15)));
//    os.add_order(std::make_unique<Reading_Order>(Reading_Order(19)));
}
