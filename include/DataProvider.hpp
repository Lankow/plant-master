/*
*   DataProvider.hpp
*   ----------------------
*   Created on: 2023/09/29
*   Author: Lankow
*/
#ifndef DATA_PROVIDER_HPP
#define DATA_PROVIDER_HPP

// DataProvider to store all the information that could be forwarded
// Handlers have a handle on a dataProvider and on cyclics fill data
// DataManager on cyclic checks and manages the data e.g. humidity thresholds

class DataProvider
{
    private:
    int m_currentHumidityLvl;
    int m_humidityThreshold;
    bool m_needsWatering;
    char m_currentTime[20];
    float m_temperature;
    float m_roomHumidity;

    public:
    DataProvider();

    int& getCurrentHumidityLvl();
    int& getHumidityThreshold();
    bool& getNeedsWatering();
    float& getTemperature();
    float& getRoomHumidity();
    char* getCurrentTime();
    
    void setCurrentHumidityLvl(int p_currentHumidityLvl);
    void setHumidityThreshold(int p_humidityThreshold);
    void setNeedsWatering(bool p_needsWatering);
    void setCurrentTime(char p_currentTime[]);
    void setTemperature(float p_temperature);
    void setRoomHumidity(float p_roomHumidity);
};
#endif // DATA_PROVIDER_HPP
