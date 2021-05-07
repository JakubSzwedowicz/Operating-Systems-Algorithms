//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <string>
#include <random>
#include <iostream>

#include "Operating_System.hpp"
#include "Read_Order.hpp"
#include "Write_Order.hpp"

Operating_System::Operating_System(const std::string& a_algorithm_name, int a_frame_size, int a_ram_frames_number,
                                   int a_hdd_pages_number)
        : m_ram(a_frame_size, a_ram_frames_number)
        , m_hard_drive(a_ram_frames_number, a_frame_size, a_hdd_pages_number)
        , m_memory_handler(a_algorithm_name, &m_ram, &m_hard_drive) {
}

void Operating_System::test_class() {
    int FIFO = 0;
    int OPT = 0;
    int LRU = 0;
    int LRU_Est = 0;
    int RAND = 0;
    double chance = 1;
    int orders_amount = 1000;
    const int ram_frames_number = 50;
    const int hdd_pages_number = 250;
    const int frame_size = 4;
    const int repetitions = 100;
    for (int i = 0; i < repetitions; i++) {
        {
            Operating_System os("FIFO", frame_size, ram_frames_number, hdd_pages_number);
            os.run_simulation(orders_amount, chance);
            FIFO += os.m_memory_handler.get_page_error();
        }
        {
            Operating_System os("OPT", frame_size, ram_frames_number, hdd_pages_number);
            os.run_simulation(orders_amount, chance);
            OPT += os.m_memory_handler.get_page_error();
        }
        {
            Operating_System os("LRU", frame_size, ram_frames_number, hdd_pages_number);
            os.run_simulation(orders_amount, chance);
            LRU += os.m_memory_handler.get_page_error();
        }
        {
            Operating_System os("LRU_Est", frame_size, ram_frames_number, hdd_pages_number);
            os.run_simulation(orders_amount, chance);
            LRU_Est += os.m_memory_handler.get_page_error();
        }
        {
            Operating_System os("RAND", frame_size, ram_frames_number, hdd_pages_number);
            os.run_simulation(orders_amount, chance);
            RAND += os.m_memory_handler.get_page_error();
        }
    }
    std::cout << "FIFO: " << FIFO << std::endl;
    std::cout << "OPT: " << OPT << std::endl;
    std::cout << "LRU: " << LRU << std::endl;
    std::cout << "LRU_Est: " << LRU_Est << std::endl;
    std::cout << "RAND: " << RAND << std::endl;

}

void Operating_System::process_order(std::unique_ptr<Order>& a_order) {
    a_order->process_order(m_memory_handler.get_page(a_order->get_segment(), a_order->get_offset()));
}

void Operating_System::run_simulation(int a_amount, double a_jump_chance) {
    static std::uniform_real_distribution<double> chance_for_new(0, 100);
    generate_orders(a_amount, a_jump_chance);
    while (m_memory_handler.process_order()) {

    }
}

void Operating_System::generate_orders(int a_amount, double a_jump_chance) {
    static std::random_device rd;
    static std::default_random_engine generator(rd());
    static std::uniform_real_distribution<double> distribution_double(0, 100);
    static std::uniform_int_distribution<int> segment_range(-2, 2);
    static std::uniform_int_distribution<int> data_range(-1000, 1000);
    static std::uniform_int_distribution<int> offset_range(0, m_ram.get_frame_size() - 1);
    static auto random_segment = [] { return segment_range(generator); };
    static auto random_data = [] { return data_range(generator); };
    static auto random_offset = [] { return offset_range(generator); };

    static auto random_double = [] { return distribution_double(generator); };

    static int begin_segment = m_ram.get_frames_number() / 2;
    for (int i = 0; i < a_amount; i++) {
        double read_order = random_double();
        std::unique_ptr<Order> order;
        if (read_order < 30) {
            order = std::make_unique<Read_Order>(begin_segment, random_offset());
        } else {
            order = std::make_unique<Write_Order>(begin_segment, random_offset(), random_data());
        }
        m_memory_handler.add_order(order);
        if (random_double() < a_jump_chance) {
            begin_segment *= 2;
        } else {
            begin_segment += random_segment();
        }
        if (begin_segment < 0 || begin_segment >= m_ram.get_frames_number() + m_hard_drive.get_frames_number()) {
            begin_segment = (m_ram.get_frames_number() + m_hard_drive.get_frames_number()) / 2;
        }
    }
}