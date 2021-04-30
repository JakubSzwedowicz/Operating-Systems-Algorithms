//
// Author: JakubSzwedowicz
// Date: 29.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_READ_ORDER_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_READ_ORDER_HPP
#include "Order.hpp"

class Read_Order : public Order{
public:

    ~Read_Order() override = default;
    Read_Order(int a_segment, int a_offset);
    void process_order(const std::unique_ptr<Page>& a_page) override;
};
#endif //PAGE_REPLACEMENT_ALGORITHMS_READ_ORDER_HPP
