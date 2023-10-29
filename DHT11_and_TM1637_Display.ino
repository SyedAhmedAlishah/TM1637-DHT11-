/*
This Code was generateed by Syed Ahmad Ali on 29 Oct, 2023, 
Pins Connection for tested code. 
Arduino (Nano)       |   DHT11 module     | TM1637 Display
     5V              |      Vcc           |      Vcc
     GND             |      GND           |      GND
     D2              |     Data           |       -
     D3              |       -            |      CLK
     D4              |       -            |      DIO
Libraries:
DHT sensor library by Adafruit (v 1.4.4)
TM1637 by Avishay Orpaz (v 1.2.0)
*/

#include <TM1637Display.h>  // Library for TM1637 4 Digit display

#include <Adafruit_Sensor.h> // Libraries for DHT11 temperature and humidity module
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2              // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11

#define CLK 3    // Digital pin connected to the CLK of TM1637 display 
#define DIO 4    // Digital pin connected to the DIO of TM1637 display 

// Create a display object of type DHT sensor
DHT_Unified dht(DHTPIN, DHTTYPE); 

// Create a display object of type TM1637Display
TM1637Display display = TM1637Display(CLK, DIO);

// Create an array that turns all segments ON
const uint8_t allON[] = {0xff, 0xff, 0xff, 0xff};

// Create an array that turns all segments OFF
const uint8_t allOFF[] = {0x00, 0x00, 0x00, 0x00};

// Create degree celsius symbol
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Degree symbol
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

const uint8_t percentage[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Degree symbol
  SEG_C | SEG_D | SEG_E | SEG_G   // C
};

// Create Heat symbol
const uint8_t heat[] = {
  SEG_B | SEG_C | SEG_E | SEG_F |SEG_G,  // H
  SEG_A | SEG_D | SEG_E | SEG_F |SEG_G,  // E
  SEG_A | SEG_B |SEG_C | SEG_E | SEG_F | SEG_G, //A
  SEG_D | SEG_E | SEG_F | SEG_G, //t
};

// Creat H2O symbol for humidity 
const uint8_t hum[] = {
  SEG_B | SEG_C | SEG_E | SEG_F |SEG_G,  // H
  SEG_A | SEG_B |SEG_D | SEG_E | SEG_G, // 2 symbol
  SEG_A | SEG_B |SEG_C | SEG_E | SEG_F | SEG_D, //O
     // C
};

// Variable for storing Temperature and Humidity Values
int temperature = 0;
int humidity = 0; 

void setup() {
  Serial.begin(9600);
  // Initializing DHT sensor object
  dht.begin();
  sensor_t sensor;

	// Set the brightness to 5 (0=dimmest 7=brightest)
	display.setBrightness(7);
	// Set all segments ON
	display.setSegments(allON);

	delay(2000);
	display.clear();

}

void loop() {

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  temperature = int(event.temperature); // Converting Temperature from float to integer 

  dht.humidity().getEvent(&event);
  humidity = int(event.relative_humidity); // Converting Humidity from float to integer 

  display.setSegments(hum, 4, 1); // Displaying H2O symbol
	delay(2000);
	display.clear();

	display.showNumberDec(humidity, false, 2, 0);	 // Displaying Humidity value 
  display.setSegments(percentage, 2, 2); // Displaying % symbol
	delay(2000);
	display.clear();

  display.setSegments(heat, 4, 0); // Displaying heat symbol
	delay(2000);
	display.clear();

  display.showNumberDec(temperature, false, 2, 0); // Displaying Temperature value
	display.setSegments(celsius, 2, 2); // Displaying Celcius symbol
	delay(2000);
	display.clear();
	
}
