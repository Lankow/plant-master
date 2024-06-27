import { useEffect, useRef, useCallback, useState } from "react";
import { IMessageEvent, w3cwebsocket } from "websocket";

const serverAddress = "ws://192.168.1.184/ws";

interface Sensor {
  id: number;
  pin: number;
  humidity: number;
  threshold: number;
}

interface UpdatedData {
  pin: number;
  threshold: number;
}

const useWebSocket = () => {
  const [sensors, setSensors] = useState<Array<Sensor>>([]);
  const [roomTemperature, setRoomTemperature] = useState<number>(0.0);
  const [roomHumidity, setRoomHumidity] = useState<number>(0.0);

  const websocket = useRef<w3cwebsocket | null>(null);
  const timeoutRef = useRef<NodeJS.Timeout | null>(null);

  const clearState = () => {
    setSensors([]);
    setRoomHumidity(0.0);
    setRoomTemperature(0.0);
  };

  const resetTimeout = () => {
    if (timeoutRef.current) {
      clearTimeout(timeoutRef.current);
    }
    timeoutRef.current = setTimeout(clearState, 5000);
  };

  useEffect(() => {
    websocket.current = new w3cwebsocket(serverAddress);
    websocket.current.onmessage = (message: IMessageEvent) => {
      resetTimeout();
      const dataFromServer = JSON.parse(message.data.toString());
      console.log(dataFromServer);
      if (dataFromServer.plantsHumidity) {
        setSensors(dataFromServer.plantsHumidity);
      }
      if (dataFromServer.roomHumidity) {
        setRoomHumidity(dataFromServer.roomHumidity);
      }
      if (dataFromServer.roomTemperature) {
        setRoomTemperature(dataFromServer.roomTemperature);
      }
    };

    // Set the initial timeout
    resetTimeout();

    return () => {
      if (timeoutRef.current) {
        clearTimeout(timeoutRef.current);
      }
      websocket.current?.close();
    };
  }, []);

  const sendUpdate = useCallback(({ pin, threshold }: UpdatedData) => {
    const updatedData: UpdatedData = {
      pin,
      threshold,
    };
    console.log(JSON.stringify(updatedData));
    websocket.current?.send(JSON.stringify(updatedData));
  }, []);

  return { sensors, roomTemperature, roomHumidity, sendUpdate };
};

export default useWebSocket;