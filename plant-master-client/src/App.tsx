import {  useEffect, useRef } from "react"
import { Box, CircularProgress, Container, CssBaseline, Grid } from "@mui/material"
import HumiditySensor from "./HumiditySensor"
import { Footer } from "./Footer"
import TopBar from "./TopBar"
import Modal from "./Modal"
import { IMessageEvent, w3cwebsocket } from "websocket"


const serverAddress = "ws://192.168.1.184/ws"


function App() {
  const websocket = useRef<w3cwebsocket | null>(null)



  useEffect(() => {
    websocket.current = new w3cwebsocket(serverAddress)
    websocket.current.onmessage = (message: IMessageEvent) => {
      const dataFromServer = JSON.parse(message.data.toString())
      console.log(dataFromServer)
    }
    return () => websocket.current?.close()
  }, [])

  return (
    <Box id="root" sx={{ background: "#8ebeed", height: "100%" }}>
      <CssBaseline />
      <TopBar />
      <Container sx={{ p: 2, display: "flex", justifyContent: "center", alignItems: "center", minHeight: "85vh" }}>
      </Container>
      <Footer />
    </Box>
  )
}

export default App
