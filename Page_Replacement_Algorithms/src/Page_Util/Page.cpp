//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include "Page.hpp"

Page::Page(int a_page_ID, int a_size, bool a_loaded, int a_page_index)
        : m_page_info(a_page_ID, a_loaded, a_page_index) {
    m_size = a_size;
    m_data = 0;
}

Page_Info& Page::get_page_info() {
    return m_page_info;
}

int Page::get_data(int a_offset) const {
    return m_data;
}

Page_Info* Page::get_page_info_ptr() {
    return &m_page_info;
}

int Page::get_size() const {
    return m_size;
}

bool Page::is_empty() const {
    return m_page_info.m_empty;
}

void Page::erase_memory() {
    m_page_info.erase_memory();
}

void Page::set_data(int a_data, int a_offset) {
    if (m_page_info.m_empty) {
        m_page_info.m_time_in_memory = 0;
    }
    m_page_info.m_time_last_called = 0;
    m_data = a_data;
    m_page_info.m_empty = false;
}

void Page::set_data(int a_data) {
    set_data(a_data, 0);

}

void Page::set_page_info(bool a_write, bool a_read, bool a_code, bool a_data) {
    m_page_info.m_access.m_write = a_write;
    m_page_info.m_access.m_read = a_read;
    m_page_info.m_type.m_code = a_code;
    m_page_info.m_type.m_data = a_data;
}

void Page::swap_locations_with_page(Page& a_page) {
    m_page_info.swap_locations(a_page.m_page_info);
}



