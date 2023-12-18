import React from "react"
import { DialogTitle, DialogContent, DialogActions, Button, CircularProgress, Pagination, Link } from "@mui/material"

interface LogsContentProps {
  handleCloseModal: () => void
  files: string[]
}

const LogsContent: React.FC<LogsContentProps> = ({ handleCloseModal, files }) => {
  return (
    <>
      <DialogTitle>Logs</DialogTitle>
      <DialogContent>
        {files.length > 0 ? (
          <>
            {files.map((file, index) => (
              <Link key={index}>{file}</Link>
            ))}
          </>
        ) : (
          <CircularProgress />
        )}
        <Pagination count={5} />
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
