//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//
#include <stdexcept>
#include "Hard_Drive.hpp"
#include "Memory_Container.hpp"

Hard_Drive::Hard_Drive(int a_first_page_ID, int a_page_size, int a_pages_number)
        : Memory_Container(a_first_page_ID, a_page_size, a_pages_number, false) {
    if (a_page_size <= 0 || a_page_size % 2 != 0 || a_pages_number <= 0) {
        throw std::invalid_argument("Ram::Ram(int, int)"
                                    "\n\tpage size = " + std::to_string(a_page_size)
                                            .append("\n\tpages number = ") + std::to_string(a_pages_number));
    }
}