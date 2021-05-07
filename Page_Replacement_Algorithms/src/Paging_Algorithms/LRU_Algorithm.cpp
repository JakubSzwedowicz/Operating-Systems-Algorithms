//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <limits>

#include "LRU_Algorithm.hpp"
#include "RAM.hpp"

LRU_Algorithm::LRU_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd,
                               RAM* a_ram, std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table)
        : IAlgorithm(a_pages_info, a_hdd, a_ram, a_orders, a_segment_table) {
}

std::unique_ptr<Page>* LRU_Algorithm::get_page_to_remove_from_RAM() {
    int max_time = std::numeric_limits<int>::min();
    std::unique_ptr<Page>* ret;
    int ram_index = m_ram.get_frames_number();
    for(int i = 0; i < ram_index; i++){
        std::unique_ptr<Page>* it = &m_ram.get_page(i);
        int time = (*it)->get_page_info().m_time_last_called;
        if(time > max_time){
            max_time = time;
            ret = it;
        }
    }
    return ret;
};