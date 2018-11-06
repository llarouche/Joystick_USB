

//Todo: ajouter manuellement libraries :
// USBHost 1.0.5 (à confirmer)
// USBHid 0.63.0 (à confirmer)
// USB Host Shield Library 2.0 1.3.2
// Adafruit PWM Servo Driver Library 1.0.2
#define DEBUG_USB_HOST 1

//PROBLÈME: Le Slider n'a que 16 valeurs... Besoin d'aide pour voir comment corriger.
//XY OK sur Logitech Wingman
//Y OK sur Logitech X56

#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#include <SPI.h>

/**************Section pour les servos************/
#include <Wire.h>                     //Pour I2C
#include <Adafruit_PWMServoDriver.h>  //Pour controle de servo en I2C

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
// Si en chaine, c'est par a suite 0x41, 0x42... etc
//La durée du pulse doit être ajustée pour matcher les valeurs min et max du servo

#define Pulselen_Min  150 // this is the 'minimum' pulse length count (out of 4096)
#define Pulselen_Max 600 // this is the 'maximum' pulse length count (out of 4096)
uint16_t Pulselen=0;  

// our servo # counter

uint8_t Servo_Avant_Gauche = 1;
uint8_t Servo_Avant_Droit = 2;
uint8_t Servo_Arriere_Gauche = 3;
uint8_t Servo_Arriere_Droit = 4;
/*************************************************/

#include "hidjoystickrptparser.h"

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

void setup() {
        Serial.begin(115200);
#if !defined(__MIPSEL__)
        while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
        Serial.println("Start");

        if (Usb.Init() == -1)
                Serial.println("OSC did not start.");

        delay(200);

        if (!Hid.SetReportParser(0, &Joy))
                ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);

/**************Section pour les servos************/
pwm.begin();          //Initialisation de la fréquence de rafraichissement des servos
pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
/**************Section pour les servos Fin************/

}

void loop() {
        Usb.Task();
        
}

