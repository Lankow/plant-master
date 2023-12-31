import React, { useCallback, useEffect, useRef, useState } from "react"
import { Box, CircularProgress, Container, CssBaseline, Grid } from "@mui/material"
import HumiditySensor from "./HumiditySensor"
import { Footer } from "./Footer"
import TopBar from "./TopBar"
import Modal from "./Modal"
import { IMessageEvent, w3cwebsocket } from "websocket"

const debugMode = true
const initialPin = 0
const initialThreshold = 4000
const serverAddress = "ws://192.168.1.184/ws"

interface Sensor {
  id: number
  lvl: number
  threshold: number
  active: boolean
}

interface LogsState {
  files: string[]
  count: number
  page: number
}

interface UpdatedData {
  type: string
  id: number
  threshold?: number
  pin?: number
}

interface LogsRequest {
  type: string
  page: number
}

function App() {
  const websocket = useRef<w3cwebsocket | null>(null)
  const [editedThreshold, setEditedThreshold] = useState(initialThreshold)
  const [editedPin, setEditedPin] = useState(initialPin)
  const [editedId, setEditedId] = useState(0xff)
  const [openedModal, setOpenedModal] = useState("")
  const [dataReceived, setDataReceived] = useState(false)
  const [sensors, setSensors] = useState<Array<Sensor>>(Array.from({ length: 8 }, () => ({ id: 0xff, lvl: 0, threshold: 0, active: false })))
  const [logsState, setLogsState] = useState<LogsState>({
    files: [],
    count: 0,
    page: 1
  })

  const resetInputs = useCallback(() => {
    setEditedPin(initialPin)
    setEditedThreshold(initialThreshold)
  }, [])

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
    const updatedData: UpdatedData = {
      type: "edit",
      id,
      threshold: threshold !== initialThreshold ? threshold : undefined,
      pin: pin !== initialPin ? pin : undefined
    }

    console.log(JSON.stringify(updatedData))

    websocket.current?.send(JSON.stringify(updatedData))
  }, [])

  const handleGetLogs = useCallback(() => {
    handleOpenModal("Logs")
    const logsRequest: LogsRequest = {
      type: "logs",
      page: logsState.page - 1
    }
    websocket.current?.send(JSON.stringify(logsRequest))
  }, [handleOpenModal, logsState.page])

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
        setSensors(dataFromServer.humidity)
        setDataReceived(true)
      } else if (dataFromServer.logs) {
        setLogsState({
          files: dataFromServer.logs.files,
          count: dataFromServer.logs.count,
          page: dataFromServer.logs.page
        })
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
        logFiles={logsState.files}
        logCount={logsState.count}
      />
    </Box>
  )
}

export default App
