import React from "react"

type HumiditySensorProps = {
  id: number
  currentHumidityLvl: number
  humidityThreshold: number
  humidityActive: boolean
}

export const HumiditySensor: React.FC<HumiditySensorProps> = ({ id, currentHumidityLvl, humidityThreshold, humidityActive }) => (
  <div>
    <h6>Humidity Sensor</h6>
    <div>Id: {id}</div>
    <div>Current humidity LVL: {currentHumidityLvl}</div>
    <div>Humidity Threshold: {humidityThreshold}</div>
    <div>Active: {humidityActive}</div>
  </div>
)
