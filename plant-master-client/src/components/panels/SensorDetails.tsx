import React from "react";
import { Typography, Divider } from "@mui/material";

interface SensorDetailsProps {
  id: number;
  pin: number;
  humidity: number;
  threshold: number;
}
 
const SensorDetails: React.FC<SensorDetailsProps> = ({ id, pin, humidity, threshold }) => (
  <>
    <Typography sx={{ mb: 1}} variant="h6">
      Humidity Data ID: {id !== 0xff ? id : "Not Assigned"}
    </Typography>
    <Divider flexItem sx={{ mb: 1 }} />
    <Typography sx={{ mb: 1 }}>Assigned Pin: {pin}</Typography>
    <Typography sx={{ mb: 1 }}>
        Current Humidity: {humidity > 4000 ? "INACTIVE" : `${(humidity / 40).toFixed(1)} %`}
    </Typography>
    <Typography sx={{ mb: 1 }}>Threshold: {(threshold/40).toFixed(1)} %</Typography>
    <Divider flexItem sx={{ mb: 2 }} />
  </>
);

export default SensorDetails;