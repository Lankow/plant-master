import React from "react";
import { Dialog } from "@mui/material";
import About from "./modals/About";
import Edit from "./modals/Edit";

interface ModalProps {
  open: boolean;
  openedModal: string;
  editedThreshold: number;
  setEditedThreshold: React.Dispatch<React.SetStateAction<number>>;
  handleCloseModal: () => void;
  handleSaveChanges: () => void;
}

const Modal: React.FC<ModalProps> = ({
  open,
  openedModal,
  editedThreshold,
  setEditedThreshold,
  handleCloseModal,
  handleSaveChanges,
}) => {
  return (
    <Dialog open={open} onClose={handleCloseModal}>
      {openedModal === "About" && <About handleCloseModal={handleCloseModal} />}
      {openedModal === "Edit" && (
        <Edit
          editedThreshold={editedThreshold}
          setEditedThreshold={setEditedThreshold}
          handleCloseModal={handleCloseModal}
          handleSaveChanges={handleSaveChanges}
        />
      )}
    </Dialog>
  );
};

export default Modal;