//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#include <limits>
#include <queue>

#include "FIFO_Algorithm.hpp"
#include "RAM.hpp"
#include "Order.hpp"

FIFO_Algorithm::FIFO_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd,
                               RAM* a_ram, std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table)
        : IAlgorithm(a_pages_info, a_hdd, a_ram, a_orders, a_segment_table) {
}

std::unique_ptr<Page>* FIFO_Algorithm::get_page_to_remove_from_RAM() {
    int max_time = std::numeric_limits<int>::min();
    std::unique_ptr<Page>* ret;
    int ram_index = m_ram.get_frames_number();
    for(auto ram_it = m_pages_info.cbegin(); ram_it != m_pages_info.cbegin() + ram_index; ++ram_it){
        int time = (*ram_it)->m_time_in_memory;
        if(time > max_time){
            max_time = time;
            ret = &m_ram.get_page((int)std::distance(m_pages_info.cbegin(), ram_it));
        }
    }
    return ret;
};
