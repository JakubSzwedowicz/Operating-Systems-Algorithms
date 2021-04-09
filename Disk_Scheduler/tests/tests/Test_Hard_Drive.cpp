//
// Created by jakub on 07.04.2021.
//

#include "gtest/gtest.h"
#include "Hard_Drive.hpp"
#include <array>
#include <tuple>

struct Test_Hard_Drive_Fixture : public ::testing::Test {
    Hard_Drive m_hd;
    static const int s_plates = 3;
    static const int s_blocks_per_plate = 7;
    constexpr static const double s_t1 = 1000;
    constexpr static const double s_t2 = 1;

    constexpr static std::array<std::pair<int, int>, 6> s_test_read_block_for_addresses{
            std::make_pair(0, 1), std::make_pair(2, 3), std::make_pair(6, 7), std::make_pair(11, 10),
            std::make_pair(19, 13), std::make_pair(20, 14)
    };

    Test_Hard_Drive_Fixture()
            : m_hd("FIFO", s_t1, s_t2, s_plates, s_blocks_per_plate, 512) {}

    virtual void SetUp() override {
        for (auto& pair : s_test_read_block_for_addresses) {
            m_hd.set_block(pair.first, pair.second);
        }
    }

    virtual void TearDown() override {
    }

};

// So the linker could actually see static variables within the class
constexpr std::array<std::pair<int, int>, 6> Test_Hard_Drive_Fixture::s_test_read_block_for_addresses;
const int Test_Hard_Drive_Fixture::s_plates;
const int Test_Hard_Drive_Fixture::s_blocks_per_plate;

TEST_F(Test_Hard_Drive_Fixture, test_read_block_for_addresses) {
    int arg = 0;
    int next_non_zero_address = s_test_read_block_for_addresses[arg].first;
    for (int i = 0; i < s_plates * s_blocks_per_plate; i++) {
        if (i == next_non_zero_address) {
            EXPECT_EQ(s_test_read_block_for_addresses[arg].second, m_hd.read_block(i));
            if (arg < s_test_read_block_for_addresses.size()) {
                arg++;
                next_non_zero_address = s_test_read_block_for_addresses[arg].first;
            }
        } else {
            EXPECT_EQ(0, m_hd.read_block(i));
        }

    }
}

TEST_F(Test_Hard_Drive_Fixture, test_read_block_for_exceptions) {
    int i = -1;
    EXPECT_THROW(m_hd.read_block(i), std::out_of_range);
    i = s_plates * s_blocks_per_plate;
    EXPECT_THROW(m_hd.read_block(i), std::out_of_range);
}

TEST_F(Test_Hard_Drive_Fixture, test_set_block) {
    int value = 1;
    for (int i = 0; i < s_plates * s_blocks_per_plate; i++) {
        m_hd.set_block(i, (value++));
    }
    value = 1;
    for (int i = 0; i < s_plates * s_blocks_per_plate; i++) {
        EXPECT_EQ((value++), m_hd.read_block(i));
    }
}

TEST_F(Test_Hard_Drive_Fixture, test_move_to_new_pos) {
    if (s_plates * s_blocks_per_plate < 21 || s_blocks_per_plate != 7) {
        GTEST_SKIP_(
                "Size of hard drive doesn't allow to run the test!"
                " There must be exactly 3 tracks per plate (which gives exactly 7 blocks per plate) and at least 3 plates."
                " If you want to change it then recalculate possible addresses on your own");
    }
    // SIZE, ORDER OF MOVE ADDRESSES AND TIMES MATTER! DO NOT CHANGE IT!
    const int size = 8;
    const int addresses[size] = {1, 1, 3, 14, 16, 16, 17, 20};
    const double times[size] = {0.5, 1, 0.5, 1000.5, 1, 1, 0.5, 1001};
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(times[i], m_hd.move_to_new_pos(addresses[i]));
    }
}