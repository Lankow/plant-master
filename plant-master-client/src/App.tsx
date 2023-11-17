import { Footer } from "./Footer"
import { HumiditySensor } from "./HumiditySensor"
import { TopBar } from "./TopBar"

function App() {
  return (
    <div>
      <TopBar />
      <HumiditySensor id={0} currentHumidityLvl={0} humidityThreshold={0} humidityActive={false} />
      <HumiditySensor id={1} currentHumidityLvl={0} humidityThreshold={0} humidityActive={false} />
      <HumiditySensor id={2} currentHumidityLvl={0} humidityThreshold={0} humidityActive={false} />
      <HumiditySensor id={3} currentHumidityLvl={0} humidityThreshold={0} humidityActive={false} />
      <Footer />
    </div>
  )
}

export default App
