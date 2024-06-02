import React from "react"
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button, Link } from "@mui/material"

interface ConnectMonitorProps {
  handleCloseModal: () => void
}

const ConnectMonitor: React.FC<ConnectMonitorProps> = ({ handleCloseModal }) => {
  return (
    <>
      <DialogTitle>Connect Monitor</DialogTitle>
      <DialogContent>
        <DialogContentText>
          In order to connect Plant-Monitor press button below and wait until proccess is complete.
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <Link href={"/connect"}>
            <Button variant="contained">Confirm</Button>
        </Link>
        <Button variant="contained" onClick={handleCloseModal}>
          Close
        </Button>
      </DialogActions>
    </>
  )
}

export default ConnectMonitor
