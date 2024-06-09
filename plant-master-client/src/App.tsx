import {  useEffect, useState, useCallback, useRef } from "react"
import { Box, Container, CssBaseline, Grid  } from "@mui/material"
import { Footer } from "./Footer"
import TopBar from "./TopBar"
import Modal from "./Modal"
import HumidityPanel from "./HumidityPanel"
import { IMessageEvent, w3cwebsocket } from "websocket"

const serverAddress = "ws://192.168.1.184/ws"

interface Sensor {
  id: number
  humidity: number
  threshold: number
}

function App() {
  const [sensors, setSensors] = useState<Array<Sensor>>(Array.from({ length: 4 }, () => ({ id: 0xff, humidity: 0, threshold: 0 })))
  const [roomTemperature, setRoomTemperature] = useState<number>(0.0);
  const [roomHumidity, setRoomHumidity] = useState<number>(0.0);

  const websocket = useRef<w3cwebsocket | null>(null)
  const [openedModal, setOpenedModal] = useState("")

  const handleOpenModal = useCallback(
    (modalName: string) => {
      setOpenedModal(modalName)
    },
    []
  )
  const handleCloseModal = useCallback(() => {
    setOpenedModal("")
  }, [])

  useEffect(() => {
    websocket.current = new w3cwebsocket(serverAddress)
    websocket.current.onmessage = (message: IMessageEvent) => {
      const dataFromServer = JSON.parse(message.data.toString())
      console.log(dataFromServer)
      if (dataFromServer.plantsHumidity) {
        setSensors(dataFromServer.plantsHumidity)
      }
      if(dataFromServer.roomHumidity){
        setRoomHumidity(dataFromServer.roomHumidity)
      }
      if(dataFromServer.toomTemperature){
        setRoomTemperature(dataFromServer.roomTemperature)
      }
    }
    return () => websocket.current?.close()
  }, [])

  return (
    <Box id="root" sx={{ background: "#8ebeed", height: "100%" }}>
      <CssBaseline />
      <TopBar handleOpenModal={handleOpenModal} roomTemperature={roomTemperature} roomHumidity={roomHumidity}/>
      <Container sx={{ p: 2, display: "flex", justifyContent: "center", alignItems: "center", minHeight: "85vh" }}>
      <Grid container spacing={1}>
            {sensors.map((sensor, index) => 
                <HumidityPanel
                key={index} //
                id={sensor.id}
                humidity={sensor.humidity}
                threshold={sensor.threshold}
              />
            )}
      </Grid>
      </Container>
      <Modal
        open={openedModal !== ""} //
        openedModal={openedModal}
        handleCloseModal={handleCloseModal}
      />
      <Footer />
    </Box>
  )
}

export default App
