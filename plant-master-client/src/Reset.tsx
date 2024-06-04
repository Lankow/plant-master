import React from "react"
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button, Link } from "@mui/material"

interface ResetProps {
  handleCloseModal: () => void
}

const Reset: React.FC<ResetProps> = ({ handleCloseModal }) => {
  return (
    <>
      <DialogTitle>Reset Plant-Master</DialogTitle>
      <DialogContent>
        <DialogContentText>
          Do You really want to reset data saved on Your Plant-Master?
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <Link href={"/reset"}>
            <Button variant="contained">Confirm</Button>
        </Link>
        <Button variant="contained" onClick={handleCloseModal}>
          Close
        </Button>
      </DialogActions>
    </>
  )
}

export default Reset
