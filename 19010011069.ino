//https://github.com/Enderceliik
//Ender CELIK

#include <EEPROM.h>

boolean toogle = LOW; // Boolean variable to be used for the led that will indicate that the system is working by flashing.
					  // Sistemin çalıştığını yanıp sönerek belli edecek led için kullanılacak boolean değişken.
int readValue;
int potentiometerValue;
float voltage;
float temperatureC;

#define analogPin0 A0 
#define analogPin5 A5

#define ledGreen1 3 
#define ledGreen2 5
#define ledRed1 6
#define ledWhite1 9
#define ledYellow1 10
#define ledRed2 11
#define ledRed3 13

void setup() {
  Serial.begin(9600); // We started communication.
					  // Haberleşmeyi başlattık.
  EEPROM.write(0,0); // I write the values ​​that I will use later in the EEPROM in order.
					 // EEPROM'a daha sonra kullanacağım değerleri sırayla yazıyorum.
  EEPROM.write(1,7);
  EEPROM.write(2,14);
  EEPROM.write(3,21);
  EEPROM.write(4,28);
  EEPROM.write(5,35);
  EEPROM.write(6,42);

  pinMode(analogPin0, INPUT); // The use cases of the pins have been set.
							  // Pinlerin kullanım durumları ayarlandı.
  pinMode(analogPin5, INPUT);
  pinMode(ledGreen1, OUTPUT);
  pinMode(ledGreen2, OUTPUT);
  pinMode(ledRed1, OUTPUT);
  pinMode(ledWhite1, OUTPUT);
  pinMode(ledYellow1, OUTPUT);
  pinMode(ledRed2, OUTPUT);

  cli(); // Interrupts are stopped.
         // Interruptt'lar durduruldu.
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624; // 1 second cutoff set. For 3 seconds: 46875
				 // 1 saniyelik kesme ayarlandı. 3 saniyelik için: 46875
  TCCR1B |=(1<<WGM12);
  TCCR1B |=(1<<CS12)|(1<<CS10);

  TIMSK1 |=(1<<OCIE1A);
  sei();

}
ISR(TIMER1_COMPA_vect)
{
    toogle = !toogle; 
    digitalWrite(ledWhite1, toogle); // Turning off and on the led indicating that the system is working.
									 // Sistemin çalıştığını işaret eden ledin södürülüp yakılması.
    potentiometerValue = analogRead(analogPin0);  
    potentiometerValue = map(potentiometerValue, 0, 1023, 0, 255);  // We have compared the above value to the range we can use.
	                                                                // Yukarıdaki değeri kullanabileceğimiz aralığa oranladık.
    
    //Serial.println(potentiometerValue); // In case you want to see the value on the potentiometer.
	                                      // Potansiyometredeki değerin görülmek istenmesi durumunda.
    
    if(potentiometerValue == 255)  // Block to process when potentiometer is in 255 [HIGH] state: Control is on Arduino.
	                               // Potansiyometre 255 [HIGH] durumundayken işlenecek blok: Kontrol Arduino'da.
    {
        analogWrite(ledYellow1, 255); // We turned off the yellow led indicating that the control is in the Potentiometer.
		                              // Kontrolün Potansiyometre de olduğunu belirten sarı led'i söndürdük.
        readValue = analogRead(analogPin5); // We read the value from the LM35 Temperature sensor.
											// LM35 Sıcaklık sensöründen gelen değeri okuduk.
        voltage = readValue * 4.68;
        voltage /= 1024.0;  // We converted it to Celsius.
		                    // Santigrat'a dönüştürdük.
        temperatureC = (voltage - 0.5) * 100;
        //Serial.println(temperatureC);  // In case the value from LM35 is desired to be seen.
									     // LM35'den gelen değerin görülmek istenmesi durumunda.
        if(temperatureC < EEPROM.read(0))  //EEPROM'a daha önce yazdığımız sıcaklık değerlerine göre led'lerin parlaklığını ayarlayan if blokları:
        {
          Serial.println("part 1"); // For debug.
          analogWrite(ledGreen1, 0);
          analogWrite(ledGreen2, 0);
          analogWrite(ledRed1, 0);
          analogWrite(ledRed2, 0);
          analogWrite(ledRed3, 0); 
        }
        if(EEPROM.read(0)< temperatureC && temperatureC<= EEPROM.read(1)) // 0 to 7
        {
          Serial.println("part 2"); // For debug.
          analogWrite(ledGreen1, 30);
          analogWrite(ledGreen2, 30);
          analogWrite(ledRed1, 30);
          analogWrite(ledRed2, 30);
          analogWrite(ledRed3, 30);
        }
        if(EEPROM.read(1)< temperatureC && temperatureC<= EEPROM.read(2)) // 7 to 14
        {
          Serial.println("part 3"); // For debug.
          analogWrite(ledGreen1, 60);
          analogWrite(ledGreen2, 60);
          analogWrite(ledRed1, 60);
          analogWrite(ledRed2, 60);
          analogWrite(ledRed3, 60);
        }
        if(EEPROM.read(2)< temperatureC && temperatureC<= EEPROM.read(3)) // 14 to 21
        {
          Serial.println("part 4"); // For debug.
          analogWrite(ledGreen1, 110);
          analogWrite(ledGreen2, 110);
          analogWrite(ledRed1, 110);;
          analogWrite(ledRed2, 110);
          analogWrite(ledRed3, 110);
        }
        if(EEPROM.read(3)< temperatureC && temperatureC<= EEPROM.read(4)) // 21 to 28
        {
          Serial.println("part 5"); // For debug.
          analogWrite(ledGreen1, 160);
          analogWrite(ledGreen2, 160);
          analogWrite(ledRed1, 160);
          analogWrite(ledRed2, 160);
          analogWrite(ledRed3, 160);
        }
        if(EEPROM.read(4)< temperatureC && temperatureC<= EEPROM.read(5)) // 28 to 35
        {
          Serial.println("part 6"); // For debug.
          analogWrite(ledGreen1, 210);
          analogWrite(ledGreen2, 210);
          analogWrite(ledRed1, 210);
          analogWrite(ledRed2, 210);
          analogWrite(ledRed3, 210);
        }
        if(EEPROM.read(5)< temperatureC && temperatureC<= EEPROM.read(6)) // 35 to 42
        {
          Serial.println("part 7"); // For debug.
          analogWrite(ledGreen1, 225);
          analogWrite(ledGreen2, 225);
          analogWrite(ledRed1, 225);
          analogWrite(ledRed2, 225);
          analogWrite(ledRed3, 225);
        }
        if(EEPROM.read(6)< temperatureC)  // 42
        {
          Serial.println("part 8"); // For debug.
          analogWrite(ledGreen1, 255);
          analogWrite(ledGreen2, 255);
          analogWrite(ledRed1, 255);
          analogWrite(ledRed2, 255);
          analogWrite(ledRed3, 255);
        } 
      }
      if(potentiometerValue != 255) // Block to be processed when Potentiometer 255 is not in [HIGH] state: Control is at Potentiometer, so is the user.
									// Potansiyometre 255 [HIGH] durumunda değilken işlenecek blok: Kontrol Potansiyometre'de yani kullanıcı da.
      { 
        readValue = analogRead(analogPin5); // We read the value from the LM35 Temperature sensor.
											// LM35 Sıcaklık sensöründen gelen değeri okuduk.
        voltage = readValue * 4.68;
        voltage /= 1024.0;  // We converted it to Celsius.
		                    // Santigrat'a dönüştürdük.
        temperatureC = (voltage - 0.5) * 100;
        temperatureC = temperatureC + 6.0;

        if(temperatureC < - 10)
        {
          Serial.println("Low temperature");
          analogWrite(ledYellow1, 255); // We turned off the yellow led indicating that the control is in the Potentiometer.
										// Kontrolün Potansiyometre de olduğunu belirten sarı led'i söndürdük.      
          analogWrite(ledGreen1, 0);
          analogWrite(ledGreen2, 0);
          analogWrite(ledRed1, 0);
          analogWrite(ledRed2, 0);
          analogWrite(ledRed3, 0); 
        }
        if(temperatureC >= 45)
        {
          Serial.println("High temperature");
          analogWrite(ledYellow1, 255); // We turned off the yellow led indicating that the control is in the Potentiometer.
										// Kontrolün Potansiyometre de olduğunu belirten sarı led'i söndürdük.
          analogWrite(ledGreen1, 255);
          analogWrite(ledGreen2, 255);
          analogWrite(ledRed1, 255);
          analogWrite(ledRed2, 255);
          analogWrite(ledRed3, 255);
        }
        if(temperatureC >= -10 && temperatureC <45)
        {
          Serial.println("User-controlled in the normal temperature range"); 
          analogWrite(ledYellow1, 0); // We turned on the yellow led indicating that the control is in the Potentiometer.
									  // Kontrolün Potansiyometre de olduğunu belirten sarı led'i yaktık.
          analogWrite(ledGreen1, potentiometerValue);
          analogWrite(ledGreen2, potentiometerValue);
          analogWrite(ledRed1, potentiometerValue);
          analogWrite(ledRed2, potentiometerValue);
          analogWrite(ledRed3, potentiometerValue);
        }
      }
}

void loop() {}
