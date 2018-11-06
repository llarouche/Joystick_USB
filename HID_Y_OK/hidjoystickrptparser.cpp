#include "hidjoystickrptparser.h"

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
joyEvents(evt),
oldHat(0xDE),
oldButtons(0) {
        for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
                oldPad[i] = 0xD;
}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
        bool match = true;
        uint8_t bit[24]={0};
        uint8_t bits=0;
        uint16_t valeur=0;
        uint8_t bitoffset=0;
        

        // Checking if there are changes in report since the method was last called
        for (uint8_t i = 0; i <= RPT_GEMEPAD_LEN; i++)
                if (buf[i] != oldPad[i]) {
                        match = false;
                        Serial.print(i);
                        Serial.print(" ");
                        break;
                }
        match = false;
        // Calling Game Pad event handler
        if (!match && joyEvents) {

           
			for (uint8_t i = 0; i <= 2; i++)
			{
          bits=buf[i];
            bit[0+8*i]=(bits & 1)>>0;
            bit[1+8*i]=(bits & 2)>>1;
            bit[2+8*i]=(bits & 4)>>2;
            bit[3+8*i]=(bits & 8)>>3;
            bit[4+8*i]=(bits & 16)>>4;
            bit[5+8*i]=(bits & 32)>>5;
            bit[6+8*i]=(bits & 64)>>6;
            bit[7+8*i]=(bits & 128)>>7;

			}

  		/*
          Serial.print(bit[7]);
          Serial.print(bit[6]);
          Serial.print(bit[5]);
          Serial.print(bit[4]);
          Serial.print(bit[3]);
          Serial.print(bit[2]);
          Serial.print(bit[1]);
          Serial.print(bit[0]);*/


          Serial.print(bit[0]);
          Serial.print(bit[1]);
          Serial.print(bit[2]);
          Serial.print(bit[3]);
          Serial.print(bit[4]);
          Serial.print(bit[5]);
          Serial.print(bit[6]);
          Serial.print(bit[7]);
          Serial.print(bit[8]);
          Serial.print(bit[9]);

          bitoffset=0;
          valeur=bit[0+bitoffset]*1+bit[1+bitoffset]*2+bit[2+bitoffset]*4+bit[3+bitoffset]*8+bit[4+bitoffset]*16+bit[5+bitoffset]*32+bit[6+bitoffset]*64+bit[7+bitoffset]*128+bit[8+bitoffset]*256+bit[9+bitoffset]*512;
          
          Serial.print(" = ");
          Serial.print(valeur);
          Serial.print(", ");


          Serial.print(bit[10]);
          Serial.print(bit[11]);
          Serial.print(bit[12]);
          Serial.print(bit[13]);
          Serial.print(bit[14]);
          Serial.print(bit[15]);
          Serial.print(bit[16]);
          Serial.print(bit[17]);
          Serial.print(bit[18]);
          Serial.print(bit[19]);

          bitoffset=10;
          valeur=bit[0+bitoffset]*1+bit[1+bitoffset]*2+bit[2+bitoffset]*4+bit[3+bitoffset]*8+bit[4+bitoffset]*16+bit[5+bitoffset]*32+bit[6+bitoffset]*64+bit[7+bitoffset]*128+bit[8+bitoffset]*256+bit[9+bitoffset]*512;
          
          Serial.print(" = ");
          Serial.print(valeur);
          Serial.print(" ");
			//}	
     Serial.print("");
			
			
                joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

                for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++) oldPad[i] = buf[i];
        }

        uint8_t hat = (buf[5] & 0xF);

        // Calling Hat Switch event handler
        if (hat != oldHat && joyEvents) {
                joyEvents->OnHatSwitch(hat);
                oldHat = hat;
        }

        uint16_t buttons = (0x0000 | buf[6]);
        buttons <<= 4;
        buttons |= (buf[5] >> 4);
        uint16_t changes = (buttons ^ oldButtons);

        // Calling Button Event Handler for every button changed
        if (changes) {
                for (uint8_t i = 0; i < 0x0C; i++) {
                        uint16_t mask = (0x0001 << i);

                        if (((mask & changes) > 0) && joyEvents) {
                                if ((buttons & mask) > 0)
                                        joyEvents->OnButtonDn(i + 1);
                                else
                                        joyEvents->OnButtonUp(i + 1);
                        }
                }
                oldButtons = buttons;
        }
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt) {
/*        Serial.print("Manette X: ");
        Serial.print(evt->X);

        Serial.print(" Manette Y: ");
        Serial.print(evt->Y);


        Serial.print(" Yaw: ");
        Serial.print(evt->Z2);    
        
        Serial.print(" Mushroom: ");
        Serial.print(evt->Z1);

        Serial.print(" Boutons: ");
        Serial.print(evt->Rz);*/

        Serial.println("");
}

void JoystickEvents::OnHatSwitch(uint8_t hat) {
        Serial.print("Throttle: ");
        Serial.print(hat);
        //PrintHex<uint8_t > (hat, 0x80);
        
        Serial.println("");
}

void JoystickEvents::OnButtonUp(uint8_t but_id) {
        //Serial.print("Up: ");
        //Serial.println(but_id, DEC);
}

void JoystickEvents::OnButtonDn(uint8_t but_id) {
        //Serial.print("Dn: ");
        //Serial.println(but_id, DEC);
}
