
#include <Arduino.h>

#include "slcan_serial.h"
#include "can_adapter_mcp2515.hpp"

SlcanLineReader *slcanLineReader = NULL;
MCP2515Adapter *can_adapter = NULL;
MCP2515 mcp2515(10);
struct can_frame canMsg;
bool mode = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }
  mcp2515.reset();
  can_adapter = new MCP2515Adapter(&mcp2515, CAN_CLOCK::MCP_8MHZ, &Serial);
  slcanLineReader = new SlcanLineReader(&Serial, can_adapter);
}

void loop()
{

  if (slcanLineReader->isCANOpened())
  {
    can_adapter->read_and_transmit(&canMsg);
  }
  slcanLineReader->ProcessSerial();
}
