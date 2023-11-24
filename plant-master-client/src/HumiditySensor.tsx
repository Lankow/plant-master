import { Card, Grid, Typography } from "@mui/material"
import React from "react"

interface HumiditySensorProps {
  lvl: number
  threshold: number
  active: boolean
}

const HumiditySensor: React.FC<HumiditySensorProps> = ({ lvl, threshold, active }) => {
  return (
    <Grid item xs={6}>
      <Card sx={{ padding: 1.5 }}>
        <Typography sx={{ mb: 1 }} variant="h6">
          Humidity Sensor
        </Typography>
        <Typography sx={{ mb: 1 }}>Current Level: {lvl}</Typography>
        <Typography sx={{ mb: 1 }}>Threshold: {threshold}</Typography>
        <Typography sx={{ mb: 1 }}>Active: {active ? "Yes" : "No"}</Typography>
      </Card>
    </Grid>
  )
}

export default HumiditySensor
