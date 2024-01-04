// Declaring Some Macros For Using First Water Pump
#define FirstWaterPump_Pin 2
#define FirstWaterPump_Enable HIGH
#define FirstWaterPump_Disable LOW

// Declaring Some Macros For Using Second Water Pump
#define SecondWaterPump_Pin 3
#define SecondWaterPump_Enable HIGH
#define SecondWaterPump_Disable LOW

// Declaring Some Macros For Using DC Motor
#define DCMotor_Pin 4
#define DCMotor_Enable HIGH
#define DCMotor_Disable LOW

// Declaring Some Macros For Using First Stepper Motor
#define FirstStepper_Direction_Pin 5
#define FirstStepper_Pulse_Pin 6
#define FirstStepper_NumberOfSteps 30

// Declaring Some Macros For Using Second Stepper Motor
#define SecondStepper_Direction_Pin 7
#define SecondStepper_Pulse_Pin 8
#define SecondStepper_NumberOfSteps 200

// Declaring Some Macros For Cinfiguring Stepper Motor Direction
#define Stepper_ClockWise HIGH
#define Stepper_CounterClockWise LOW

// Declaring Some Macros For Using First IR Sensor
#define FirstIRSensor_Pin 9
#define FirstIRSensor_Enable HIGH
#define FirstIRSensor_Disable LOW

// Declaring Some Macros For Using Second IR Sensor
#define SecondIRSensor_Pin 10
#define SecondIRSensor_Enable HIGH
#define SecondIRSensor_Disable LOW

// Declaring Some Macros For Using First IR Sensor
#define ThirdIRSensor_Pin 11
#define ThirdIRSensor_Enable HIGH
#define ThirdIRSensor_Disable LOW

// Declaring Some Macros For Timing Second Water Pump
#define DrainCoffee_Time 5000

// Declaring Some Macros For Timing Second Stepper Motor Cycle
#define FirstGlassToSecondGlass_Time 10000
#define SecondGlassToFirstGlass_Time 10000

#define FirstGlassToThirdGlass_Time 20000
#define ThirdGlassToFirstGlass_Time 20000

// Declaring Some Utility Macros For Timing
#define TakingGlass_Time 10000

unsigned long int TheTime = (unsigned long int)0;

void setup(void) {
  // Configuring First Water Pump
  pinMode((uint8_t)FirstWaterPump_Pin, (uint8_t)OUTPUT);
  digitalWrite((uint8_t)FirstWaterPump_Pin, (uint8_t)FirstWaterPump_Disable);

  // Configuring Second Water Pump
  pinMode((uint8_t)SecondWaterPump_Pin, (uint8_t)OUTPUT);
  digitalWrite((uint8_t)SecondWaterPump_Pin, (uint8_t)SecondWaterPump_Disable);

  // Configuring DC Motor
  pinMode((uint8_t)DCMotor_Pin, (uint8_t)OUTPUT);
  digitalWrite((uint8_t)DCMotor_Pin, (uint8_t)DCMotor_Disable);

  // Configuring First Stepper Motor
  pinMode((uint8_t)FirstStepper_Direction_Pin, (uint8_t)OUTPUT);
  pinMode((uint8_t)FirstStepper_Pulse_Pin, (uint8_t)OUTPUT);
  digitalWrite((uint8_t)FirstStepper_Direction_Pin, (uint8_t)LOW);
  digitalWrite((uint8_t)FirstStepper_Pulse_Pin, (uint8_t)LOW);

  // Configuring Second Stepper Motor
  pinMode((uint8_t)SecondStepper_Direction_Pin, (uint8_t)OUTPUT);
  pinMode((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)OUTPUT);
  digitalWrite((uint8_t)SecondStepper_Direction_Pin, (uint8_t)LOW);
  digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)LOW);

  // Configuring First IR Sensor
  pinMode((uint8_t)FirstIRSensor_Pin, (uint8_t)INPUT);

  // Configuring Second IR Sensor
  pinMode((uint8_t)SecondIRSensor_Pin, (uint8_t)INPUT);

  // Configuring Third IR Sensor
  pinMode((uint8_t)ThirdIRSensor_Pin, (uint8_t)INPUT);

  // Dealy 4 Seconds For Initializing Machine
  delay((unsigned long int)4000);

  // Enableing First Water Pump
  digitalWrite((uint8_t)FirstWaterPump_Pin, (uint8_t)FirstWaterPump_Enable);
  // 1 ClockWise Rotation First Stepper Motor
  digitalWrite((uint8_t)FirstStepper_Direction_Pin, (uint8_t)Stepper_ClockWise);
  for (int Counter = (int)0; Counter < (int)SecondStepper_NumberOfSteps; Counter += (int)1) {
    digitalWrite((uint8_t)FirstStepper_Pulse_Pin, (uint8_t)HIGH);
    delay((unsigned long int)17);
    digitalWrite((uint8_t)FirstStepper_Pulse_Pin, (uint8_t)LOW);
    delay((unsigned long int)17);
  }
  delay((unsigned long int)8000);
  // 1 CounterClockWise Rotation First Stepper
  digitalWrite((uint8_t)FirstStepper_Direction_Pin, (uint8_t)Stepper_CounterClockWise);
  for (int Counter = (int)0; Counter < (int)SecondStepper_NumberOfSteps; Counter += (int)1) {
    digitalWrite((uint8_t)FirstStepper_Pulse_Pin, (uint8_t)HIGH);
    delay((unsigned long int)17);
    digitalWrite((uint8_t)FirstStepper_Pulse_Pin, (uint8_t)LOW);
    delay((unsigned long int)17);
  }
  delay((unsigned long int)5000);
  // Disabling First Water Pump
  digitalWrite((uint8_t)FirstWaterPump_Pin, (uint8_t)FirstWaterPump_Disable);

  // Enabling DC Motor For 60 Seconds
  digitalWrite((uint8_t)DCMotor_Pin, (uint8_t)DCMotor_Enable);
  delay((unsigned long int)60000);
  digitalWrite((uint8_t)DCMotor_Pin, (uint8_t)DCMotor_Disable);
}

void loop(void) {
// Set Program Start Point
StartPoint:

  // Check If The First IR Sensor Is Enable
  if (digitalRead((uint8_t)FirstIRSensor_Pin) == (int)FirstIRSensor_Enable) {
    delay((unsigned long int)2000);

    // Enabling Second Water Pump
    digitalWrite((uint8_t)SecondWaterPump_Pin, (uint8_t)SecondWaterPump_Enable);
    delay((unsigned long int)DrainCoffee_Time);
    // Disabling Second Water Pump
    digitalWrite((uint8_t)SecondWaterPump_Pin, (uint8_t)SecondWaterPump_Disable);

    delay((unsigned long int)2000);

    // Waiting For Taking The Filled Glass
    delay((unsigned long int)TakingGlass_Time);

    // Move Program To Start Point
    goto StartPoint;
  }

  // Check If The Second IR Sensor Is Enable
  else if (digitalRead((uint8_t)SecondIRSensor_Pin) == (int)SecondIRSensor_Enable) {
    // Move The Head To Second Glass Section
    TheTime = millis();
    while ((millis() < (FirstGlassToSecondGlass_Time + TheTime)))
    {
      digitalWrite((uint8_t)SecondStepper_Direction_Pin, (uint8_t)Stepper_ClockWise);
      for (int Counter = (int)0; Counter < SecondStepper_NumberOfSteps; Counter += 1)
      {
        digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)HIGH);
        delayMicroseconds(2500);
        digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)LOW);
        delayMicroseconds(2500);
      }
    }

    delay((unsigned long int)2000);

    // Enabling Second Water Pump
    digitalWrite((uint8_t)SecondWaterPump_Pin, (uint8_t)SecondWaterPump_Enable);
    delay((unsigned long int)DrainCoffee_Time);
    // Disabling Second Water Pump
    digitalWrite((uint8_t)SecondWaterPump_Pin, (uint8_t)SecondWaterPump_Disable);

    delay((unsigned long int)2000);

    // Move The Head To First Glass Section
    TheTime = millis();
    while ((millis() < (SecondGlassToFirstGlass_Time + TheTime)))
    {
      digitalWrite((uint8_t)SecondStepper_Direction_Pin, (uint8_t)Stepper_CounterClockWise);
      for (int Counter = (int)0; Counter < SecondStepper_NumberOfSteps; Counter += 1)
      {
        digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)HIGH);
        delayMicroseconds(2500);
        digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)LOW);
        delayMicroseconds(2500);
      }
    }    

    // Waiting For Taking The Filled Glass
    delay((unsigned long int)TakingGlass_Time);

    // Move Program To Start Point
    goto StartPoint;
  }

  // Check If The Third IR Sensor Is Enable
  else if (digitalRead((uint8_t)ThirdIRSensor_Pin) == (int)ThirdIRSensor_Enable) {
    // Move The Head To Third Glass Section
    TheTime = millis();
    while ((millis() < (FirstGlassToThirdGlass_Time + TheTime)))
    {
      digitalWrite((uint8_t)SecondStepper_Direction_Pin, (uint8_t)Stepper_ClockWise);
      for (int Counter = (int)0; Counter < SecondStepper_NumberOfSteps; Counter += 1)
      {
        digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)HIGH);
        delayMicroseconds(2500);
        digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)LOW);
        delayMicroseconds(2500);
      }
    }

    delay((unsigned long int)2000);

    // Enabling Second Water Pump
    digitalWrite((uint8_t)SecondWaterPump_Pin, (uint8_t)SecondWaterPump_Enable);
    delay((unsigned long int)DrainCoffee_Time);
    // Disabling Second Water Pump
    digitalWrite((uint8_t)SecondWaterPump_Pin, (uint8_t)SecondWaterPump_Disable);

    delay((unsigned long int)2000);

    // Move The Head To First Glass Section
    TheTime = millis();
    while ((millis() < (ThirdGlassToFirstGlass_Time + TheTime)))
    {
      digitalWrite((uint8_t)SecondStepper_Direction_Pin, (uint8_t)Stepper_CounterClockWise);
      for (int Counter = (int)0; Counter < SecondStepper_NumberOfSteps; Counter += 1)
      {
        digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)HIGH);
        delayMicroseconds(2500);
        digitalWrite((uint8_t)SecondStepper_Pulse_Pin, (uint8_t)LOW);
        delayMicroseconds(2500);
      }
    }    

    // Waiting For Taking The Filled Glass
    delay((unsigned long int)TakingGlass_Time);

    // Move Program To Start Point
    goto StartPoint;
  }

  // If The All Sensors Is Not Enable
  else {
    // Move Program To Start Point
    goto StartPoint;
  }
}