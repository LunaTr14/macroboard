#include <Keyboard.h>
const int SCL_PIN = 5;
const int SDO_PIN = 6;

/*
----Keycode Tables----
https://docstore.mik.ua/orelly/webprog/DHTML_javascript/0596004672_jvdhtmlckbk-app-b.html
----Keycode Tables----
*/

const int KEYS[7] = {89, 90, 91, 92, 93, 94, 95};
const int MODIFIERS[2] = {210, 130}; // HOME, LEFT_ALT
const int BUTTON_DELAY = 250;

void setup()
{
  Serial.begin(9600);
  Keyboard.begin();
}

void loop()
{
  BLINK_SCL();
  for (int i = 0; i < 7; i++)
  {
    START_SCL_CLOCK();

    if (is_valid_signal())
    {
      HOLD_MODIFIERS();
      press_key(KEYS[i]);
      break;
    }
  }
  Keyboard.releaseAll();
  delay(BUTTON_DELAY); // Prevents double click
}

// No idea what this code does
const void BLINK_SCL()
{
  pinMode(SCL_PIN, OUTPUT);
  digitalWrite(SCL_PIN, HIGH);
  pinMode(SDO_PIN, INPUT);
}

const void START_SCL_CLOCK()
{
  digitalWrite(SCL_PIN, LOW);
  digitalWrite(SCL_PIN, HIGH);
}

bool is_valid_signal()
{
  return !digitalRead(SDO_PIN);
}

const void HOLD_MODIFIERS()
{
  for (int i = 0; i < sizeof(MODIFIERS); i++)
  {
    Keyboard.press(MODIFIERS[i]);
  }
}

void press_key(uint8_t key_id)
{
  Keyboard.press(key_id);
}