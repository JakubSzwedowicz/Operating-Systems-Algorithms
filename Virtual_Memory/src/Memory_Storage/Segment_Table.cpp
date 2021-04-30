//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#include <string>
#include <vector>
#include <queue>

#include "RAM.hpp"
#include "Hard_Drive.hpp"
#include "Segment_Table.hpp"
#include "FIFO_Algorithm.hpp"
#include "OPT_Algorithm.hpp"
#include "LRU_Algorithm.hpp"
#include "LRU_Est_Algorithm.hpp"
#include "RAND_Algorithm.hpp"
#include "Order.hpp"

Segment_Table::Segment_Table(const std::string& a_algorithm, Hard_Drive* a_hdd, RAM* a_ram,
                             std::deque<std::unique_ptr<Order>>& a_queue)
        : m_segments_number(a_hdd->get_frames_number() + a_ram->get_frames_number())
        , m_pages_size(a_hdd->get_frame_size())
        , m_ram_frames(a_ram->get_frames_number())
        , m_hdd_pages(a_hdd->get_frames_number())
        , m_ram(*a_ram)
        , m_orders(a_queue) {
    m_pages_info.reserve(m_hdd_pages + m_ram_frames);
    for (int i = 0; i < m_ram_frames; i++) {
        m_pages_info.push_back(a_ram->get_page(i)->get_page_info_ptr());
    }
    for (int i = 0; i < m_hdd_pages; i++) {
        m_pages_info.push_back(a_hdd->get_page(i)->get_page_info_ptr());
    }
    if (a_algorithm == "FIFO") {
        m_algorithm = std::make_unique<FIFO_Algorithm>(&m_pages_info, a_hdd, a_ram, a_queue, *this);
    } else if (a_algorithm == "OPT") {
        m_algorithm = std::make_unique<OPT_Algorithm>(&m_pages_info, a_hdd, a_ram, a_queue, *this);
    } else if (a_algorithm == "LRU") {
        m_algorithm = std::make_unique<LRU_Algorithm>(&m_pages_info, a_hdd, a_ram, a_queue, *this);
    } else if (a_algorithm == "LRU_Est") {
        m_algorithm = std::make_unique<LRU_Est_Algorithm>(&m_pages_info, a_hdd, a_ram, a_queue, *this);
    } else if (a_algorithm == "RAND") {
        m_algorithm = std::make_unique<RAND_Algorithm>(&m_pages_info, a_hdd, a_ram, a_queue, *this);
    }
}

int Segment_Table::get_data_address(int a_segment_ID, int a_data_offset) {
    increment_time();
    return m_algorithm->get_data_address(a_segment_ID, a_data_offset);
}

void Segment_Table::set_data_segment(int a_segment_ID, int a_data) {

}

int Segment_Table::get_page_error() const {
    return m_algorithm->get_page_errors();
}

bool Segment_Table::check_is_page_loaded(int a_page_ID) const {
    return m_pages_info[a_page_ID]->m_location.m_loaded_in_ram;
}

void Segment_Table::increment_time() const {
    for (int i = 0; i < m_ram.get_frames_number(); i++) {
        m_ram.get_page(i)->get_page_info().m_time_in_memory++;
        m_ram.get_page(i)->get_page_info().m_time_last_called++;
    }
}

