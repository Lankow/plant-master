/*
*   HumidityHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
class HumidityHandler
{
    private:
    int m_operatedPin;
    int m_currentHumidityLvl;
    int m_humidityThreshold;
    bool m_needsWatering;

    void compareHumidity();

    public:
    HumidityHandler(int pin, int threshold);
    
    void readHumidity();
    void setHumidityThreshold(int value);
    void setOperatedPin(int pin);

    bool getNeedsWatering();
};