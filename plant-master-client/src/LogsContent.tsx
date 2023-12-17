import React from "react"
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button } from "@mui/material"

interface LogsContentProps {
  handleCloseModal: () => void
  files: string[]
  count: number
  currentPage: number
}

const LogsContent: React.FC<LogsContentProps> = ({ handleCloseModal }) => {
  return (
    <>
      <DialogTitle>Logs</DialogTitle>
      <DialogContent>
        <DialogContentText>Logs TBD</DialogContentText>
      </DialogContent>
      <DialogActions>
        <Button variant="contained" onClick={handleCloseModal}>
          Close
        </Button>
      </DialogActions>
    </>
  )
}

export default LogsContent
