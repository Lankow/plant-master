import React from "react"
import { Card, Grid, Typography } from "@mui/material"

interface HumidityPanelProps {
  id: number
  humidity: number
  threshold: number
}

const HumidityPanel: React.FC<HumidityPanelProps> = ({ id, humidity, threshold }) => {

  return (
    <Grid item xs={12} md={6} xl={6}>
      <Card sx={{ padding: 1.5 }}>
        <Typography sx={{ mb: 1 }} variant="h6">
          Humidity Sensor
        </Typography>
        <Typography sx={{ mb: 1 }}>HandlerId: {id != 0xff ? id : "Not Assigned"}</Typography>
        <Typography sx={{ mb: 1 }}>Current Humidity: {humidity}</Typography>
        <Typography sx={{ mb: 1 }}>Threshold: {threshold}</Typography>
      </Card>
    </Grid>
  )
}

export default HumidityPanel