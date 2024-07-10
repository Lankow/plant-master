#include <gtest/gtest.h>
#include "gtest/internal/gtest-filepath.h"
#include "data/PlantHumidityData.hpp"

// Test the constructor
TEST(PlantHumidityDataTest, ConstructorTest)
{
    uint8_t pin = 5;
    uint16_t threshold = 3000;
    PlantHumidityData data(pin, threshold);

    EXPECT_EQ(data.getAssignedPin(), pin);
    EXPECT_EQ(data.getCurrentHumidity(), 0);
    EXPECT_EQ(data.getHumidityThreshold(), threshold);
}

TEST(PlantHumidityDataTest, SetGetAssignedPinTest)
{
    PlantHumidityData data(5, 3000);
    uint8_t newPin = 7;
    data.setAssignedPin(newPin);

    EXPECT_EQ(data.getAssignedPin(), newPin);
}

TEST(PlantHumidityDataTest, SetGetCurrentHumidityTest)
{
    PlantHumidityData data(5, 3000);
    uint16_t newHumidity = 1500;
    data.setCurrentHumidity(newHumidity);

    EXPECT_EQ(data.getCurrentHumidity(), newHumidity);
}

TEST(PlantHumidityDataTest, SetGetHumidityThresholdTest)
{
    PlantHumidityData data(5, 3000);
    uint16_t newThreshold = 2500;
    data.setHumidityThreshold(newThreshold);

    EXPECT_EQ(data.getHumidityThreshold(), newThreshold);
}