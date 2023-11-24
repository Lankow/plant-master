import React from "react"
import { Dialog, DialogTitle, DialogContent, DialogContentText, DialogActions, Button } from "@mui/material"

interface LogsModalProps {
  open: boolean
  handleClose: () => void
}

const LogsModal: React.FC<LogsModalProps> = ({ open, handleClose }) => {
  return (
    <>
      {/* Modal for displaying logs */}
      <Dialog open={open} onClose={handleClose}>
        <DialogTitle>Logs</DialogTitle>
        <DialogContent>
          <DialogContentText>Logs TBD</DialogContentText>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose} variant="contained">
            Close
          </Button>
        </DialogActions>
      </Dialog>
    </>
  )
}

export default LogsModal
