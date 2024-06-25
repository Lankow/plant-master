import React, { useCallback } from "react"
import { Card, Grid, Typography, Button, Divider } from "@mui/material"

interface HumidityPanelProps {
  id: number,
  pin: number
  humidity: number
  threshold: number,
  handleOpenModal: (modal: string) => void,
  setEditedPin: React.Dispatch<React.SetStateAction<number>>,
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>
}

const HumidityPanel: React.FC<HumidityPanelProps> = ({ id, pin, humidity, threshold, handleOpenModal, setEditedPin, setEditedThreshold }) => {

  const handleEditSensor = useCallback(
    (pin: number, threshold: number ) => {
      setEditedPin(pin)
      setEditedThreshold(threshold)
      handleOpenModal("Edit")
    },
    [handleOpenModal, setEditedPin, setEditedThreshold]
  )

  return (
    <Grid item xs={12} md={6} xl={6}>
      <Card sx={{ padding: 1.5 }}>
        <Typography sx={{ mb: 1 }} variant="h6">Humidity Data ID: {id != 0xff ? id : "Not Assigned"}</Typography>
        <Divider flexItem sx={{ mb: 1 }}/>
        <Typography sx={{ mb: 1 }}>Assigned Pin: {pin}</Typography>
        <Typography sx={{ mb: 1 }}>Current Humidity: {humidity}</Typography>
        <Typography sx={{ mb: 1 }}>Threshold: {threshold}</Typography>
        <Divider flexItem sx={{ mb: 2 }}/>
        <Button variant="contained" onClick={() => handleEditSensor(pin, threshold)}>
          Edit Threshold
        </Button>
      </Card>
    </Grid>
  )
}

export default HumidityPanel