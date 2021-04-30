//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_IALGORITHM_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_IALGORITHM_HPP

#include <vector>
#include <memory>
#include <tuple>
#include <queue>

#include "Page.hpp"
#include "Order.hpp"


class Hard_Drive;

class RAM;

class Segment_Table;

class Segment_Table;

class IAlgorithm {
public:
    IAlgorithm(std::vector<Page_Info*>* m_pages_info, Hard_Drive* a_hdd, RAM* a_ram,
               std::deque<std::unique_ptr<Order>>& a_orders, Segment_Table& a_segment_table);

    int load_page_into_RAM(int a_page_ID);

    virtual int get_data_address(int a_segment_ID, int a_offset);

    virtual ~IAlgorithm() = default;

    int get_page_errors() const;

protected:
    RAM& m_ram;
    Hard_Drive& m_hard_Drive;
    std::vector<Page_Info*>& m_pages_info;
    std::deque<std::unique_ptr<Order>>& m_orders;
    Segment_Table& m_segment_table;

    int get_page_index_from_ram(int a_segment_ID);

    virtual std::unique_ptr<Page>& swap_with_ram(int a_page_ID);

    std::unique_ptr<Page>& get_page_from_hdd(int a_page_ID);

    virtual std::unique_ptr<Page>* get_page_to_remove_from_RAM() = 0;

    int m_page_errors;

};

#endif //PAGE_REPLACEMENT_ALGORITHMS_IALGORITHM_HPP
