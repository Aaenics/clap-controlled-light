int soundSensorPin = 4;  //connect this to pin DO of your sound sensor
int relay = 7;  //connect this to the postive terminal of your led

int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;
 
void setup() {
  pinMode(soundSensorPin, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600); // Initialize the Serial Monitor
}
 
void loop() {
  int status_sensor = digitalRead(soundSensorPin);
  if (status_sensor == 0)
  {
    if (clap == 0)
    {
      detection_range_start = detection_range = millis();
      clap++;
    }
    else if (clap > 0 && millis()-detection_range >= 50)
    {
      detection_range = millis();
      clap++;
    }
  }
  if (millis()-detection_range_start >= 400)
  {
    if (clap == 1)
    {
      if (!status_lights)
      {
        status_lights = true;
        digitalWrite(relay, HIGH);
      }
      else if (status_lights)
      {
        status_lights = false;
        digitalWrite(relay, LOW);
      }
      Serial.println("Clap Detected!"); // Print clap message to Serial Monitor
    }
    clap = 0;
  }
}
