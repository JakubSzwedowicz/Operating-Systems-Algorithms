//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_PHYSICAL_MEMORY_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_PHYSICAL_MEMORY_HPP

#include <vector>
#include <memory>

#include "Page.hpp"

class IAlgorithm;

class Memory_Container {
private:
    const int m_frame_size; // in bytes
    int m_frames_number;    // must be a positive number
    int m_total_size;   // in bytes
    int m_frames_in_use;
    const int m_begin_address = 0;
    int m_end_address = 0;  // resulting variable
    std::vector<std::unique_ptr<Page>> m_pages;   // Can't be changed runtime!
public:
    Memory_Container(int a_first_frame_ID, int a_frame_size, int a_frames_number, bool a_loaded_to_ram);

    void swap_pages(int a_first, Memory_Container& a_memory, int a_second);

    void swap_pages(std::unique_ptr<Page>& a_page_to_load, std::unique_ptr<Page>& a_page_to_unload);

    [[nodiscard]] std::unique_ptr<Page>& get_page(int a_index);

    [[nodiscard]] int get_frames_in_use() const;

    [[nodiscard]] int get_free_index() const;

    [[nodiscard]] std::unique_ptr<Page>* get_free_ptr();

    [[nodiscard]] int get_total_size() const;

    [[nodiscard]] int get_frame_size() const;

    [[nodiscard]] int get_frames_number() const;

    [[maybe_unused]] [[nodiscard]] int get_begin_address() const;

    [[nodiscard]] int get_end_address() const;

    void set_page(int a_page_index, std::unique_ptr<Page>& a_page);

    [[nodiscard]] bool is_empty() const;

    [[nodiscard]] bool is_page_empty(int a_page_index) const;

private:
    std::unique_ptr<Page> remove_page(int a_page_ID);

};

#endif //PAGE_REPLACEMENT_ALGORITHMS_PHYSICAL_MEMORY_HPP
