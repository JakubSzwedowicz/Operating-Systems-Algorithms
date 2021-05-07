//
// Author: JakubSzwedowicz
// Date: 29.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_WRITE_ORDER_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_WRITE_ORDER_HPP
#include "Order.hpp"

class Write_Order : public Order {
public:
    ~Write_Order() override = default;
    Write_Order(int a_segment, int a_offset, int a_data);
    void process_order(const std::unique_ptr<Page>& a_page) override;

};
#endif //PAGE_REPLACEMENT_ALGORITHMS_WRITE_ORDER_HPP
