import React from "react"
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button, Link } from "@mui/material"

interface AboutContentProps {
  handleCloseModal: () => void
}

const AboutContent: React.FC<AboutContentProps> = ({ handleCloseModal }) => {
  return (
    <>
      <DialogTitle>About Plant-Master</DialogTitle>
      <DialogContent>
        <DialogContentText>
          Visit my{" "}
          <Link href="https://github.com/Lankow/plant-master" target="_blank">
            Github
          </Link>
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
