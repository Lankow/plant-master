// Modal.tsx

import React from "react"
import { Dialog } from "@mui/material"
import LogsContent from "./LogsContent"
import AboutContent from "./AboutContent"
import EditSensorContent from "./EditSensorContent"

interface ModalProps {
  open: boolean
  openedModal: string
  editedPin: number
  editedThreshold: number
  setEditedPin: React.Dispatch<React.SetStateAction<number>>
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>
  handleCloseModal: () => void
  handleSaveChanges: () => void
  logFiles: string[]
}

const Modal: React.FC<ModalProps> = ({
  open, //
  openedModal,
  editedPin,
  editedThreshold,
  setEditedPin,
  setEditedThreshold,
  handleCloseModal,
  handleSaveChanges,
  logFiles
}) => {
  const renderContent = () => {
    switch (openedModal) {
      case "Logs":
        return <LogsContent files={logFiles} handleCloseModal={handleCloseModal} />
      case "About":
        return <AboutContent handleCloseModal={handleCloseModal} />
      case "Edit":
        return (
          <EditSensorContent //
            editedThreshold={editedThreshold}
            editedPin={editedPin}
            setEditedThreshold={setEditedThreshold}
            setEditedPin={setEditedPin}
            handleCloseModal={handleCloseModal}
            handleSaveChanges={handleSaveChanges}
          />
        )
      default:
        return null
    }
  }

  return (
    <Dialog open={open} onClose={handleCloseModal}>
      {renderContent()}
    </Dialog>
  )
}

export default Modal
