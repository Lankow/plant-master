import React from "react";
import { Box } from "@mui/material";
import ChipList from "./ChipList";

interface InfoChipsProps {
  roomTemperature: number;
  roomHumidity: number;
  waterPumpActive: boolean;
  activeReaderPin: number;
}

const InfoChips: React.FC<InfoChipsProps> = ({
  roomTemperature,
  roomHumidity,
  waterPumpActive,
  activeReaderPin
}) => {
  return (
    <Box sx={{ display: "flex", alignItems: "center", gap: 2 }}>
      <ChipList
        roomTemperature={roomTemperature}
        roomHumidity={roomHumidity}
        waterPumpActive={waterPumpActive}
        activeReaderPin={activeReaderPin}
        direction="row"
      />
    </Box>
  );
};

export default InfoChips;
