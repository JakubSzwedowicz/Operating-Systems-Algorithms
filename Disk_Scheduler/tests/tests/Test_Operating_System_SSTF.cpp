//
// Created by jakub on 08.04.2021.
//

#include "gtest/gtest.h"
#include "Operating_System.hpp"
#include "Writing_Order.hpp"
#include "Reading_Order.hpp"

#include <array>
#include <tuple>

struct Test_Operating_System_SSTF_Fixture : public ::testing::Test {
    Operating_System m_os;
    static const int m_number_of_plates = 3;
    static const int m_number_of_blocks_per_plate = 7;
    static const int m_block_size = 512;
    constexpr static const double m_t1 = 1000;
    constexpr static const double m_t2 = 1;
    static const int s_orders_size = 8;
    constexpr static std::array<std::pair<int, int>, s_orders_size> s_orders_parameters = {
            std::make_pair<int, int>(1, 1),
            std::make_pair<int, int>(18, 2),
            std::make_pair<int, int>(3, -1),
            std::make_pair<int, int>(19, 3),
            std::make_pair<int, int>(6, -1),
            std::make_pair<int, int>(13, 4),
            std::make_pair<int, int>(15, 5),
            std::make_pair<int, int>(19, -1)
    };

    constexpr static std::array<std::pair<int, double>, s_orders_size> s_orders_order_and_times = {
            std::make_pair<int, double>(1, 0.5),
            std::make_pair<int, double>(6, 0.25),
            std::make_pair<int, double>(3, 0.25),
            std::make_pair<int, double>(13, 1000.5),
            std::make_pair<int, double>(15, 1),
            std::make_pair<int, double>(19, 1001),
            std::make_pair<int, double>(18, 1),
            std::make_pair<int, double>(19, 1)
    };


    Test_Operating_System_SSTF_Fixture() : m_os("SSTF", m_t1, m_t2, m_number_of_plates, m_number_of_blocks_per_plate,
                                                m_block_size) {}

protected:
    void SetUp() override {
        for(int i = 0; i < s_orders_size; i++){
            if(s_orders_parameters[i].second != -1){
                m_os.add_order(std::make_unique<Writing_Order>(Writing_Order(s_orders_parameters[i].first, s_orders_parameters[i].second)));
            } else {
                m_os.add_order(std::make_unique<Reading_Order>(Reading_Order(s_orders_parameters[i].first)));
            }
        }
    }

    void TearDown() override {
    }
};

const int Test_Operating_System_SSTF_Fixture::s_orders_size;
constexpr std::array<std::pair<int, int>, 8> Test_Operating_System_SSTF_Fixture::s_orders_parameters;
constexpr std::array<std::pair<int, double>, 8> Test_Operating_System_SSTF_Fixture::s_orders_order_and_times;
const int Test_Operating_System_SSTF_Fixture::m_block_size;

TEST_F(Test_Operating_System_SSTF_Fixture, test_run_for_proccess_and_overall_time) {
    double sum = 0;
    for (int i = 0; i < s_orders_size; i++) {
        std::unique_ptr<Order> order = m_os.process_one();
        EXPECT_EQ(s_orders_order_and_times[i].first, order->get_block_address());
        double time = m_os.get_previous_operation_time();
        EXPECT_EQ(s_orders_order_and_times[i].second, time);
        sum += time;
    }
    EXPECT_EQ(sum, m_os.get_whole_working_time());
}
