//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#include <stdexcept>
#include "Order.hpp"

Order::Order(int a_segment, int a_offset)
        : Order(a_segment, a_offset, 0) {
}


Order::Order(int a_segment, int a_offset, int a_data)
        : m_segment(a_segment), m_offset(a_offset), m_data(a_data), m_processed(false) {
}

int Order::get_data() const {
    return m_data;
}

int Order::get_segment() const {
    return m_segment;
}

int Order::get_offset() const {
    return m_offset;
}

bool Order::get_processed() const {
    return m_processed;
}

void Order::set_data(int a_data) {
    m_data = a_data;
}

void Order::set_data(int a_byte_index, int a_data) {
    throw std::logic_error(
            "Pages don't contain blocks of data but a single int, thus function hasn't been implemented yet");
    // Placeholder to erase the warning about making this method static.
    m_data = a_data;
}

