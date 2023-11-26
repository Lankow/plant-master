import React from "react"
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button, Typography, Link } from "@mui/material"

interface AboutContentProps {
  handleCloseModal: () => void
}

const AboutContent: React.FC<AboutContentProps> = ({ handleCloseModal }) => {
  return (
    <>
      <DialogTitle>About Plant-Master</DialogTitle>
      <DialogContent>
        <DialogContentText>
          <Typography>
            Visit my{" "}
            <Link href="https://github.com/Lankow/plant-master" target="_blank">
              Github
            </Link>
          </Typography>
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <Button variant="contained" onClick={handleCloseModal}>
          Close
        </Button>
      </DialogActions>
    </>
  )
}

export default AboutContent
