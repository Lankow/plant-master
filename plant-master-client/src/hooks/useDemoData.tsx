import { useEffect, useState, useRef } from "react";

interface Sensor {
  id: number;
  pin: number;
  humidity: number;
  threshold: number;
}

const generateRandomNumber = (min: number, max: number) => Math.floor(Math.random() * (max - min + 1)) + min;

const generateUniquePins = (count: number, min: number, max: number) => {
  const pins = new Set<number>();
  while (pins.size < count) {
    pins.add(generateRandomNumber(min, max));
  }
  return Array.from(pins);
};

const generateRandomThreshold = (min: number, max: number) => {
  const randomMultiplier = Math.floor(generateRandomNumber(min / 5, max / 5));
  return randomMultiplier * 5;
};

const generateRandomHumidity = (min: number, max: number) => {
  return generateRandomNumber(min, max);
};

const useDemoData = () => {
  const [sensors, setSensors] = useState<Array<Sensor>>([]);
  const [roomTemperature, setRoomTemperature] = useState<number>(0.0);
  const [roomHumidity, setRoomHumidity] = useState<number>(0.0);
  const [waterPumpActive, setWaterPumpActive] = useState<boolean>(false);
  const [activeReaderPin, setActiveReaderPin] = useState<number>(0);

  const sensorsRef = useRef(sensors);
  sensorsRef.current = sensors;

  const activeReaderPinRef = useRef(activeReaderPin);
  
  useEffect(() => {
    activeReaderPinRef.current = activeReaderPin;
  }, [activeReaderPin]);

  const updateSensorHumidity = () => {
    let pumpActive = false;
    let activePin = 0;

    setSensors(sensorsRef.current.map(sensor => {
      let newHumidity = sensor.pin === activeReaderPinRef.current ? sensor.humidity + 1 : sensor.humidity - 0.25;

      if (newHumidity < 0) newHumidity = 0;
      if (newHumidity > 100) newHumidity = 100;

      if (newHumidity < sensor.threshold) {
        pumpActive = true;
        activePin = sensor.pin;
      }

      return { ...sensor, humidity: newHumidity };
    }));

    setWaterPumpActive(pumpActive);
    setActiveReaderPin(activePin);
  };

  const updateRoomConditions = () => {
    setRoomTemperature(prev => {
      let newTemp = prev + (Math.random() < 0.5 ? -0.1 : 0.1);
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
    const initialPins = generateUniquePins(5, 5, 30);
    const initialSensors = initialPins.map((pin, i) => ({
      id: i,
      pin,
      humidity: generateRandomHumidity(0, 100),
      threshold: generateRandomThreshold(0, 100),
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
    waterPumpActive,
    activeReaderPin,
    sendUpdate,
  };
};

export default useDemoData;
