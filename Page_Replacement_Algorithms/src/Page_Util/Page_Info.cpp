//
// Author: JakubSzwedowicz
// Date: 29.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <algorithm>

#include "Page_Info.hpp"

Page_Info::Page_Info(int a_page_ID, bool a_loaded, int a_page_index)
        : m_location(a_loaded, a_page_index), m_empty(true), m_page_ID(a_page_ID) {
}

void Page_Info::swap_locations(Page_Info& a_page_info) {
    std::swap(m_location, a_page_info.m_location);
}

void Page_Info::erase_memory() {
    m_empty = true;
    m_time_in_memory = std::numeric_limits<int>::max();
    m_time_last_called = std::numeric_limits<int>::max();
}
Page_Info::Location::Location(bool a_loaded, int a_page_index)
        : m_loaded_in_ram(a_loaded), m_page_index(a_page_index) {
}
