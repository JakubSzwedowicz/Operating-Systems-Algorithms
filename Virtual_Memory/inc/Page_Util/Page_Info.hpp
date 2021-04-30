//
// Author: JakubSzwedowicz
// Date: 29.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_PAGE_INFO_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_PAGE_INFO_HPP

struct Page_Info {
    // STRUCTS
    struct Access {
        Access() = default;

        bool m_write;
        bool m_read;
    };

    struct Type {
        Type() = default;

        bool m_code;
        bool m_data;
        bool m_mixed;
    };

    struct Location {
        Location(bool a_loaded, int a_page_index);

        bool m_loaded_in_ram;
        int m_page_index;
    };

    // METHODS
    Page_Info(int a_page_number, bool a_loaded, int a_physical_address = -1);

    void swap_locations(Page_Info& a_page_info);

    void erase_memory();

    // MEMBERS
    Location m_location;
    Access m_access;
    Type m_type;
    bool m_empty;
    const int m_page_ID;
    int m_time_in_memory;
    int m_time_last_called;
};

#endif //PAGE_REPLACEMENT_ALGORITHMS_PAGE_INFO_HPP
