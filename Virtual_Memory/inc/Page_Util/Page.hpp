//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_PAGE_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_PAGE_HPP

#include "Page_Info.hpp"

class Segment_Table;
class Page{
private:
    Page_Info m_page_info;
    int m_size;
    int m_data;
    [[nodiscard]] Page_Info* get_page_info_ptr();
public:
    Page(int a_page_ID, int a_size, bool a_loaded, int a_page_index);
    [[nodiscard]] Page_Info& get_page_info();   // bad design
    [[nodiscard]] [[maybe_unused]] int get_data(int a_offset) const;
    [[nodiscard]] int get_size() const;
    [[nodiscard]] bool is_empty() const;
    void erase_memory();
    void set_data(int a_data, int a_length);
    void set_data(int a_data);
    void set_page_info(bool a_write, bool a_read, bool a_code, bool a_data);
    void swap_locations_with_page(Page& a_page);
    friend Segment_Table;
};
#endif //PAGE_REPLACEMENT_ALGORITHMS_PAGE_HPP
