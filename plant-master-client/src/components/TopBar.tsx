import React from "react";
import { AppBar, Box, Button, Container, Toolbar, Typography } from "@mui/material";

interface TopBarProps {
  handleOpenModal: (modal: string) => void;
  roomTemperature: number;
  roomHumidity: number;
  waterPumpActive: boolean;
  activeReaderPin: number;
}

const TopBar: React.FC<TopBarProps> = ({ handleOpenModal, roomTemperature, roomHumidity, waterPumpActive, activeReaderPin }) => {
  return (
    <AppBar component="nav" position="static">
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography
            variant="h6"
            component="div"
            sx={{ flexGrow: 1, display: { sm: "block" }, textTransform: "uppercase" }}
          >
            Plant-Master
          </Typography>
          <Typography sx={{ mr: 2 }}>
            Room: {roomTemperature} °C / {roomHumidity} %
          </Typography>
          <Typography sx={{ mr: 2 }}>
            Water Pump: {waterPumpActive ? "Active" : "Inactive"}
          </Typography>
          <Typography sx={{ mr: 2 }}>
            Active Reader Pin: {activeReaderPin}
          </Typography>
          <Box sx={{ display: { sm: "block" } }}>
            <Button sx={{ color: "#fff" }} onClick={() => handleOpenModal("About")}>
              About
            </Button>
          </Box>
        </Toolbar>
      </Container>
    </AppBar>
  );
};

export default TopBar;
