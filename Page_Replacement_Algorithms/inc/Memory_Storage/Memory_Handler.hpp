//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_MEMORY_HANDLER_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_MEMORY_HANDLER_HPP
#include <queue>
#include <memory>

#include "Segment_Table.hpp"
#include "Order.hpp"

class RAM;
class Hard_Drive;
class Memory_Handler {
public:
    Memory_Handler(const std::string& a_algorithm, RAM* a_ram, Hard_Drive* a_hdd);
    std::unique_ptr<Page>& get_page(int a_segment_ID, int a_data_offset);
    int get_page_error() const;
    void add_order(std::unique_ptr<Order>& a_order);
    std::unique_ptr<Order> process_order();
private:
    [[maybe_unused]] Hard_Drive& m_hdd;
    RAM& m_ram;
    std::deque<std::unique_ptr<Order>> m_orders;
    Segment_Table m_segment_table;
};

#endif //PAGE_REPLACEMENT_ALGORITHMS_MEMORY_HANDLER_HPP
