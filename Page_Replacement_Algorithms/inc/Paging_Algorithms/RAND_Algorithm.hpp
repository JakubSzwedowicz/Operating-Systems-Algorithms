//
// Author: JakubSzwedowicz
// Date: 30.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_RAND_ALGORITHM_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_RAND_ALGORITHM_HPP
#include <random>

#include "IAlgorithm.hpp"
#include "Order.hpp"
#include "Page_Info.hpp"

class Hard_Drive;

class RAND_Algorithm : public IAlgorithm{
public:
    RAND_Algorithm(std::vector<Page_Info*>* a_pages_info, Hard_Drive* a_hdd, RAM* a_ram, std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table);
private:
    std::unique_ptr<Page>* get_page_to_remove_from_RAM() override;
    std::random_device m_dev;
    std::mt19937 m_rng;
    std::uniform_int_distribution<std::mt19937::result_type> m_dist; // distribution in range [1, 6]
};

#endif //PAGE_REPLACEMENT_ALGORITHMS_RAND_ALGORITHM_HPP
