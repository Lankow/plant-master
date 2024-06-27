import React from "react";
import { Button } from "@mui/material";

interface EditButtonProps {
  onClick: () => void;
}

const EditButton: React.FC<EditButtonProps> = ({ onClick }) => (
  <Button variant="contained" onClick={onClick}>
    Edit Threshold
  </Button>
);

export default EditButton;