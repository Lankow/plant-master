import React from "react";
import { Typography, Box } from "@mui/material";

const Footer: React.FC = () => {
  return (
    <Box component="footer" sx={{ py: 2 }}>
      <Typography variant="h6" align="center" color="white" sx={{ minHeight: "10vh" }}>
        Plant-Master by Lankow © 2023
      </Typography>
    </Box>
  );
};

export default Footer;