import { IMessageEvent, w3cwebsocket } from "websocket"
import { useEffect, useRef, useState } from "react"
import { TopBar } from "./TopBar"
import { Box, Container, CssBaseline, Grid } from "@mui/material"
import HumiditySensor from "./HumiditySensor"
import { Footer } from "./Footer"

function App() {
  const websocket = useRef<w3cwebsocket | null>(null)

  useEffect(() => {
    websocket.current = new w3cwebsocket("ws://192.168.1.184/ws")
    websocket.current.onmessage = (message: IMessageEvent) => {
      const dataFromServer = JSON.parse(message.data.toString())
      setSensors(dataFromServer.humidity)
    }
    return () => websocket.current?.close()
  }, [])

  const initialSensors = Array.from({ length: 8 }, () => ({
    lvl: 0,
    threshold: 0,
    active: false
  }))
  const [sensors, setSensors] = useState(initialSensors)

  return (
    <Box id="root" sx={{ background: "#8ebeed", height: "100%" }}>
      <CssBaseline />
      <TopBar />
      <Container sx={{ p: 2 }}>
        <Grid container spacing={3}>
          {sensors.map((sensor, index) => (!sensor.active ? <HumiditySensor key={index} {...sensor} /> : null))}
        </Grid>
      </Container>
      <Footer />
    </Box>
  )
}

export default App
