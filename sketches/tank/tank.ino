/*
IR sensor

left A0
central 5V
right GROUND

LED (13) 10
 */

#include <IRremote.h>
#include <Adafruit_MotorShield.h>
#include <andsoft.h>

const int IR_PIN = A0;
const int LED_PIN = 10;

int speed = 125;
uint8_t direction = RELEASE;

IRrecv irrecv(IR_PIN);
decode_results results;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor = AFMS.getMotor(3);

AndSoft::LED led(LED_PIN, speed);

const unsigned long periods[] = {300, 300};

void execute()
{
  led.setHigh(speed);

  if (direction == RELEASE)
  {
    // fix light when not moving
    led.on();
  }
  else
  {
    // flashing light when moving
    led.flash(periods, 2, false);
  }

  motor->setSpeed(speed);
  motor->run(direction);

  Serial.print("Direction: ");
  Serial.println(direction);
  Serial.print("Speed: ");
  Serial.println(speed);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino TANK 1.0.");
  Serial.print("Initialising...");

  irrecv.enableIRIn();
  led.setup();
  AFMS.begin();

  Serial.println("done.");
  delay(100);

  execute();
  delay(100);
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.print(results.decode_type);
    Serial.print(",");

    const unsigned long value = results.value;
    Serial.println(value, HEX);

    switch (value)
    {
    case 0x10: // 1
      speed = 0;
      break;
    case 0x810: // 2
      speed = 255;
      break;
    case 0x410: // 3
      direction = RELEASE;
      break;
    case 0xC10: // 4
      direction = FORWARD;
      break;
    case 0x210: // 5
      direction = BACKWARD;
      break;
    case 0x90: // P+
      speed += 5;
      break;
    case 0x890: // P-
      speed -= 5;
      break;
    }
    speed = min(255, max(speed, 0));

    execute();

    irrecv.resume();
  }

  led.loop();
  delay(100);
}

// Local Variables:
// mode: c++
// End:
