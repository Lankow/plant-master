import { AppBar, Box, Button, Container, Toolbar, Typography } from "@mui/material"
import React from "react"

interface TopBarProps {
  handleOpenModal: (modal: string) => void
  handleGetLogs: () => void
}

const TopBar: React.FC<TopBarProps> = ({ handleOpenModal, handleGetLogs }) => {
  return (
    <AppBar component="nav" position="static">
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1, display: { sm: "block", textTransform: "uppercase" } }}>
            Plant-Master
          </Typography>
          <Box sx={{ display: { sm: "block" } }}>
            <Button sx={{ color: "#fff" }} onClick={() => handleOpenModal("About")}>
              About
            </Button>
            <Button sx={{ color: "#fff" }} onClick={() => handleGetLogs()}>
              Get Logs
            </Button>
          </Box>
        </Toolbar>
      </Container>
    </AppBar>
  )
}

export default TopBar
