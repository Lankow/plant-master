/*
*   NetworkHandler.cpp
*   ----------------------
*   Created on: 2023/09/26
*   Author: Lankow
*/
#include "NetworkHandler.h"
#include "config.h"
#include "constants.h"

NetworkHandler::NetworkHandler(){
  m_server = WiFiServer(80);
};

void NetworkHandler::initWiFi() {
  uint8_t connectionCounter = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Connecting to SSID: %s \n", WIFI_SSID);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);

    connectionCounter++;

    if(connectionCounter >= MAX_CONNECTION_TRIES){
      Serial.println("Encountered error when connecting to WiFi... \n");
      return;
    }
  }

  IPAddress ip = WiFi.localIP();

  Serial.printf("WiFi Connected - IP Address: %u.%u.%u.%u \n", ip[0], ip[1], ip[2], ip[3]);
  updateTimeViaNTP();
  startServer();
};

void NetworkHandler::updateTimeViaNTP(){
  if(WiFi.status() == WL_CONNECTED){
    configTime(GMT_OFFSET, DAY_OFFSET, NTP_SERVER_PL_0, NTP_SERVER_PL_1, NTP_SERVER_PL_2);
  }
  else{
    Serial.println("WiFi connection not available - Time update is not possible...");
  }
};

void NetworkHandler::startServer(){
  
  if(NULL != &m_server){
    m_server.begin();
    Serial.print("Connect to IP Address: ");
    Serial.print("http://");
    Serial.println(WiFi.localIP());
  }
};

void NetworkHandler::handleClient(){
  m_client = m_server.available();
  
  if(!m_client) return;

  if(m_client.connected()){
    html();
  }
};

void NetworkHandler::html(){
  m_client.println("HTTP/1.1 200 OK");
  m_client.println("Content-Type: text/html");
  m_client.println("Connection: close");
  m_client.println();

  m_client.println("<!DOCTYPE HTML>");
  m_client.println("<html>");

  m_client.println("<head></head>");
  m_client.println("<body>");
  m_client.println("<h2>PLANT-MASTER</h2>");
  m_client.println("<p>To be reworked...</p>");
 
  m_client.println("</body>");
  m_client.println("</html>");    
}