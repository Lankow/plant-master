import { useEffect, useState, useCallback, useRef } from "react";
import { Box, Container, CssBaseline, Grid } from "@mui/material";
import { Footer } from "./Footer";
import TopBar from "./TopBar";
import Modal from "./Modal";
import HumidityPanel from "./HumidityPanel";
import { IMessageEvent, w3cwebsocket } from "websocket";

const serverAddress = "ws://192.168.1.184/ws";
const initialThreshold = 0
const initialPin = 0
interface Sensor {
  id: number;
  pin: number;
  humidity: number;
  threshold: number;
}

interface UpdatedData {
  pin: number
  threshold: number
}

function App() {
  const [sensors, setSensors] = useState<Array<Sensor>>([]);
  const [roomTemperature, setRoomTemperature] = useState<number>(0.0);
  const [roomHumidity, setRoomHumidity] = useState<number>(0.0);
  const [editedThreshold, setEditedThreshold] = useState(initialThreshold)
  const [editedPin, setEditedPin] = useState(initialPin)

  const websocket = useRef<w3cwebsocket | null>(null);
  const [openedModal, setOpenedModal] = useState("");

  const handleOpenModal = useCallback((modalName: string) => {
    setOpenedModal(modalName);
  }, []);

  const handleCloseModal = useCallback(() => {
    setOpenedModal("");
  }, []);

  const sendUpdate = useCallback(({ pin, threshold  }: { pin: number;  threshold: number }) => {
    const updatedData: UpdatedData = {
      pin,
      threshold
    }

    console.log(JSON.stringify(updatedData))

    websocket.current?.send(JSON.stringify(updatedData))
  }, [])

  const handleSaveChanges = useCallback(() => {
    sendUpdate({
      pin: editedPin,
      threshold: editedThreshold
    })
    handleCloseModal()
  }, [editedThreshold, editedPin, sendUpdate, handleCloseModal])

  useEffect(() => {
    websocket.current = new w3cwebsocket(serverAddress);
    websocket.current.onmessage = (message: IMessageEvent) => {
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
    return () => websocket.current?.close();
  }, []);

  return (
    <Box id="root" sx={{ background: "#8ebeed", height: "100%" }}>
      <CssBaseline />
      <TopBar handleOpenModal={handleOpenModal} roomTemperature={roomTemperature} roomHumidity={roomHumidity} />
      <Container sx={{ p: 2, minHeight: "85vh" }}>
        <Grid container spacing={1} rowSpacing={0}>
          {sensors.map((sensor, index) => (
            <HumidityPanel
              key={index}
              pin={sensor.pin}
              id={sensor.id}
              humidity={sensor.humidity}
              threshold={sensor.threshold}
              handleOpenModal={handleOpenModal}
              setEditedPin={setEditedPin}
              setEditedThreshold={setEditedThreshold}
            />
          ))}
        </Grid>
      </Container>
      <Modal
        open={openedModal !== ""} //
        openedModal={openedModal}
        editedPin={editedPin}
        editedThreshold={editedThreshold}
        setEditedPin={setEditedPin}
        setEditedThreshold={setEditedThreshold}
        handleCloseModal={handleCloseModal}
        handleSaveChanges={handleSaveChanges}
      />
      <Footer />
    </Box>
  );
}

export default App;