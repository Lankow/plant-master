import React, { useCallback } from "react"
import { Button, Card, Grid, Typography } from "@mui/material"

interface HumiditySensorProps {
  id: number
  lvl: number
  threshold: number
  active: boolean
  handleOpenModal: (modal: string) => void
  setEditedId: React.Dispatch<React.SetStateAction<number>>
}

const HumiditySensor: React.FC<HumiditySensorProps> = ({ id, lvl, threshold, active, handleOpenModal, setEditedId }) => {
  const handleEditSensor = useCallback(
    (sensorId: number) => {
      setEditedId(sensorId)
      handleOpenModal("Edit")
    },
    [handleOpenModal, setEditedId]
  )
  return (
    <Grid item xs={12} md={6} xl={6}>
      <Card sx={{ padding: 1.5 }}>
        <Typography sx={{ mb: 1 }} variant="h6">
          Humidity Sensor
        </Typography>
        <Typography sx={{ mb: 1 }}>HandlerId: {id != 0xff ? id : "Not Assigned"}</Typography>
        <Typography sx={{ mb: 1 }}>Current Level: {lvl}</Typography>
        <Typography sx={{ mb: 1 }}>Threshold: {threshold}</Typography>
        <Typography sx={{ mb: 1 }}>Active: {active ? "Yes" : "No"}</Typography>
        <Button variant="contained" onClick={() => handleEditSensor(id)}>
          Edit Sensor
        </Button>
      </Card>
    </Grid>
  )
}

export default HumiditySensor
