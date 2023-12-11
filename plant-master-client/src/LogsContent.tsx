import React from "react"
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button } from "@mui/material"

interface LogsContentProps {
  handleCloseModal: () => void
}

const LogsContent: React.FC<LogsContentProps> = ({ handleCloseModal }) => {
  return (
    <>
      <DialogTitle>Logs</DialogTitle>
    </>
  )
}

export default LogsContent
