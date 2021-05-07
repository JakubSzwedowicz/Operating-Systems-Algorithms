//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_ORDER_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_ORDER_HPP

#include <memory>

class Page;

class Order {
public:
    Order(int a_segment, int a_offset, int a_data);

    Order(int a_segment, int a_offset);

    virtual ~Order() = default;

    virtual void process_order(const std::unique_ptr<Page>& a_page) = 0;

    [[nodiscard]] int get_data() const;

    [[nodiscard]] int get_segment() const;

    [[nodiscard]] int get_offset() const;

    [[nodiscard]] bool get_processed() const;

    void set_data(int a_data);

    void set_data(int a_byte_index, int a_data);

protected:
    int m_segment;
    int m_offset;
    int m_data;
    bool m_processed;
};

#endif //PAGE_REPLACEMENT_ALGORITHMS_ORDER_HPP
