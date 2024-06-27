import React, { useCallback } from "react";
import { Card, Grid } from "@mui/material";
import SensorDetails from "./SensorDetails";
import EditButton from "./EditButton";

interface HumidityPanelProps {
  id: number;
  pin: number;
  humidity: number;
  threshold: number;
  handleOpenModal: (modal: string) => void;
  setEditedPin: React.Dispatch<React.SetStateAction<number>>;
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>;
}

const HumidityPanel: React.FC<HumidityPanelProps> = ({
  id,
  pin,
  humidity,
  threshold,
  handleOpenModal,
  setEditedPin,
  setEditedThreshold,
}) => {
  const handleEditSensor = useCallback(() => {
    setEditedPin(pin);
    setEditedThreshold(threshold);
    handleOpenModal("Edit");
  }, [pin, threshold, setEditedPin, setEditedThreshold, handleOpenModal]);

  return (
    <Grid item xs={12} md={6} xl={6}>
      <Card sx={{ padding: 1.5 }}>
        <SensorDetails id={id} pin={pin} humidity={humidity} threshold={threshold} />
        <EditButton onClick={handleEditSensor} />
      </Card>
    </Grid>
  );
};

export default HumidityPanel;