//
//    Copyright 2016 Christopher D. McMurrough
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
* @FILE multicolor_led.ino
* @BRIEF An example Arduino sketch showing dimmer control of a multicolor LED
* @AUTHOR Christopher D. McMurrough
**********************************************************************************************************************/

// define onobard LED pins
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



// define potentiometer pins
const int POT_PIN = 14;

/***********************************************************************************************************************
* @BRIEF perform initial setup of the microcontroller
* @AUTHOR Christoper D. McMurrough
**********************************************************************************************************************/
void setup()
{ 
    // flash the onboard LED state
    for(int i = 0; i < 25; i++)
    {
        digitalWrite(LED_PIN, LED_ON);
        delay(50);
        digitalWrite(LED_PIN, LED_OFF);
        delay(50);
    }

    // start serial communication at 9600 bps
    Serial.begin(9600);
}

boolean sendPacket(unsigned int payloadSize, byte *payload)
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
        checkSum = checkSum ^ packet[i + 2];
    }

    // store the checksum
    packet[packetSize - 1] = checkSum;

    // send the packet
    Serial.write(packet, packetSize);
    Serial.flush();
    return true;
}


boolean validatePacket(unsigned int packetSize, byte *packet)
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
    byte checksum = 0x00;
    for(int i = 0; i < packetSize - 1; i++)
    {
        checksum = checksum ^ packet[i];
    }

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
  setup();
  boolean isRunning = true;
    boolean ledState = false;

    // create the serial packet receive buffer
    static byte buffer[PACKET_MAX_BYTES];
    int count = 0;
    int packetSize = PACKET_MIN_BYTES;
    
while(isRunning)
    {
      
        // check to see if serial byte is available
        if(Serial.available())
        {
            // get the byte
            byte b = Serial.read();

            if(count == 0 && b == PACKET_START_BYTE)
            {
                // this byte signals the beginning of a new packet
                buffer[count] = b;
                count++;
                continue;
            }
            else if(count == 0)
            {
                // the first byte is not valid, ignore it and continue
                continue;
            }
            else if(count == 1)
            {
                // this byte contains the overall packet length
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
                // store the byte
                buffer[count] = b;
                count++;
            }

            // handle the byte according to the current count
            
            //Serial.write(buffer, 5);
            //Serial.flush();
            //sendPacket(packetSize - PACKET_OVERHEAD_BYTES, buffer + 2);
           if(count >= packetSize)
           
            {
                // validate the packet
                if(validatePacket(packetSize, buffer))
                {
                    // change the LED state if the packet is valid
                    ledState = !ledState;
                    digitalWrite(LED_PIN, ledState);

                    if(buffer[2] == 0x50)
                    {
                        // this byte signals the beginning of a new packet
                        int potValue = analogRead(POT_PIN);
                        //Serial.println(potValue);
                        /////////
                        buffer[3]= (byte)potValue/4;
                        buffer[4] = buffer[0] ^buffer[1] ^buffer[2] ^buffer[3];
                        sendPacket(packetSize - PACKET_OVERHEAD_BYTES, buffer + 2);
                        //buffer[4]=validatePacket(packetSize, buffer);     
                        count=0;         
                    }
            
                    // echo back the received packet payload
                    
                }
            
                
           }       
            
        }
/*
        ///////////////////////////////////////////////////////////////
        // check to see if serial byte is available
        if(Serial.available())
        {
            // get the byte
            byte b = Serial.read();

            // handle the byte according to the current count
            if(count == 0 && b == PACKET_START_BYTE)
            {
                // this byte signals the beginning of a new packet
                buffer[count] = b;
                count++;
                continue;
            }
            else if(count == 0)
            {
                // the first byte is not valid, ignore it and continue
                continue;
            }
            else if(count == 1)
            {
                // this byte contains the overall packet length
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
                // store the byte
                buffer[count] = b;
                count++;
            }


            // check to see if we have acquired enough bytes for a full packet
            if(buffer[2] == 0x50)
            {
            
            if(count >= packetSize)
            {
                // validate the packet
                if(validatePacket(packetSize, buffer))
                {
                    // change the LED state if the packet is valid
                    ledState = !ledState;
                    digitalWrite(LED_PIN, ledState);
                    buffer[3]=potValue/4;
                    // echo back the received packet payload
                    sendPacket(packetSize - PACKET_OVERHEAD_BYTES, buffer + 2);
                }

                // reset the count
                count = 0;
            }
            }
        }
        */


        
        
    }

    
  
}
