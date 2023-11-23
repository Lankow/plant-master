import { IMessageEvent, w3cwebsocket } from "websocket"
import { useEffect, useRef, useState } from "react"
import Button from "@mui/material/Button"

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

  const initialSensors = Array.from({ length: 10 }, () => ({
    lvl: 0,
    threshold: 50,
    active: false
  }))
  const [sensors, setSensors] = useState(initialSensors)

  return (
    <div id="root">
      <div>
        <h1>
          <span>Plant-Master</span>
        </h1>
        {sensors.map((sensor, index) => (
          <div key={index}>
            <p>Current Level: {sensor.lvl}</p>
            <p>Threshold: {sensor.threshold}</p>
            <p>Active: {sensor.active ? "Yes" : "No"}</p>
            <hr />
          </div>
        ))}
        <Button variant="contained">Update Humidity LVL</Button>
      </div>
    </div>
  )
}

export default App
