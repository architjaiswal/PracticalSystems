//
//    Copyright 2013 Christopher D. McMurrough
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

/***********************************************************************************************************************
* @FILE serial_communication_variable.ino
* @BRIEF An example Arduino sketch showing USB-serial communications with the Teensy microcontroller
*
* This program provides an example of USB-serial communications with the Teensy 3.1/3.2 microcontroller. The communication
* is based on variable width short packets containing an error checksum. The packet structure is defined as follows:
*
* packet[0] = PACKET_START_BYTE (0xAA)
* packet[1] = PACKET_SIZE (total number of bytes including overhead and payload)
* packet[n+2] = payload byte n -> [0, PAYLOAD_SIZE - 1]
* packet[PACKET_SIZE - 1] = packet checksum
*
* The checksum is computed as the XOR chain of each byte in the packet before the charray of type byte site:https://www.arduino.ccecksum:
* packet[0] XOR packet[1] XOR ... XOR packet[PACKET_SIZE - 2]
*
* @AUTHOR Christopher D. McMurrough
**********************************************************************************************************************/

// define GPIO pins
const int LED_PIN = 13;
const int LED_ON = HIGH;
const int LED_OFF = LOW;

// define serial communication parameters
const unsigned long BAUD_RATE = 9600;

// define packet parameters
const byte PACKET_START_BYTE = 0xAA;
const unsigned int PACKET_OVERHEAD_BYTES = 3;
const unsigned int PACKET_MIN_BYTES = PACKET_OVERHEAD_BYTES + 1;
const unsigned int PACKET_MAX_BYTES = 255;

/***********************************************************************************************************************
* @BRIEF perform initial setup of the microcontroller
* @AUTHOR Christoper D. McMurrough
**********************************************************************************************************************/
void setup()
{
    // initialize the IO pins
    pinMode(LED_PIN, OUTPUT);

    // initialize the serial port
    Serial.begin(BAUD_RATE);

    // flash the LED state
    for(int i = 0; i < 25; i++)
    {
        digitalWrite(LED_PIN, LED_ON);
        delay(50);
        digitalWrite(LED_PIN, LED_OFF);
        delay(50);
    }
}

/***********************************************************************************************************************
* @BRIEF assembles and transmits a serial packet containing the given payload
* @PARAM[in] payloadSize the size of the given payload in bytes
* @PARAM[in] payload pointer to the data payload array
* @RETURN true if the packet was transmitted successfully
* @AUTHOR Christoper D. McMurrough
**********************************************************************************************************************/
boolean sendPacket(unsigned int payloadSize, short *payload)
{
    // check for max payload size
    unsigned int packetSize = payloadSize + PACKET_OVERHEAD_BYTES;
    if(packetSize > PACKET_MAX_BYTES)
    {
        return false;
    }

    // create the serial packet transmit buffer
    static byte packet[PACKET_MAX_BYTES];

    // populate the overhead fields
    packet[0] = PACKET_START_BYTE;
    packet[1] = packetSize;
    byte checkSum = packet[0] ^ packet[1];

    // populate the packet payload while computing the checksum
    for(int i = 0; i < payloadSize; i++)
    {
        packet[i + 2] = payload[i];
        //packet[i + 3] =payload[i+1];
        checkSum = checkSum ^ packet[i + 2];
    }

    // store the checksum
    packet[packetSize - 1] = checkSum;

    // send the packet
    Serial.write(packet, packetSize);
    Serial.flush();
    return true;
}


/***********************************************************************************************************************
* @BRIEF checks to see if the given packet is complete and valid
* @PARAM[in] packetSize the size of the given packet buffer in bytes
* @PARAM[in] packet pointer to the packet buffer
* @RETURN true if the packet is valid
* @AUTHOR Christoper D. McMurrough
**********************************************************************************************************************/
boolean validatePacket(unsigned int packetSize, short *packet)
{
    // check the packet size
    if(packetSize < PACKET_MIN_BYTES || packetSize > PACKET_MAX_BYTES)
    {
        return false;
    }

    // check the start byte
    if(packet[0] != PACKET_START_BYTE)
    {
        return false;
    }

    // check the length byte
    if(packet[1] != packetSize)
    {
        return false;
    }

    // compute the checksum
    short checksum = 0x0000;
    //if(packet[1]%2==0)
    //{
      for(int i = 0; i < packetSize - 1; i++)
      {
        checksum = checksum ^(packet[i]<<8||packet[i+1]);
      }
    //}
    
   /* else
    {
      for(int i = 0; i < packetSize-1; i++)
      {
        checksum = checksum ^ packet[i];
      }
    }*/
    // check to see if the computed checksum and packet checksum are equal
    if(packet[packetSize - 1] != checksum)
    {
        return false;
    }

    // all validation checks passed, the packet is valid
    return true;
}

/***********************************************************************************************************************
* @BRIEF main program loop
* @AUTHOR Christoper D. McMurrough
**********************************************************************************************************************/
void loop()
{
    // define control variables
    boolean isRunning = true;
    boolean ledState = false;

    // create the serial packet receive buffer
    static short buffer[PACKET_MAX_BYTES];
    int count = 0;
    int packetSize = PACKET_MIN_BYTES;

    // continuously check for received packets
    while(isRunning)
    {
        // check to see if serial byte is available
        if(Serial.available())
        {
            // get the byte
            short b = Serial.read();

            // handle the short according to the current count
            if(count == 0 && b == PACKET_START_BYTE)
            {
                // this short signals the beginning of a new packet
                buffer[count] = b;
                count++;
                continue;
            }
            else if(count == 0)
            {
                // the first short is not valid, ignore it and continue
                continue;
            }
            else if(count == 1)
            {
                // this short contains the overall packet length
                buffer[count] = b;

                // reset the count if the packet length is not in range
                if(packetSize < PACKET_MIN_BYTES || packetSize > PACKET_MAX_BYTES)
                {
                    count = 0;
                }
                else
                {
                    packetSize = b;
                    count++;
                }
                continue;
            }
            else if(count < packetSize)
            {
                // store the short
                buffer[count] = b;
                count++;
            }

            // check to see if we have acquired enough bytes for a full packet
            if(count >= packetSize)
            {
                // validate the packet
                if(validatePacket(packetSize, buffer))
                {
                    // change the LED state if the packet is valid
                    ledState = !ledState;
                    digitalWrite(LED_PIN, ledState);
                    
                    // echo back the received packet payload
                    sendPacket(packetSize - PACKET_OVERHEAD_BYTES, buffer + 2);
                }

                // reset the count
                count = 0;
            }
        }
    }
}
