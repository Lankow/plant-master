import React from "react";
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button, Slider } from "@mui/material";

interface EditProps {
  editedThreshold: number;
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>;
  handleCloseModal: () => void;
  handleSaveChanges: () => void;
}

const Edit: React.FC<EditProps> = ({
  editedThreshold,
  setEditedThreshold,
  handleCloseModal,
  handleSaveChanges,
}) => {

  const handleSliderChange = (_event: Event, value: number | number[]) => {
    setEditedThreshold(value as number);
  };

  return (
    <>
      <DialogTitle sx={{ ml: 1, mt: 2 }}>Edit Threshold</DialogTitle>
      <DialogContent sx={{ p: 4 }}>
        <DialogContentText sx={{ mb: 3 }}>
          Modify the values for the sensor below:
        </DialogContentText>
        <Slider
          value={(editedThreshold)}
          onChange={handleSliderChange}
          valueLabelDisplay="auto"
          valueLabelFormat={(value) => value.toString()}
          step={5}
          marks
          min={0}
          max={100}
        />
      </DialogContent>
      <DialogActions sx={{ mr: 3, mb: 2 }}>
        <Button onClick={handleCloseModal}>Cancel</Button>
        <Button onClick={handleSaveChanges} variant="contained">
          Save
        </Button>
      </DialogActions>
    </>
  );
};

export default Edit;
