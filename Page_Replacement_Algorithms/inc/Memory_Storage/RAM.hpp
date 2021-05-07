//
// Author: JakubSzwedowicz
// Date: 26.04.2021.
// e-mail: kuba.szwedowicz@gmail.com 
//

#ifndef PAGE_REPLACEMENT_ALGORITHMS_RAM_HPP
#define PAGE_REPLACEMENT_ALGORITHMS_RAM_HPP

#include <vector>
#include <memory>

#include "Memory_Container.hpp"

class IAlgorithm;
class RAM : public Memory_Container {
public:
    RAM(int a_frame_size, int a_frame_number);

private:
    friend IAlgorithm;

};

#endif //PAGE_REPLACEMENT_ALGORITHMS_RAM_HPP
