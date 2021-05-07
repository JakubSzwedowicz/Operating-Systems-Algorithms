//
// Author: JakubSzwedowicz
// Date: 28.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_HDD_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_HDD_HPP
#include <vector>

#include "Memory_Container.hpp"

class IAlgorithm;
class Hard_Drive : public Memory_Container{
public:
    Hard_Drive(int a_first_page_ID, int a_page_size, int a_pages_number);

private:
    friend IAlgorithm;
};
#endif //PAGE_REPLACEMENT_ALGORITHMS_HDD_HPP
