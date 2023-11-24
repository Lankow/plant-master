import React, { useState } from "react"
import { Button, Card, Grid, Typography } from "@mui/material"
import EditSensorModal from "./EditSensorModal"

interface HumiditySensorProps {
  lvl: number
  threshold: number
  active: boolean
}

const HumiditySensor: React.FC<HumiditySensorProps> = ({ lvl, threshold, active }) => {
  const [open, setOpen] = useState(false)
  const [editedThreshold, setEditedThreshold] = useState(4095)
  const [editedPin, setEditedPin] = useState(4095)

  const handleClickOpen = () => {
    setOpen(true)
  }

  const handleClose = () => {
    setOpen(false)
  }

  const handleSaveChanges = () => {
    // WebSocket Handling TBD
    setOpen(false)
  }

  return (
    <Grid item xs={12} md={6} xl={6}>
      <Card sx={{ padding: 1.5 }}>
        <Typography sx={{ mb: 1 }} variant="h6">
          Humidity Sensor
        </Typography>
        <Typography sx={{ mb: 1 }}>Current Level: {lvl}</Typography>
        <Typography sx={{ mb: 1 }}>Threshold: {threshold}</Typography>
        <Typography sx={{ mb: 1 }}>Active: {active ? "Yes" : "No"}</Typography>
        <Button variant="contained" onClick={handleClickOpen}>
          Edit Sensor
        </Button>

        <EditSensorModal
          open={open} //
          editedThreshold={editedThreshold}
          editedPin={editedPin}
          setEditedThreshold={setEditedThreshold}
          setEditedPin={setEditedPin}
          handleClose={handleClose}
          handleSaveChanges={handleSaveChanges}
        />
      </Card>
    </Grid>
  )
}

export default HumiditySensor
