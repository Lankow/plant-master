import React from "react"
import { Dialog, DialogTitle, DialogContent, DialogContentText, DialogActions, Button } from "@mui/material"

interface LogsModalProps {
  open: string
  handleCloseModal: () => void
}

const LogsModal: React.FC<LogsModalProps> = ({ open, handleCloseModal }) => {
  return (
    <>
      <Dialog open={open == "Logs"} onClose={handleCloseModal}>
        <DialogTitle>Logs</DialogTitle>
        <DialogContent>
          <DialogContentText>Logs TBD</DialogContentText>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleCloseModal} variant="contained">
            Close
          </Button>
        </DialogActions>
      </Dialog>
    </>
  )
}

export default LogsModal
