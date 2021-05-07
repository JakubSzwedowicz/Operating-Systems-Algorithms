//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <queue>
#include <limits>
#include <memory>

#include "IAlgorithm.hpp"
#include "RAM.hpp"
#include "Hard_Drive.hpp"
#include "Order.hpp"
#include "Segment_Table.hpp"

IAlgorithm::IAlgorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd, RAM* a_ram,
                       std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table)
        : m_ram(*a_ram), m_hard_Drive(*a_hdd), m_pages_info(*a_pages_info), m_orders(a_orders), m_segment_table(
        a_segment_table), m_page_errors(
        0) {
}

int IAlgorithm::get_page_errors() const {
    return m_page_errors;
}

int IAlgorithm::load_page_into_RAM(int a_page_ID) {
    m_page_errors++;
    auto& ret = swap_with_ram(a_page_ID);
    return ret->get_page_info().m_location.m_page_index;
}

int IAlgorithm::get_data_address(int a_segment_ID, int a_offset) {
    if (!m_segment_table.check_is_page_loaded(a_segment_ID)) {
        load_page_into_RAM(a_segment_ID);
    }
//    m_pages_info[a_segment_ID]->m_time_last_called = 0;
    int page_index = get_page_index_from_ram(a_segment_ID);
    return page_index * m_ram.get_frame_size() + a_offset;
}

int IAlgorithm::get_page_index_from_ram(int a_segment_ID) {
    return m_pages_info[a_segment_ID]->m_location.m_page_index;
}

std::unique_ptr<Page>& IAlgorithm::swap_with_ram(int a_page_ID) {
    std::unique_ptr<Page>& page_to_load = get_page_from_hdd(a_page_ID);

    std::unique_ptr<Page>* page_to_unload = m_ram.get_free_ptr();
    if (!page_to_unload) {
        page_to_unload = get_page_to_remove_from_RAM();
    }
    m_ram.swap_pages(page_to_load, *page_to_unload);

    return *page_to_unload;
}

std::unique_ptr<Page>& IAlgorithm::get_page_from_hdd(int a_page_ID){
    int hdd_index = m_pages_info[a_page_ID]->m_location.m_page_index;
    std::unique_ptr<Page>& page_to_load = m_hard_Drive.get_page(hdd_index);
    return page_to_load;
}

