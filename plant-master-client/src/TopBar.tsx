import { AppBar, Box, Button, Container, Toolbar, Typography } from "@mui/material"
import React from "react"

interface TopBarProps {
}

const TopBar: React.FC<TopBarProps> = () => {
  return (
    <AppBar component="nav" position="static">
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1, display: { sm: "block", textTransform: "uppercase" } }}>
            Plant-Master
          </Typography>
          <Box sx={{ display: { sm: "block" } }}>
            <Button sx={{ color: "#fff" }}>
              About
            </Button>
            <Button sx={{ color: "#fff" }}>
              Get Logs
            </Button>
          </Box>
        </Toolbar>
      </Container>
    </AppBar>
  )
}

export default TopBar
