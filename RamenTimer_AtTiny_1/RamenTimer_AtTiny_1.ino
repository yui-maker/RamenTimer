//Yui_maker ramen PCB timer code.
//This is a code for 3 minutes and the numbers are hard coded in it. :(
//the tone library wasn't working for playing tones with AtTiny 85 so, I used another code found online
//This is the final version of the code uploaded on the IC

#include <Arduino.h>

int push_button = 4;
int buzz = 3;
int led_2 = 2;
int led_1 = 1;
int led_0 = 0;

long Timestamp_Button_Pressed;

bool timerRunning = false;

void setup()
{
  // Set LED and buzzer pins as outputs, and the button pin as an input with pull-up
  pinMode(led_0, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(push_button, INPUT_PULLUP);

  // Initialize variables
  Timestamp_Button_Pressed = 0;

  // Put the buzzer to silent
  noTone(buzz);
}

void loop()
{
  // Check if the button is pressed
  if (digitalRead(push_button) == LOW && !timerRunning)
  {
    // Let the button debounce
    delay(200);
    // start the initial timer for button press
    Timestamp_Button_Pressed = millis();
    // turn on the flag for timer running
    timerRunning = true;

    //loop for the first minute
    while (millis() - Timestamp_Button_Pressed <= 60000)
    {
      digitalWrite(led_0, HIGH);
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      //if button pressed turn the timer off
      if (digitalRead(push_button) == LOW) {
        break;
      }

    }
    // turn on second LED for the second minute
    while ((millis() - Timestamp_Button_Pressed <= 120000) && (millis() - Timestamp_Button_Pressed > 60000) )
    {
      digitalWrite(led_0, HIGH);
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, LOW);

      if (digitalRead(push_button) == LOW) {
        break;
      }

    }
    // turn on third LED for the third minute
    while ((millis() - Timestamp_Button_Pressed <= 180000) && (millis() - Timestamp_Button_Pressed > 120000) )
    {
      digitalWrite(led_0, HIGH);
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);

      if (digitalRead(push_button) == LOW) {
        break;
      }

    }
  }
  // Check if it's the end of the third minute
  if (millis() - Timestamp_Button_Pressed > 180000 && timerRunning)
  {
    //Untill user presses a button let all LEDs be on and buzzer running
    while (digitalRead(push_button) == HIGH) {
      digitalWrite(led_0, HIGH);
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      //tone library wasn't working so, this code is for buzzing the buzzer
      for (int i = 150; i > 85; i--) {
        analogWrite(buzz, i);
      }
      delay(100);
      digitalWrite(buzz, LOW);
      delay(100);
    }

    // Reset variables if the user presses the button
    if (digitalRead(push_button) == LOW) {
      Timestamp_Button_Pressed = 0;
      timerRunning = false;
      noTone(buzz);
      digitalWrite(led_0, LOW);
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      delay(250);
    }

  }

  // If the button was pressed while timer was running for more than 100 miliseconds.
  if (timerRunning && (digitalRead(push_button) == LOW) && (millis() - Timestamp_Button_Pressed < 180000) && (millis() - Timestamp_Button_Pressed > 100))
  {
    // Button is pressed while the timer is running, cancel everything
    Timestamp_Button_Pressed = 0;
    timerRunning = false;
    noTone(buzz);
    digitalWrite(led_0, LOW);
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    delay(200);
  }
}
