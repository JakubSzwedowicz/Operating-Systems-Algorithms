//
// Author: JakubSzwedowicz
// Date: 29.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <memory>

#include "Read_Order.hpp"
#include "Page.hpp"

void Read_Order::process_order(const std::unique_ptr<Page>& a_page) {
    m_data = a_page->get_data(m_offset);
    m_processed = true;
}

Read_Order::Read_Order(int a_segment, int a_offset)
        : Order(a_segment, a_offset) {
}