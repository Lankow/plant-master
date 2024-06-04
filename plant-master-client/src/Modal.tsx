import React from "react"
import { Dialog } from "@mui/material"
import About from "./About"
import Reset from "./Reset"

interface ModalProps {
  open: boolean
  openedModal: string
  handleCloseModal: () => void
}

const Modal: React.FC<ModalProps> = ({
  open, //
  openedModal,
  handleCloseModal

}) => {
  const renderContent = () => {
    switch (openedModal) {
      case "Reset":
        return <Reset handleCloseModal={handleCloseModal} />
      case "About":
        return <About handleCloseModal={handleCloseModal} />
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