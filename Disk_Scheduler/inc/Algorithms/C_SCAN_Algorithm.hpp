//
// Created by jakub on 09.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_C_SCAN_ALGORITHM_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_C_SCAN_ALGORITHM_HPP
#include "IAlgorithm.hpp"

class C_SCAN_Algorithm : public IAlgorithm{
public:
    explicit C_SCAN_Algorithm(Hard_Drive& a_hard_drive);

    std::unique_ptr<Order> process_queue() override;
};
#endif //HARD_DRIVE_ACCESS_ALGORITHMS_C_SCAN_ALGORITHM_HPP
