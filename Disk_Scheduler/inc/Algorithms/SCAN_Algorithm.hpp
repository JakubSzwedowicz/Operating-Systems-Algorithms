//
// Created by jakub on 09.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_SCAN_ALGORITHM_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_SCAN_ALGORITHM_HPP
#include "IAlgorithm.hpp"


class SCAN_Algorithm : public IAlgorithm {
public:
    explicit SCAN_Algorithm(Hard_Drive& aHardDrive);

    std::unique_ptr<Order> process_queue() override;
};
#endif //HARD_DRIVE_ACCESS_ALGORITHMS_SCAN_ALGORITHM_HPP
