//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#include "RAND_Algorithm.hpp"
#include "RAM.hpp"

RAND_Algorithm::RAND_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd,
                               RAM* a_ram, std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table)
        : IAlgorithm(a_pages_info, a_hdd, a_ram, a_orders, a_segment_table), m_rng(m_dev()), m_dist(0, m_ram.get_frames_number() - 1) {
}

std::unique_ptr<Page>* RAND_Algorithm::get_page_to_remove_from_RAM() {
    int ram_index = m_dist(m_rng);
    std::unique_ptr<Page>* ret = &m_ram.get_page(ram_index);
    return ret;
};