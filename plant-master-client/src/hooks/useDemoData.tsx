import { useEffect, useState, useRef } from "react";

interface Sensor {
  id: number;
  pin: number;
  humidity: number;
  threshold: number;
}

const generateRandomNumber = (min: number, max: number) => Math.floor(Math.random() * (max - min + 1)) + min;

const useDemoData = () => {
  const [sensors, setSensors] = useState<Array<Sensor>>([]);
  const [roomTemperature, setRoomTemperature] = useState<number>(0.0);
  const [roomHumidity, setRoomHumidity] = useState<number>(0.0);

  const sensorsRef = useRef(sensors);
  sensorsRef.current = sensors;

  const updateSensorHumidity = () => {
    setSensors(sensorsRef.current.map(sensor => {
      let newHumidity = sensor.humidity + (Math.random() < 0.5 ? -20 : 20);
      if (newHumidity < 100) newHumidity = 100;
      if (newHumidity > 4000) newHumidity = 4000;
      return { ...sensor, humidity: newHumidity };
    }));
  };

  const updateRoomConditions = () => {
    setRoomTemperature(prev => {
      let newTemp = prev + (Math.random() < 0.5 ? -0.5 : 0.5);
      if (newTemp < 15) newTemp = 15;
      if (newTemp > 30) newTemp = 30;
      return newTemp;
    });

    setRoomHumidity(prev => {
      let newHumidity = prev + (Math.random() < 0.5 ? -0.5 : 0.5);
      if (newHumidity < 20) newHumidity = 20;
      if (newHumidity > 80) newHumidity = 80;
      return newHumidity;
    });
  };

  useEffect(() => {
    const initialSensors = Array.from({ length: 5 }, (_, i) => ({
      id: i,
      pin: i,
      humidity: generateRandomNumber(100, 4000),
      threshold: generateRandomNumber(100, 4000),
    }));
    setSensors(initialSensors);

    const intervalId = setInterval(() => {
      updateSensorHumidity();
      updateRoomConditions();
    }, 1000);

    return () => clearInterval(intervalId);
  }, []);

  const sendUpdate = ({ pin, threshold }: { pin: number; threshold: number }) => {
    setSensors(prev =>
      prev.map(sensor => (sensor.pin === pin ? { ...sensor, threshold } : sensor))
    );
  };

  return {
    sensors,
    roomTemperature,
    roomHumidity,
    sendUpdate,
  };
};

export default useDemoData;
