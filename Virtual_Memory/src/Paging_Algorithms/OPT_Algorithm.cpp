//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <limits>

#include "OPT_Algorithm.hpp"
#include "RAM.hpp"

OPT_Algorithm::OPT_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd,
                             RAM* a_ram, std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table)
        : IAlgorithm(a_pages_info, a_hdd, a_ram, a_orders, a_segment_table)
        , m_next_occurances(m_ram.get_frames_number(), std::numeric_limits<int>::max()) {
}

std::unique_ptr<Page>* OPT_Algorithm::get_page_to_remove_from_RAM() {
    int the_longest_time_unused = std::numeric_limits<int>::min();
    std::unique_ptr<Page>* ret;
    int ram_index = m_next_occurances.size();
    for (auto ram_it = m_next_occurances.cbegin(); ram_it != m_next_occurances.cbegin() + ram_index; ++ram_it) {
        int time_unused = (*ram_it);
        if (time_unused > the_longest_time_unused) {
            the_longest_time_unused = time_unused;
            ret = &m_ram.get_page((int) std::distance(m_next_occurances.cbegin(), ram_it));
        }
    }
    return ret;
}


int OPT_Algorithm::get_data_address(int a_segment_ID, int a_offset) {
    int address = IAlgorithm::get_data_address(a_segment_ID, a_offset);

    int segment_index_in_ram = m_pages_info[a_segment_ID]->m_location.m_page_index;
    m_next_occurances[segment_index_in_ram] = find_next_order_on_page(a_segment_ID);

    return address;
}

void OPT_Algorithm::decrement_time_till_use() {
    for (int & next_occurance : m_next_occurances) {
        next_occurance--;
    }
}

std::unique_ptr<Page>& OPT_Algorithm::swap_with_ram(int a_page_ID) {
    std::unique_ptr<Page>& loaded_page = IAlgorithm::swap_with_ram(a_page_ID);

    int ram_index = loaded_page->get_page_info().m_location.m_page_index;
    m_next_occurances[ram_index] = find_next_order_on_page(a_page_ID);

    return loaded_page;
}


int OPT_Algorithm::find_next_order_on_page(int a_page_ID) {
    for (auto it = m_orders.cbegin(); it != m_orders.cend(); ++it) {
        if ((*it)->get_segment() == a_page_ID) {
            return std::distance(m_orders.cbegin(), it);
        }
    }
    return std::numeric_limits<int>::max();
}
