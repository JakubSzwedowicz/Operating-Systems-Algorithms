//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#include <memory>

#include "Memory_Container.hpp"
#include "Page.hpp"

Memory_Container::Memory_Container(int a_first_frame_ID, int a_frame_size, int a_frames_number,
                                   bool a_loaded_to_ram)
        : m_frame_size(a_frame_size)
        , m_frames_number(a_frames_number)
        , m_total_size(a_frame_size * a_frames_number)
        , m_frames_in_use(0)
        , m_begin_address(a_first_frame_ID * a_frame_size)
        , m_end_address(m_begin_address + a_frame_size * a_frames_number - 1) {
    int frame_ID = a_first_frame_ID;
    int frame_index = 0;
    m_pages.reserve(a_frames_number);
    for (int i = 0; i < m_frames_number; i++) {
        m_pages.push_back(std::make_unique<Page>(frame_ID, a_frame_size, a_loaded_to_ram, frame_index));
        frame_ID++;
        frame_index++;
    }
}

std::unique_ptr<Page>& Memory_Container::get_page(int a_index) {
    return m_pages[a_index];
}

void Memory_Container::set_page(int a_page_index, std::unique_ptr<Page>& a_page) {
    m_frames_in_use++;
    m_pages[a_page_index] = std::move(a_page);
}

bool Memory_Container::is_empty() const {
    return m_pages.empty();
}

bool Memory_Container::is_page_empty(int a_page_index) const {
    return m_pages[a_page_index] == nullptr;
}

std::unique_ptr<Page> Memory_Container::remove_page(int a_page_ID) {
    std::unique_ptr<Page> ret = std::move(m_pages[a_page_ID]);
    m_frames_in_use--;
    return ret;
}

int Memory_Container::get_free_index() const {
//    if (m_frames_in_use == m_frames_number) {
//        return -1;
//    }
    int ret = 0;
    for (ret = 0; ret < m_frames_number; ret++) {
        if (m_pages[ret]->is_empty()) {
            return ret;
        }
    }
    return -1;
}


std::unique_ptr<Page>* Memory_Container::get_free_ptr() {
//    if (m_frames_in_use == m_frames_number) {
//        return nullptr;
//    }
    for (auto& unq_ptr : m_pages) {
        if (unq_ptr->is_empty()) {
            return &unq_ptr;
        }
    }
    return {};
}


int Memory_Container::get_total_size() const {
    return m_total_size;
}

int Memory_Container::get_frame_size() const {
    return m_frame_size;
}

int Memory_Container::get_frames_number() const {
    return m_frames_number;
}

int Memory_Container::get_begin_address() const {
    return m_begin_address;
}

int Memory_Container::get_end_address() const {
    return m_end_address;
}

int Memory_Container::get_frames_in_use() const {
    return m_frames_in_use;
}

void Memory_Container::swap_pages(int a_first, Memory_Container& a_memory, int a_second) {
    swap_pages(m_pages[a_first], a_memory.m_pages[a_second]);
}

void Memory_Container::swap_pages(std::unique_ptr<Page>& a_page_to_load, std::unique_ptr<Page>& a_page_to_unload) {
    a_page_to_load->get_page_info().m_time_last_called = 0;
    a_page_to_load->get_page_info().m_time_in_memory = 0;
    a_page_to_load->swap_locations_with_page(*a_page_to_unload);
    a_page_to_load.swap(a_page_to_unload);
}




