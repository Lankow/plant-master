import { AppBar, Box, Button, Container, Toolbar, Typography } from "@mui/material"
import React from "react"

export const TopBar: React.FC = () => {
  return (
    <AppBar component="nav" position="static">
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography variant="h6" component="div" sx={{ flexGrow: 1, display: { xs: "none", sm: "block" } }}>
            Plant-Master
          </Typography>
          <Box sx={{ display: { xs: "none", sm: "block" } }}>
            <Button sx={{ color: "#fff" }}>Get Logs</Button>
          </Box>
        </Toolbar>
      </Container>
    </AppBar>
  )
}
