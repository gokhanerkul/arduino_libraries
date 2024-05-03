#include "HX711.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN
float analog_pot=0;
#define DOUT 2
#define CLK 3
HX711 scale;
float calibration_factor =51000;
//56400 worked for my 440lb max scale set
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#endif
void setup() {
Serial.begin(9600);
scale.begin(DOUT, CLK);
scale.set_scale();
scale.tare(); //Reset the scale to 0
long zero_factor = scale.read_average(); //Get a baseline reading
Serial.print("Zero factor: "); //This can be used to remove the need to tare the
scale. Useful in permanent scale projects.
Serial.println(zero_factor);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C
addr 0x3D (for the 128x64)
// init done
display.display();
delay(200);
// Clear the buffer.
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("KENDINURET");
delay(3000);
display.setTextColor(BLACK, WHITE); // 'inverted' text
display.display();
delay(1000);
}
void loop() {
digitalWrite(6,HIGH);
scale.set_scale(calibration_factor); //Adjust to this calibration factor
Serial.print("Reading: ");
Serial.print(scale.get_units()*0.453592, 3);
Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you
follow SI units like a sane person
Serial.print(" calibration_factor: ");
Serial.print(calibration_factor);
Serial.println();
display.clearDisplay();
display.setTextSize(2.5);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print(scale.get_units()*0.453592, 2);
display.println(" kg");
display.println()
display.print(scale.get_units(), 2);
display.println(" £");
display.setTextColor(BLACK, WHITE); // 'inverted' text
display.display();
delay(1000);}
