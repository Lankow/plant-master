import { IMessageEvent, w3cwebsocket } from "websocket"
import { useCallback, useEffect, useRef, useState } from "react"
import { Box, Container, CssBaseline, Grid } from "@mui/material"
import HumiditySensor from "./HumiditySensor"
import { Footer } from "./Footer"
import TopBar from "./TopBar"
import Modal from "./Modal"

function App() {
  const initialPin: number = 0
  const initialThreshold: number = 4000

  const websocket = useRef<w3cwebsocket | null>(null)
  const [editedThreshold, setEditedThreshold] = useState(initialThreshold)
  const [editedPin, setEditedPin] = useState(initialPin)
  const [editedId, setEditedId] = useState(0xff)
  const [openedModal, setOpenedModal] = useState("")

  const resetInputs = useCallback(() => {
    setEditedPin(initialPin)
    setEditedThreshold(initialThreshold)
  }, [setEditedPin, setEditedThreshold])

  const handleOpenModal = (modalName: string) => {
    resetInputs()
    setOpenedModal(modalName)
  }

  const handleCloseModal = useCallback(() => {
    setOpenedModal("")
  }, [setOpenedModal])

  const sendUpdate = useCallback(({ id, threshold, pin }: { id: number; threshold?: number; pin?: number }) => {
    const updatedData: { type: string; id: number; threshold?: number; pin?: number } = {
      type: "edit",
      id,
      threshold: undefined,
      pin: undefined
    }

    if (threshold !== initialThreshold) {
      updatedData.threshold = threshold
    }

    if (pin !== initialPin) {
      updatedData.pin = pin
    }

    websocket.current?.send(JSON.stringify(updatedData))
  }, [])

  const handleSaveChanges = useCallback(() => {
    sendUpdate({
      id: editedId,
      threshold: editedThreshold,
      pin: editedPin
    })
    handleCloseModal()
  }, [editedId, editedThreshold, editedPin, sendUpdate, handleCloseModal])

  useEffect(() => {
    websocket.current = new w3cwebsocket("ws://192.168.1.184/ws")
    websocket.current.onmessage = (message: IMessageEvent) => {
      const dataFromServer = JSON.parse(message.data.toString())
      setSensors(dataFromServer.humidity)
    }
    return () => websocket.current?.close()
  }, [])

  const initialSensors = Array.from({ length: 8 }, () => ({
    id: 0xff,
    lvl: 0,
    threshold: 0,
    active: false
  }))
  const [sensors, setSensors] = useState(initialSensors)

  return (
    <Box id="root" sx={{ background: "#8ebeed", height: "100%" }}>
      <CssBaseline />
      <TopBar handleOpenModal={handleOpenModal} />
      <Container sx={{ p: 2 }}>
        <Grid container spacing={3}>
          {sensors.map((sensor, index) =>
            !sensor.active ? (
              <HumiditySensor
                key={index} //
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
