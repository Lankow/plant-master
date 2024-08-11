// ChipList.tsx
import React from "react";
import { Box, Chip } from "@mui/material";

interface ChipListProps {
  roomTemperature: number;
  roomHumidity: number;
  waterPumpActive: boolean;
  activeReaderPin: number;
  direction: 'row' | 'column';
}

const ChipList: React.FC<ChipListProps> = ({
  roomTemperature,
  roomHumidity,
  waterPumpActive,
  activeReaderPin,
  direction
}) => {
  return (
    <Box sx={{ display: "flex", flexDirection: direction, width: '100%', gap: 2 }}>
      <Chip label={`Temperature: ${roomTemperature.toFixed(1)} °C`} sx={{ color: '#fff' }} />
      <Chip label={`Humidity: ${roomHumidity.toFixed(1)} %`} sx={{ color: '#fff' }} />
      <Chip label={`Water Pump: ${waterPumpActive ? "Active" : "Inactive"}`} sx={{ color: '#fff' }} />
      <Chip label={`Active Reader Pin: ${activeReaderPin != 0 ? activeReaderPin : "None"}`} sx={{ color: '#fff' }} />
    </Box>
  );
};

export default ChipList;