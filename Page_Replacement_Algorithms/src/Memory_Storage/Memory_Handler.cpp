//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <string>

#include "Memory_Handler.hpp"
#include "RAM.hpp"
#include "Hard_Drive.hpp"
#include "Order.hpp"

Memory_Handler::Memory_Handler(const std::string& a_algorithm, RAM* a_ram, Hard_Drive* a_hdd)
        : m_hdd(*a_hdd), m_ram(*a_ram), m_segment_table(a_algorithm, a_hdd, a_ram, m_orders) {
}

std::unique_ptr<Page>& Memory_Handler::get_page(int a_segment_ID, int a_data_offset) {
    int address = m_segment_table.get_data_address(a_segment_ID, a_data_offset);
    // Normally it would return the value straight from the RAM address
    // , but here (since it's OOP) it needs to decode it back to the page and ask for the right data
    int ram_index = address / m_ram.get_frame_size();
    return m_ram.get_page(ram_index);
}

int Memory_Handler::get_page_error() const {
    return m_segment_table.get_page_error();
}

void Memory_Handler::add_order(std::unique_ptr<Order>& a_order) {
    m_orders.push_back(std::move(a_order));
}

std::unique_ptr<Order> Memory_Handler::process_order() {
    if(m_orders.empty()){
        return nullptr;
    }
    std::unique_ptr<Order> ret = std::move(m_orders.front());
    m_orders.pop_front();
    std::unique_ptr<Page>& address = get_page(ret->get_segment(), ret->get_offset());
    ret->process_order(address);
    return ret;
}
