import { AppBar, Box, Button, Container, Toolbar, Typography } from "@mui/material"
import React, { useState } from "react"
import LogsModal from "./LogsModal"

export const TopBar: React.FC = () => {
  const [open, setOpen] = useState(false)

  const fetchLogs = () => {
    console.log("Fetching logs...")
  }

  const handleClickOpen = () => {
    fetchLogs()
    setOpen(true)
  }

  const handleClose = () => {
    setOpen(false)
  }
  return (
    <AppBar component="nav" position="static">
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1, display: { sm: "block", textTransform: "uppercase" } }}>
            Plant-Master
          </Typography>
          <Box sx={{ display: { sm: "block" } }}>
            <Button sx={{ color: "#fff" }} onClick={handleClickOpen}>
              Get Logs
            </Button>
          </Box>
        </Toolbar>

        <LogsModal open={open} handleClose={handleClose} />
      </Container>
    </AppBar>
  )
}
