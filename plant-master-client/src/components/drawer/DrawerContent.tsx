import React from "react";
import { Box, List, ListItem, Button } from "@mui/material";
import ChipList from "./ChipList";

interface DrawerContentProps {
  roomTemperature: number;
  roomHumidity: number;
  waterPumpActive: boolean;
  activeReaderPin: number;
  handleOpenModal: (modal: string) => void;
  toggleDrawer: (open: boolean) => () => void;
}

const DrawerContent: React.FC<DrawerContentProps> = ({
  roomTemperature,
  roomHumidity,
  waterPumpActive,
  activeReaderPin,
  handleOpenModal,
  toggleDrawer
}) => {
  return (
    <Box sx={{ width: 250, height: "100vh", background: "#8ebeed" }} onClick={toggleDrawer(false)} onKeyDown={toggleDrawer(false)}>
      <List>
        <ListItem>
          <ChipList
            roomTemperature={roomTemperature}
            roomHumidity={roomHumidity}
            waterPumpActive={waterPumpActive}
            activeReaderPin={activeReaderPin}
            direction="column"
          />
        </ListItem>
        <ListItem>
          <Button variant="contained" fullWidth onClick={() => handleOpenModal("About")}>
            About
          </Button>
        </ListItem>
        <ListItem>
          <Button variant="contained" fullWidth onClick={toggleDrawer(false)}>
            Close
          </Button>
        </ListItem>
      </List>
    </Box>
  );
};

export default DrawerContent;
