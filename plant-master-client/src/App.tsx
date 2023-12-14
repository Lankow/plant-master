import { IMessageEvent, w3cwebsocket } from "websocket"
import { useCallback, useEffect, useRef, useState } from "react"
import { Box, CircularProgress, Container, CssBaseline, Grid } from "@mui/material"
import HumiditySensor from "./HumiditySensor"
import { Footer } from "./Footer"
import TopBar from "./TopBar"
import Modal from "./Modal"

const debugMode = true
const initialPin = 0
const initialThreshold = 4000
const serverAddress = "ws://192.168.1.184/ws"

function App() {
  const websocket = useRef<w3cwebsocket | null>(null)
  const [editedThreshold, setEditedThreshold] = useState(initialThreshold)
  const [editedPin, setEditedPin] = useState(initialPin)
  const [editedId, setEditedId] = useState(0xff)
  const [openedModal, setOpenedModal] = useState("")
  const [dataReceived, setDataReceived] = useState(false)
  const [sensors, setSensors] = useState(Array.from({ length: 8 }, () => ({ id: 0xff, lvl: 0, threshold: 0, active: false })))

  const resetInputs = useCallback(() => {
    setEditedPin(initialPin)
    setEditedThreshold(initialThreshold)
  }, [setEditedPin, setEditedThreshold])

  const handleOpenModal = useCallback(
    (modalName: string) => {
      resetInputs()
      setOpenedModal(modalName)
    },
    [resetInputs]
  )

  const handleCloseModal = useCallback(() => {
    setOpenedModal("")
  }, [])

  const sendUpdate = useCallback(({ id, threshold, pin }: { id: number; threshold?: number; pin?: number }) => {
    const updatedData: { type: string; id: number; threshold?: number; pin?: number } = {
      type: "edit",
      id: id,
      threshold: threshold !== initialThreshold ? threshold : undefined,
      pin: pin !== initialPin ? pin : undefined
    }

    console.log(JSON.stringify(updatedData))

    websocket.current?.send(JSON.stringify(updatedData))
  }, [])

  const handleGetLogs = useCallback(() => {
    handleOpenModal("Logs")
    const logsRequest: { type: string } = {
      type: "logs"
    }
    websocket.current?.send(JSON.stringify(logsRequest))
  }, [handleOpenModal])

  const handleSaveChanges = useCallback(() => {
    sendUpdate({
      id: editedId,
      threshold: editedThreshold,
      pin: editedPin
    })
    handleCloseModal()
  }, [editedId, editedThreshold, editedPin, sendUpdate, handleCloseModal])

  useEffect(() => {
    websocket.current = new w3cwebsocket(serverAddress)
    websocket.current.onmessage = (message: IMessageEvent) => {
      const dataFromServer = JSON.parse(message.data.toString())
      if (dataFromServer.humidity) {
        console.log(dataFromServer.humidity)
        setSensors(dataFromServer.humidity)
        setDataReceived(true)
      } else if (dataFromServer.logs) {
        console.log(dataFromServer.logs)
      } else {
        setDataReceived(false)
      }
    }
    return () => websocket.current?.close()
  }, [])

  return (
    <Box id="root" sx={{ background: "#8ebeed", height: "100%" }}>
      <CssBaseline />
      <TopBar handleOpenModal={handleOpenModal} handleGetLogs={handleGetLogs} />
      <Container sx={{ p: 2, display: "flex", justifyContent: "center", alignItems: "center", minHeight: "85vh" }}>
        {dataReceived ? (
          <Grid container spacing={3}>
            {sensors.map((sensor, index) =>
              sensor.active || debugMode ? (
                <HumiditySensor //
                  key={index}
                  id={sensor.id}
                  lvl={sensor.lvl}
                  threshold={sensor.threshold}
                  active={sensor.active}
                  handleOpenModal={handleOpenModal}
                  setEditedId={setEditedId}
                />
              ) : null
            )}
          </Grid>
        ) : (
          <CircularProgress size="10rem" />
        )}
      </Container>
      <Footer />
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
    </Box>
  )
}

export default App
