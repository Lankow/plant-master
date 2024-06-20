import { AppBar, Box, Button, Container, Toolbar, Typography } from "@mui/material"
import React from "react"

interface TopBarProps {
  handleOpenModal: (modal: string) => void
  roomTemperature: number
  roomHumidity: number
}

const TopBar: React.FC<TopBarProps> = ({ handleOpenModal, roomTemperature, roomHumidity }) => {
  return (
    <AppBar component="nav" position="static">
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1, display: { sm: "block", textTransform: "uppercase" } }}>
            Plant-Master
          </Typography>
          <Typography sx={{ mr: 1 }}>
            Room: {roomTemperature} °C / {roomHumidity} %
          </Typography>
          <Box sx={{ display: { sm: "block" } }}>
            <Button sx={{ color: "#fff" }} onClick={() => handleOpenModal("About")}>
              About
            </Button>
          </Box>
        </Toolbar>
      </Container>
    </AppBar>
  )
}

export default TopBar
