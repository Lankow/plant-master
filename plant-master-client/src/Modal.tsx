import React from "react"
import { Dialog } from "@mui/material"
import About from "./About"
import Reset from "./Reset"
import Edit from "./Edit"

interface ModalProps {
  open: boolean
  openedModal: string
  editedThreshold: number
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>
  handleCloseModal: () => void
  handleSaveChanges: () => void
}

const Modal: React.FC<ModalProps> = ({
  open, //
  openedModal,
  editedThreshold,
  setEditedThreshold,
  handleCloseModal,
  handleSaveChanges

}) => {
  const renderContent = () => {
    switch (openedModal) {
      case "Reset":
        return <Reset handleCloseModal={handleCloseModal} />
      case "About":
        return <About handleCloseModal={handleCloseModal} />
      case "Edit":
        return (
          <Edit //
            editedThreshold={editedThreshold}
            setEditedThreshold={setEditedThreshold}
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