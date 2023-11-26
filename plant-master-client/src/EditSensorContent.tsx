import React from "react"
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button, TextField, Slider, Typography } from "@mui/material"

interface EditSensorContentProps {
  editedThreshold: number
  editedPin: number
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>
  setEditedPin: React.Dispatch<React.SetStateAction<number>>
  handleCloseModal: () => void
  handleSaveChanges: () => void
}

const EditSensorContent: React.FC<EditSensorContentProps> = ({ editedThreshold, editedPin, setEditedThreshold, setEditedPin, handleCloseModal, handleSaveChanges }) => {
  return (
    <>
      <DialogTitle sx={{ ml: 1, mt: 2 }}>Edit Sensor</DialogTitle>
      <DialogContent sx={{ p: 4 }}>
        <DialogContentText sx={{ mb: 2 }}>Modify the values for the sensor below:</DialogContentText>
        <TextField label="New Pin" variant="outlined" fullWidth sx={{ mb: 2 }} value={editedPin} onChange={e => setEditedPin(Number(e.target.value))} />
        <Typography gutterBottom sx={{ mt: 2 }}>
          New Threshold
        </Typography>
        <Slider value={editedThreshold} onChange={(_event, value) => setEditedThreshold(value as number)} valueLabelDisplay="auto" valueLabelFormat={value => value.toString()} step={100} marks min={0} max={4000} />
      </DialogContent>
      <DialogActions sx={{ mr: 3, mb: 2 }}>
        <Button onClick={handleCloseModal}>Cancel</Button>
        <Button onClick={handleSaveChanges} variant="contained">
          Save Changes
        </Button>
      </DialogActions>
    </>
  )
}

export default EditSensorContent
