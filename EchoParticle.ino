int LED = D0;

int OFF = 0;
int ON = 1;
int alert = OFF;

void setup() {
  pinMode(LED, OUTPUT);
  Particle.variable("alert", alert);
  // invoke with
  // ON
  // curl https://api.particle.io/v1/devices/36003f001047343438323536/alert -d access_token=123412341234 -d "args=on"
  // OFF
  // curl https://api.particle.io/v1/devices/36003f001047343438323536/alert -d access_token=123412341234 -d "args=off"
  //
  Particle.function("alert", setAlert);

  // COUPLING - events come from garagedoor app/device!
  Particle.subscribe("door-opened", evOpenedHandler, MY_DEVICES);
  Particle.subscribe("door-closed", evClosedHandler, MY_DEVICES);
}

void evOpenedHandler(const char *event, const char *data) {
    alert = ON;
}

void evClosedHandler(const char *event, const char *data) {
    alert = OFF;
}

void loop() {
  if (alert) {
      flashLED(5,2);
  }
  delay(300);
}

// Cloud functions must return int and take one String
int setAlert(String extra) {
  if (extra == "on") {
    alert = ON;
  } else {
    alert = OFF;
  }
  return 1; // success
}

// Turn on the LED briefly, n times in quick succession
void flashLED(int n, int d) {
  for (int i=0; i<n; i++) {
    digitalWrite(LED, HIGH);
    delay(d*50);
    digitalWrite(LED, LOW);
    delay(d*50);
  }
}