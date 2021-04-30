//
// Author: JakubSzwedowicz
// Date: 29.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <memory>

#include "Write_Order.hpp"
#include "Page.hpp"


Write_Order::Write_Order(int a_segment, int a_offset, int a_data)
        : Order(a_segment, a_offset, a_data) {

}

void Write_Order::process_order(const std::unique_ptr<Page>& a_page) {
    // I don't know whether it should be Order taking under the consideration the offset or Memory Handler...
    a_page->set_data(m_data);
    m_processed = true;
}

