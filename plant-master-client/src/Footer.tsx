import { Typography } from "@mui/material"
import React from "react"

export const Footer: React.FC = () => {
  return (
    <footer>
      <Typography variant="h6" align="center" color="textSecondary" component="p" sx={{ p: 1 }}>
        Plant-Master by Lankow © 2023
      </Typography>
    </footer>
  )
}
