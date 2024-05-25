import React from "react"
import { DialogTitle, DialogContent, DialogActions, Button, CircularProgress, Pagination, Link } from "@mui/material"

const logsPerPage = 10

interface LogsContentProps {
  handleCloseModal: () => void
  files: string[]
  logCount: number
}

const LogsContent: React.FC<LogsContentProps> = ({ handleCloseModal, files, logCount }) => {
  return (
    <>
      <DialogTitle>Logs</DialogTitle>
      <DialogContent>
        {files.length > 0 ? (
          <>
            {files.map((file, index) => (
              <Link key={index}>{file}</Link>
            ))}
            <Pagination count={logCount / logsPerPage} />
          </>
        ) : (
          <CircularProgress />
        )}
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
