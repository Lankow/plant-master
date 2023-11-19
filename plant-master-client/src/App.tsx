import React from "react"
import { Footer } from "./Footer"
import { HumiditySensor } from "./HumiditySensor"
import { TopBar } from "./TopBar"

type HumiditySensorState = {
  id: number
  currentHumidityLvl: number
  humidityThreshold: number
  humidityActive: boolean
}

class App extends React.Component<undefined, HumiditySensorState> {
  state: HumiditySensorState = {
    id: 0,
    currentHumidityLvl: 0,
    humidityThreshold: 0,
    humidityActive: false
  }

  render() {
    return (
      <div>
        <TopBar />
        <HumiditySensor
          id={this.state.id} //
          currentHumidityLvl={this.state.currentHumidityLvl}
          humidityThreshold={this.state.humidityThreshold}
          humidityActive={this.state.humidityActive}
        />
        <Footer />
      </div>
    )
  }
}

export default App
