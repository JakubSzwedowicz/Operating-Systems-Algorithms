//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_LRU_EST_ALGORITHM_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_LRU_EST_ALGORITHM_HPP

#include <map>

#include "IAlgorithm.hpp"

class LRU_Est_Algorithm : public IAlgorithm {
public:
    LRU_Est_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd, RAM* a_ram,
                      std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table);

private:
    std::unique_ptr<Page>* get_page_to_remove_from_RAM() override;

    void remove_excess();

    void gather_excess(std::map<int, int>& a_gathered_excess);

public:
    int get_data_address(int a_segment_ID, int a_offset) override;

    [[maybe_unused]] int get_ID_to_remove();

private:
    void remove_occurences(int a_segment_ID);

    void remove_element_from_memory(int a_segment_ID);

    int get_min();

    void add_next_ID(int a_next_ID);

    const int m_max_memory_size = 100;
    std::deque<int> m_ID_order;
    std::map<int, int> m_ID_counter;
    int m_ID_to_remove;
    int m_ID_to_load;
};

#endif //PAGE_REPLACEMENT_ALGORITHMS_LRU_EST_ALGORITHM_HPP
