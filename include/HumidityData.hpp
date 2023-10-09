/*
*   HumidityData.hpp
*   ----------------------
*   Created on: 2023/10/09
*   Author: Lankow
*/
#ifndef HUMIDITY_DATA_HPP
#define HUMIDITY_DATA_HPP
class HumidityData
{
    private:
    int m_currentHumidityLvl;
    int m_humidityThreshold;
    bool m_needsWatering;

    public:
    HumidityData();

    int& getCurrentHumidityLvl();
    int& getHumidityThreshold();
    bool& getNeedsWatering();

    void setCurrentHumidityLvl(int p_currentHumidityLvl);
    void setHumidityThreshold(int p_humidityThreshold);
    void setNeedsWatering(bool p_needsWatering);
};
#endif // HUMIDITY_DATA_HPP