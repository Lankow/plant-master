import React from "react";
import { DialogTitle, DialogContent, DialogContentText, DialogActions, Button, Link, Typography, Divider } from "@mui/material";

interface AboutContentProps {
  handleCloseModal: () => void;
}

const About: React.FC<AboutContentProps> = ({ handleCloseModal }) => {
  return (
    <>
      <DialogTitle>About Plant-Master</DialogTitle>
      <Divider flexItem/>
      <DialogContent>
        <DialogContentText>
          <Typography variant="h6" gutterBottom>
            Overview
          </Typography>
          <Typography paragraph>
            Plant-Master is an innovative application designed to help you monitor and maintain the optimal conditions for your plants. Whether you are a professional horticulturist or a home gardener, Plant-Master provides the tools you need to ensure your plants thrive.
          </Typography>
          <Typography paragraph>
            Visit the project repository on{" "}
            <Link href="https://github.com/Lankow/plant-master" target="_blank" rel="noopener">
              Github
            </Link>{" "}
            to learn more.
          </Typography>
          <Typography variant="h6" gutterBottom>
            Features
          </Typography>
          <Typography paragraph>
            <ul>
              <li>Real-time monitoring of room temperature and humidity.</li>
              <li>Automatic control of water pump based on soil moisture levels.</li>
              <li>Customizable thresholds for alerts and actions.</li>
              <li>Easy-to-use interface for setting up and managing your plant environment.</li>
              <li>Supports multiple sensors and devices for comprehensive monitoring.</li>
            </ul>
          </Typography>

          <Typography variant="h6" gutterBottom>
            Technology
          </Typography>
          <Typography paragraph>
            Plant-Master leverages modern web technologies and hardware integration to provide seamless monitoring and control:
            <ul>
              <li>React and Material-UI for a responsive and user-friendly interface.</li>
              <li>WebSockets for real-time data updates.</li>
              <li>Integration with various sensors for temperature, humidity, and soil moisture.</li>
            </ul>
          </Typography>
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <Button variant="contained" onClick={handleCloseModal}>
          Close
        </Button>
      </DialogActions>
    </>
  );
};

export default About;
