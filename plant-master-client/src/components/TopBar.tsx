// TopBar.tsx
import React, { useState } from "react";
import {
  AppBar,
  Box,
  Button,
  Container,
  Drawer,
  IconButton,
  Toolbar,
  Typography
} from "@mui/material";
import Menu from "@mui/icons-material/Menu";
import DrawerContent from "../components/drawer/DrawerContent";
import InfoChips from "../components/drawer/InfoChips";

interface TopBarProps {
  handleOpenModal: (modal: string) => void;
  roomTemperature: number;
  roomHumidity: number;
  waterPumpActive: boolean;
  activeReaderPin: number;
}

const TopBar: React.FC<TopBarProps> = ({
  handleOpenModal,
  roomTemperature,
  roomHumidity,
  waterPumpActive,
  activeReaderPin
}) => {
  const [drawerOpen, setDrawerOpen] = useState(false);

  const toggleDrawer = (open: boolean) => () => {
    setDrawerOpen(open);
  };

  return (
    <AppBar component="nav" position="static">
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1, textTransform: "uppercase" }}>
            Plant-Master
          </Typography>
          <Box sx={{ display: { xs: "none", md: "flex" }, alignItems: "center" }}>
            <InfoChips
              roomTemperature={roomTemperature}
              roomHumidity={roomHumidity}
              waterPumpActive={waterPumpActive}
              activeReaderPin={activeReaderPin}
            />
            <Button sx={{ color: "#fff" }} onClick={() => handleOpenModal("About")}>
              About
            </Button>
          </Box>
          <Box sx={{ display: { xs: "block", md: "none" } }}>
            <IconButton sx={{ color: "#fff" }} onClick={toggleDrawer(true)}>
              <Menu />
            </IconButton>
          </Box>
        </Toolbar>
      </Container>
      <Drawer anchor="right" open={drawerOpen} onClose={toggleDrawer(false)}>
        <DrawerContent
          roomTemperature={roomTemperature}
          roomHumidity={roomHumidity}
          waterPumpActive={waterPumpActive}
          activeReaderPin={activeReaderPin}
          handleOpenModal={handleOpenModal}
          toggleDrawer={toggleDrawer}
        />
      </Drawer>
    </AppBar>
  );
};

export default TopBar;
