//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_SEGMENT_TABLE_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_SEGMENT_TABLE_HPP

#include "IAlgorithm.hpp"
#include "Order.hpp"

class Hard_Drive;

class RAM;

class Segment_Table {
public:
    Segment_Table(const std::string& a_algorithm, Hard_Drive* a_hdd, RAM* a_ram,
                  std::deque<std::unique_ptr<Order>>& a_orders);

    int get_data_address(int a_segment_ID, int a_data_offset);

    int get_page_error() const;

    void set_data_segment(int a_segment_ID, int a_data);

    bool check_is_page_loaded(int a_page_ID) const;

private:
    void increment_time() const;

    [[maybe_unused]] const int m_segments_number;
    [[maybe_unused]] const int m_pages_size;
    const int m_ram_frames;
    const int m_hdd_pages;
    RAM& m_ram;
    std::unique_ptr<IAlgorithm> m_algorithm;
    std::vector<Page_Info*> m_pages_info;
    [[maybe_unused]] std::deque<std::unique_ptr<Order>>& m_orders;
};

#endif //PAGE_REPLACEMENT_ALGORITHMS_SEGMENT_TABLE_HPP
