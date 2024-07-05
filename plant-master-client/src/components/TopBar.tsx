import React, { useState } from "react";
import {
  AppBar,
  Box,
  Button,
  Container,
  Drawer,
  IconButton,
  Toolbar,
  Typography,
  List,
  ListItem,
  Chip
} from "@mui/material";
import Menu from "@mui/icons-material/Menu";

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

  const drawerList = () => (
    <Box sx={{ width: 250 }} onClick={toggleDrawer(false)} onKeyDown={toggleDrawer(false)}>
      <List>
        <ListItem>
          <Chip label={`Temperature: ${roomTemperature.toFixed(1)} °C`} sx={{ mb: 1, width: '100%' }} />
        </ListItem>
        <ListItem>
          <Chip label={`Humidity: ${roomHumidity.toFixed(1)} %`} sx={{ mb: 1, width: '100%' }} />
        </ListItem>
        <ListItem>
          <Chip label={`Water Pump: ${waterPumpActive ? "Active" : "Inactive"}`} sx={{ mb: 1, width: '100%' }} />
        </ListItem>
        <ListItem>
          <Chip label={`Active Reader Pin: ${activeReaderPin}`} sx={{ mb: 1, width: '100%' }} />
        </ListItem>
        <ListItem>
          <Button variant="contained" fullWidth onClick={() => handleOpenModal("About")}>
            About
          </Button>
        </ListItem>
        <ListItem>
          <Button variant="outlined" fullWidth onClick={toggleDrawer(false)}>
            Close
          </Button>
        </ListItem>
      </List>
    </Box>
  );

  return (
    <AppBar component="nav" position="static">
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1, textTransform: "uppercase" }}>
            Plant-Master
          </Typography>
          <Box sx={{ display: { xs: "none", md: "flex" }, alignItems: "center" }}>
            <Chip label={`Temperature: ${roomTemperature.toFixed(1)} °C`} sx={{ mr: 2, color: 'white' }} />
            <Chip label={`Humidity: ${roomHumidity.toFixed(1)} %`} sx={{ mr: 2, color: 'white' }} />
            <Chip label={`Water Pump: ${waterPumpActive ? "Active" : "Inactive"}`} sx={{ mr: 2, color: 'white' }} />
            <Chip label={`Active Reader Pin: ${activeReaderPin}`} sx={{ mr: 2, color: 'white' }} />
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
        {drawerList()}
      </Drawer>
    </AppBar>
  );
};

export default TopBar;
