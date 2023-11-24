import React from "react"
import { Dialog, DialogTitle, DialogContent, DialogContentText, DialogActions, Button, TextField, Slider, Typography } from "@mui/material"

interface EditSensorModalProps {
  open: boolean
  editedThreshold: number
  editedPin: number
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>
  setEditedPin: React.Dispatch<React.SetStateAction<number>>
  handleClose: () => void
  handleSaveChanges: () => void
}

const EditSensorModal: React.FC<EditSensorModalProps> = ({
  open, //
  editedThreshold,
  editedPin,
  setEditedThreshold,
  setEditedPin,
  handleClose,
  handleSaveChanges
}) => {
  return (
    <Dialog open={open} onClose={handleClose}>
      <DialogTitle sx={{ ml: 1, mt: 2 }}>Edit Sensor</DialogTitle>
      <DialogContent sx={{ p: 4 }}>
        <DialogContentText sx={{ mb: 2 }}>Modify the values for the sensor below:</DialogContentText>
        <TextField
          label="New Pin" //
          variant="outlined"
          fullWidth
          sx={{ mb: 2 }}
          value={editedPin}
          onChange={e => setEditedPin(Number(e.target.value))}
        />
        <Typography gutterBottom sx={{ mt: 2 }}>
          New Threshold
        </Typography>
        <Slider
          value={editedThreshold} //
          onChange={(_event, value) => setEditedThreshold(value as number)}
          valueLabelDisplay="auto"
          valueLabelFormat={value => value.toString()}
          step={100}
          marks
          min={0}
          max={4000}
        />
      </DialogContent>
      <DialogActions sx={{ mr: 3, mb: 2 }}>
        <Button onClick={handleClose}>Cancel</Button>
        <Button onClick={handleSaveChanges} variant="contained">
          Save Changes
        </Button>
      </DialogActions>
    </Dialog>
  )
}

export default EditSensorModal
