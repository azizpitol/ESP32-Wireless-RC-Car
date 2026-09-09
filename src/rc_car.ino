/*
  ============================================================
  Wireless RC Car Using ESP32
  ============================================================

  Project:
  Wireless Dual-Motor RC Car

  Controller:
  ESP32

  Receiver:
  FlySky FS-iA6B

  Motor Drivers:
  2 x BTS7960

  Power:
  3S LiPo Battery (11.1V nominal, 12.6V fully charged)
  LM2596 Buck Converter(s)

  ------------------------------------------------------------
  Receiver Connections
  ------------------------------------------------------------
  CH1 -> GPIO 34  (Throttle)
  CH2 -> GPIO 35  (Steering)

  ------------------------------------------------------------
  BTS7960 #1
  ------------------------------------------------------------
  RPWM -> GPIO 25
  LPWM -> GPIO 26

  ------------------------------------------------------------
  BTS7960 #2
  ------------------------------------------------------------
  RPWM -> GPIO 27
  LPWM -> GPIO 14

  ============================================================
*/


// ============================================================
// PIN DEFINITIONS
// ============================================================

// ---------- Receiver ----------
const int THROTTLE_PIN = 34;
const int STEERING_PIN = 35;


// ---------- BTS7960 Motor Driver #1 ----------
const int MOTOR1_RPWM = 25;
const int MOTOR1_LPWM = 26;


// ---------- BTS7960 Motor Driver #2 ----------
const int MOTOR2_RPWM = 27;
const int MOTOR2_LPWM = 14;


// ============================================================
// PWM SETTINGS
// ============================================================

const int PWM_FREQUENCY = 1000;
const int PWM_RESOLUTION = 8;       // 8-bit = 0 to 255

const int MAX_SPEED = 255;


// ============================================================
// RC SIGNAL SETTINGS
// ============================================================

// Typical RC receiver pulse range
const int RC_MIN = 1000;
const int RC_CENTER = 1500;
const int RC_MAX = 2000;

// Dead zone around joystick center
const int DEAD_ZONE = 50;


// ============================================================
// SAFETY SETTINGS
// ============================================================

// If receiver signal is not received within this time,
// stop the motors.
const unsigned long SIGNAL_TIMEOUT = 100;


// ============================================================
// FUNCTION: Stop a Motor
// ============================================================

void stopMotor(int rpwm, int lpwm)
{
  analogWrite(rpwm, 0);
  analogWrite(lpwm, 0);
}


// ============================================================
// FUNCTION: Control One BTS7960 Motor
// ============================================================
//
// speed:
//   +255 = maximum forward
//      0 = stop
//   -255 = maximum reverse
//
// ============================================================

void setMotor(int rpwm, int lpwm, int speed)
{
  // Limit speed
  speed = constrain(speed, -MAX_SPEED, MAX_SPEED);

  // Stop
  if (speed == 0)
  {
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 0);
    return;
  }

  // Forward
  if (speed > 0)
  {
    analogWrite(lpwm, 0);
    analogWrite(rpwm, speed);
  }

  // Reverse
  else
  {
    analogWrite(rpwm, 0);
    analogWrite(lpwm, -speed);
  }
}


// ============================================================
// FUNCTION: Convert RC Pulse to Motor Speed
// ============================================================

int rcToSpeed(int pulse)
{
  // If signal is invalid, return zero
  if (pulse < RC_MIN || pulse > RC_MAX)
  {
    return 0;
  }

  // Calculate difference from center
  int difference = pulse - RC_CENTER;

  // Apply dead zone
  if (abs(difference) < DEAD_ZONE)
  {
    return 0;
  }

  // Convert RC value to motor speed
  int speed;

  if (difference > 0)
  {
    speed = map(
      pulse,
      RC_CENTER + DEAD_ZONE,
      RC_MAX,
      0,
      MAX_SPEED
    );
  }
  else
  {
    speed = map(
      pulse,
      RC_MIN,
      RC_CENTER - DEAD_ZONE,
      -MAX_SPEED,
      0
    );
  }

  return constrain(speed, -MAX_SPEED, MAX_SPEED);
}


// ============================================================
// SETUP
// ============================================================

void setup()
{
  Serial.begin(115200);

  // Receiver pins
  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEERING_PIN, INPUT);

  // Motor driver pins
  pinMode(MOTOR1_RPWM, OUTPUT);
  pinMode(MOTOR1_LPWM, OUTPUT);

  pinMode(MOTOR2_RPWM, OUTPUT);
  pinMode(MOTOR2_LPWM, OUTPUT);

  // Make sure motors are stopped at startup
  stopMotor(MOTOR1_RPWM, MOTOR1_LPWM);
  stopMotor(MOTOR2_RPWM, MOTOR2_LPWM);

  Serial.println();
  Serial.println("=================================");
  Serial.println(" Wireless RC Car - ESP32");
  Serial.println("=================================");
  Serial.println("System starting...");
}


// ============================================================
// MAIN LOOP
// ============================================================

void loop()
{
  // ----------------------------------------------------------
  // Read receiver signals
  // ----------------------------------------------------------

  unsigned long throttlePulse =
    pulseIn(THROTTLE_PIN, HIGH, 30000);

  unsigned long steeringPulse =
    pulseIn(STEERING_PIN, HIGH, 30000);


  // ----------------------------------------------------------
  // Receiver failsafe
  // ----------------------------------------------------------

  if (
    throttlePulse < RC_MIN ||
    throttlePulse > RC_MAX ||
    steeringPulse < RC_MIN ||
    steeringPulse > RC_MAX
  )
  {
    stopMotor(MOTOR1_RPWM, MOTOR1_LPWM);
    stopMotor(MOTOR2_RPWM, MOTOR2_LPWM);

    Serial.println("No valid receiver signal - MOTORS STOPPED");

    delay(20);
    return;
  }


  // ----------------------------------------------------------
  // Convert receiver input to speed values
  // ----------------------------------------------------------

  int throttle = rcToSpeed(throttlePulse);
  int steering = rcToSpeed(steeringPulse);


  // ----------------------------------------------------------
  // Differential Drive Mixing
  // ----------------------------------------------------------
  //
  // Forward:
  //
  // Left  = throttle
  // Right = throttle
  //
  // Turning:
  //
  // Left  = throttle + steering
  // Right = throttle - steering
  //
  // This allows the vehicle to turn by changing the
  // relative speed of the two motors.
  // ----------------------------------------------------------

  int leftMotorSpeed =
    throttle + steering;

  int rightMotorSpeed =
    throttle - steering;


  // Limit motor speeds
  leftMotorSpeed =
    constrain(leftMotorSpeed, -MAX_SPEED, MAX_SPEED);

  rightMotorSpeed =
    constrain(rightMotorSpeed, -MAX_SPEED, MAX_SPEED);


  // ----------------------------------------------------------
  // Send commands to BTS7960 drivers
  // ----------------------------------------------------------

  setMotor(
    MOTOR1_RPWM,
    MOTOR1_LPWM,
    leftMotorSpeed
  );

  setMotor(
    MOTOR2_RPWM,
    MOTOR2_LPWM,
    rightMotorSpeed
  );


  // ----------------------------------------------------------
  // Serial Monitor Debugging
  // ----------------------------------------------------------

  Serial.print("Throttle: ");
  Serial.print(throttlePulse);

  Serial.print(" | Steering: ");
  Serial.print(steeringPulse);

  Serial.print(" | Left: ");
  Serial.print(leftMotorSpeed);

  Serial.print(" | Right: ");
  Serial.println(rightMotorSpeed);


  delay(20);
}
