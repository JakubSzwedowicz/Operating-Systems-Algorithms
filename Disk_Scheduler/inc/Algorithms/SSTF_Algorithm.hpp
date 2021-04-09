//
// Created by jakub on 08.04.2021.
//

#ifndef HARD_DRIVE_ACCESS_ALGORITHMS_SSTF_ALGORITHM_HPP
#define HARD_DRIVE_ACCESS_ALGORITHMS_SSTF_ALGORITHM_HPP

#include "IAlgorithm.hpp"
#include "Hard_Drive.hpp"

class SSTF_Algorithm : public IAlgorithm {
//    std::vector<int> m_blocks_on_tracks;
//    int m_number_of_plates;
public:
    explicit SSTF_Algorithm(Hard_Drive& a_hard_drive);

    std::unique_ptr<Order> process_queue() override;
};
#endif //HARD_DRIVE_ACCESS_ALGORITHMS_SSTF_ALGORITHM_HPP
