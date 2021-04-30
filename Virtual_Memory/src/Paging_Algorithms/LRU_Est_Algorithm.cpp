//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#include <algorithm>
#include <stdexcept>
#include <iterator>

#include "LRU_Est_Algorithm.hpp"
#include "RAM.hpp"
#include "Segment_Table.hpp"

LRU_Est_Algorithm::LRU_Est_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd,
                                     RAM* a_ram, std::deque<std::unique_ptr<Order>>& a_orders,
                                     Segment_Table& a_segment_table)
        : IAlgorithm(a_pages_info, a_hdd, a_ram, a_orders, a_segment_table) {
}

std::unique_ptr<Page>* LRU_Est_Algorithm::get_page_to_remove_from_RAM() {
    int temp = get_min();
    return &m_ram.get_page(m_pages_info[temp]->m_location.m_page_index);
}

void LRU_Est_Algorithm::add_next_ID(int a_next_ID) {
    m_ID_order.push_back(a_next_ID);
    m_ID_counter[a_next_ID]++;
    if (m_ID_order.size() == m_max_memory_size) {
        remove_excess();
    }
};

void LRU_Est_Algorithm::remove_excess() {
    int bottom_ID = m_ID_order.front();
    try {
        // There is a possibility of removing segment before it gets naturally forgotten so despite its IDs still present
        // , the actual segment might have already been erased
        m_ID_counter.at(bottom_ID)--;
        if (m_ID_counter[bottom_ID] == 0) {
            remove_element_from_memory(bottom_ID);
        }
    } catch (const std::out_of_range& ex) {

    }
    m_ID_order.pop_front();
}

void LRU_Est_Algorithm::remove_occurences(int a_segment_ID) {
    m_ID_order.erase(std::remove(m_ID_order.begin(), m_ID_order.end(), a_segment_ID), m_ID_order.end());
}

void LRU_Est_Algorithm::remove_element_from_memory(int a_segment_ID) {
    m_ID_counter.erase(a_segment_ID);
}

int LRU_Est_Algorithm::get_min() {
    auto the_most_rare_ID = std::min_element(m_ID_counter.cbegin(), m_ID_counter.cend(),
                                             [&](const std::pair<int, int>& f,
                                                 const std::pair<int, int>& s) -> bool {
                                                 if(m_pages_info[f.first]->m_location.m_loaded_in_ram){
                                                     if(m_pages_info[s.first]->m_location.m_loaded_in_ram){
                                                         return f.second < s.second;
                                                     } else {
                                                         return true;
                                                     }
                                                 }
                                                 return false;
                                             });
    return the_most_rare_ID->first;
}

[[maybe_unused]] int LRU_Est_Algorithm::get_ID_to_remove() {
    return m_ID_to_remove;
}

int LRU_Est_Algorithm::get_data_address(int a_segment_ID, int a_offset) {
    add_next_ID(a_segment_ID);
    int address = IAlgorithm::get_data_address(a_segment_ID, a_offset);
    return address;
}
