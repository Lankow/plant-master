import {  useEffect, useState, useCallback, useRef } from "react"
import { Box, Container, CssBaseline } from "@mui/material"
import { Footer } from "./Footer"
import TopBar from "./TopBar"
import Modal from "./Modal"
import { IMessageEvent, w3cwebsocket } from "websocket"


const serverAddress = "ws://192.168.1.184/ws"

function App() {
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
    }
    return () => websocket.current?.close()
  }, [])

  return (
    <Box id="root" sx={{ background: "#8ebeed", height: "100%" }}>
      <CssBaseline />
      <TopBar handleOpenModal={handleOpenModal}/>
      <Container sx={{ p: 2, display: "flex", justifyContent: "center", alignItems: "center", minHeight: "85vh" }}>
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
