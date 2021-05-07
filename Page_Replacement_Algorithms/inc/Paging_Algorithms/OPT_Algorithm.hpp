//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_OPT_ALGORITHM_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_OPT_ALGORITHM_HPP

#include "IAlgorithm.hpp"
#include "Order.hpp"

class OPT_Algorithm : public IAlgorithm {
public:
    OPT_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd, RAM* a_ram,
                  std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table);

    int get_data_address(int a_segment_ID, int a_offset) override;

private:
    std::unique_ptr<Page>* get_page_to_remove_from_RAM() override;

    std::unique_ptr<Page>& swap_with_ram(int a_page_ID) override;

private:
    void decrement_time_till_use();

    std::vector<int> m_next_occurances;

    int find_next_order_on_page(int a_page_ID);
};

#endif //PAGE_REPLACEMENT_ALGORITHMS_OPT_ALGORITHM_HPP
