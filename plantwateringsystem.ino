


unsigned int SAMPLE_DELAY = 40000;
const int PUMP_TIME = 3 * 1000;
const int TRIGGER_VALUE = 50;

char state = 0;
//states
//0 init
//1 polling
//2 watering

unsigned long timeStamp;
unsigned long startWateringTime;
const float VOLTAGE = 5;

const int motorControl = 2;

// soil sensor
const int AirValue = 598;
const int WaterValue = 418;  
int intervals = (AirValue - WaterValue)/3;   

void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  pinMode(motorControl, OUTPUT); 
  timeStamp = millis();
  startWateringTime = 0;
  state = 1;
}

int checkSoil() {
  float voltage = (float(analogRead(A0))/1023.0)* VOLTAGE;// read sensor
  Serial.print("Soil Moisture Sensor Voltage: ");
  Serial.print(voltage); 
  Serial.println(" V");
  return int(voltage * 10);
}

void controlMotor( bool val ) {
  
}

void loop() {
  // is it pumping now
  if( state == 2 ){
      if( (millis() - startWateringTime) > PUMP_TIME){
        // stop the pump
        Serial.println("stop the pump");
        timeStamp = millis();
        state = 1;
        digitalWrite(motorControl, LOW);
      }
      return;
  }

  // should we check to see if we should pump?
  if( (millis() - timeStamp) < SAMPLE_DELAY){
    return;
  }
  
  timeStamp = millis();

  if( checkSoil() > 20){
    startWateringTime = millis();
    Serial.println("Start pumping");
    state = 2;
    digitalWrite(motorControl, HIGH);
  }
  
}
