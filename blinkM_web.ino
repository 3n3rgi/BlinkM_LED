#include "I2C_LED.h"

// MY: defining random array of colors
//String myColors[2] = {"blue", "red"};

// define the LEDcolor variable
String LEDcolor = "";

int reading = 0;
double volts = 0.0;
// define the A5 as the photoresistor
int photoR = A0;

// runs once at the beginning
void setup() {

    // Open serial port
    Serial.begin(9600);

    // Defining IoT functions
    Particle.function("color", changeColor);

    // Defining IoT variables
    // Particle.variable("newColor", &LEDcolor, STRING);

    // Publish LED chanage of color
    // particle.publish("newColor")


    // Defining internet variables for reading the light level
    Spark.variable("analog", &reading, INT);
    Spark.variable("volts", &volts, DOUBLE);

    // join i2c bus
    Wire.begin();

    // turn off any blinkm scripts
    Wire.beginTransmission(0x00);
    Wire.write('o');
    Wire.endTransmission();
}

// runs continuously
void loop() {
    reading = analogRead(photoR);
    volts = reading * 3.3 / 4096.0;
    Serial.print(volts);
    Serial.print(" - ");
    Serial.print(test(2));
    Serial.print(" - ");
    delay(1500);
}


// Print the color over serial port to the terminal
void printSerial(String color) {
    Serial.println("The user selected the color ");
    Serial.print(color);
    Serial.print('\n');
}

// transmit to the I2C
void transmitColor(byte red, byte green, byte blue) {
    // begin transmission to 0x00, which will send to all connected I2Cs
    Wire.beginTransmission(0x00);
    // fade to a color
    Wire.write('c');
    // set the RGB bytes
    Wire.write(red);
    Wire.write(green);
    Wire.write(blue);
    // send the transmission
    Wire.endTransmission();
}

// LED blinking
//void LEDblink(String color, int duration) {

//}

// LED breething

// set color based on name
int changeColor(String color_name) {

    // publish
    //Particle.publish("newColor");

    // console update
    // printSerial(color_name);

    if (color_name == "red") {
        transmitColor(0xff, 0x00, 0x00);
    } else if (color_name == "green") {
        transmitColor(0x00, 0x80, 0x00);
    } else if (color_name == "blue") {
        transmitColor(0x00, 0x00, 0xff);
    } else if (color_name == "cyan") {
        transmitColor(0x00, 0xff, 0xff);
    } else if (color_name == "white") {
        transmitColor(0xff, 0xff, 0xff);
    } else if (color_name == "oldlace") {
        transmitColor(0xfd, 0xf5, 0xe6);
    } else if (color_name == "warmwhite") {
        transmitColor(0xfd, 0xf5, 0xe6);
    } else if (color_name == "purple") {
        transmitColor(0x80, 0x00, 0x80);
    } else if (color_name == "magenta") {
        transmitColor(0xff, 0x00, 0xff);
    } else if (color_name == "yellow") {
        transmitColor(0xff, 0xff, 0x00);
    } else if (color_name == "orange") {
        transmitColor(0xff, 0xa5, 0x00);
    } else if (color_name == "pink") {
        transmitColor(0xff, 0xc0, 0xcb);
    } else if (color_name == "dim") {
        transmitColor(0x04, 0x04, 0x04);
    }
}