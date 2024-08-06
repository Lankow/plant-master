import { useState, useCallback } from "react";
import { Box, CircularProgress, Container, CssBaseline, Grid } from "@mui/material";
import Footer from "./components/Footer";
import TopBar from "./components/TopBar";
import Modal from "./components/Modal";
import HumidityPanel from "./components/panels/HumidityPanel";
import useWebSocket from "./hooks/useWebSocket";
import useDemoData from "./hooks/useDemoData";

const initialThreshold = 0;
const initialPin = 0;

function App() {
  const isDemo = import.meta.env.VITE_DEMO === "true";
  const { sensors, roomTemperature, roomHumidity, waterPumpActive, activeReaderPin, sendUpdate } = isDemo ? useDemoData() : useWebSocket();
  const [editedThreshold, setEditedThreshold] = useState(initialThreshold);
  const [editedPin, setEditedPin] = useState(initialPin);
  const [openedModal, setOpenedModal] = useState("");

  const handleOpenModal = useCallback((modalName: string) => {
    setOpenedModal(modalName);
  }, []);

  const handleCloseModal = useCallback(() => {
    setOpenedModal("");
  }, []);

  const handleSaveChanges = useCallback(() => {
    sendUpdate({
      pin: editedPin,
      threshold: editedThreshold,
    });
    handleCloseModal();
  }, [editedThreshold, editedPin, sendUpdate, handleCloseModal]);

  return (
    <Box id="root" sx={{ background: "#8ebeed", height: "100%" }}>
      <CssBaseline />
      <TopBar 
        handleOpenModal={handleOpenModal} 
        roomTemperature={roomTemperature} 
        roomHumidity={roomHumidity} 
        waterPumpActive={waterPumpActive} 
        activeReaderPin={activeReaderPin} 
      />
      <Container sx={{ p: 2, minHeight: "85vh" }}>
        {sensors.length > 0 ? (
          <Grid container spacing={1} rowSpacing={0}>
            {sensors.map((sensor, index) => (
              <HumidityPanel
                key={index}
                pin={sensor.pin}
                id={sensor.id}
                humidity={sensor.humidity}
                threshold={sensor.threshold}
                activeReaderPin={activeReaderPin}
                handleOpenModal={handleOpenModal}
                setEditedPin={setEditedPin}
                setEditedThreshold={setEditedThreshold}
              />
            ))}
          </Grid>
        ) : (
          <Box display="flex" justifyContent="center" alignItems="center" minHeight="85vh">
            <CircularProgress size="10rem" />
          </Box>
        )}
      </Container>
      <Modal
        open={openedModal !== ""}
        openedModal={openedModal}
        editedThreshold={editedThreshold}
        setEditedThreshold={setEditedThreshold}
        handleCloseModal={handleCloseModal}
        handleSaveChanges={handleSaveChanges}
      />
      <Footer />
    </Box>
  );
}

export default App;
