//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_LRU_ALGORITHM_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_LRU_ALGORITHM_HPP
#include "IAlgorithm.hpp"

class LRU_Algorithm : public IAlgorithm{
public:
    LRU_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd, RAM* a_ram, std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table);
private:
    std::unique_ptr<Page>* get_page_to_remove_from_RAM() override;
};
#endif //PAGE_REPLACEMENT_ALGORITHMS_LRU_ALGORITHM_HPP
