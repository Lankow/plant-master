import { IMessageEvent, w3cwebsocket } from "websocket"
import { useEffect, useRef } from "react"
import Button from "@mui/material/Button"

function App() {
  const websocket = useRef<w3cwebsocket | null>(null)

  useEffect(() => {
    websocket.current = new w3cwebsocket("ws://192.168.1.184/ws")
    websocket.current.onmessage = (message: IMessageEvent) => {
      const dataFromServer = JSON.parse(message.data.toString())
      console.log(dataFromServer.humidity)
    }
    return () => websocket.current?.close()
  }, [])

  return (
    <div id="root">
      <div>
        <h1>
          <span>Plant-Master</span>
        </h1>
        <Button variant="contained">Update Humidity LVL</Button>
      </div>
    </div>
  )
}

export default App
