import React, { useCallback } from "react";
import { Card, Grid } from "@mui/material";
import SensorDetails from "./SensorDetails";
import EditButton from "./EditButton";

interface HumidityPanelProps {
  id: number;
  pin: number;
  humidity: number;
  threshold: number;
  activeReaderPin: number;
  handleOpenModal: (modal: string) => void;
  setEditedPin: React.Dispatch<React.SetStateAction<number>>;
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>;
}

const HumidityPanel: React.FC<HumidityPanelProps> = ({
  id,
  pin,
  humidity,
  threshold,
  activeReaderPin,
  handleOpenModal,
  setEditedPin,
  setEditedThreshold,
}) => {
  const handleEditSensor = useCallback(() => {
    setEditedPin(pin);
    setEditedThreshold(threshold);
    handleOpenModal("Edit");
  }, [pin, threshold, setEditedPin, setEditedThreshold, handleOpenModal]);

  const isActiveReader = pin === activeReaderPin;
  const cardStyles = {
    padding: 1.5,
    backgroundColor: isActiveReader ? '#4f824f' : '#fff',
    color: isActiveReader ? '#fff' : '#000',
  };

  return (
    <Grid item xs={12} md={6} xl={6}>
      <Card sx={cardStyles}>
        <SensorDetails id={id} pin={pin} humidity={humidity} threshold={threshold} />
        <EditButton onClick={handleEditSensor} />
      </Card>
    </Grid>
  );
};

export default HumidityPanel;