//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_OPERATING_SYSTEM_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_OPERATING_SYSTEM_HPP

#include "Memory_Handler.hpp"
#include "RAM.hpp"
#include "Hard_Drive.hpp"
#include "Order.hpp"

class Operating_System {
public:
    Operating_System(const std::string& a_algorithm_name, int a_frame_size, int a_ram_frames_number, int a_hdd_pages_number);
    void process_order(std::unique_ptr<Order>& a_order);
    static void test_class();
private:
    void run_simulation(int a_amount, double a_jump_chance);
    void generate_orders(int a_amount, double a_jump_chance);
    RAM m_ram;
    Hard_Drive m_hard_drive;
    Memory_Handler m_memory_handler;
};

#endif //PAGE_REPLACEMENT_ALGORITHMS_OPERATING_SYSTEM_HPP
