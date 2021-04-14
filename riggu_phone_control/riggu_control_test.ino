#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>   // For using server 


#define pwmB D1
#define pwmC D2

D5
#define dirB D6
#define dirC D7

const char* ssid    = "Riggu";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "20212021"

ESP8266WebServer server(80);


// B is left most 
// C is right most
int s=255;

void right(){
  digitalWrite(dirB,0);
  analogWrite(pwmB,s);
  digitalWrite(dirC,0);
  analogWrite(pwmC,s);  
  server.send(200,"text/plain","moving right");
}


void left(){
  Serial.println("left");

  digitalWrite(dirB,1);
  analogWrite(pwmB,s);
  digitalWrite(dirC,1);
  analogWrite(pwmC,s);
  server.send(200,"text/plain","moving left");  
}

void forward(){
  analogWrite(pwmA,0);
  digitalWrite(dirB,0);
  analogWrite(pwmB,s);
  digitalWrite(dirC,1);
  analogWrite(pwmC,s);  
  server.send(200,"text/plain","moving forward");
}


void backward(){
  Serial.println("back");

  digitalWrite(dirB,1);
  Serial.println(s/sqrt(3));
  analogWrite(pwmB,s/sqrt(3));
  digitalWrite(dirC,0);
  analogWrite(pwmC,s/sqrt(3));  
  server.send(200,"text/plain","moving backward");
}


void rotation_clockwise(){

  digitalWrite(dirB,0);
  analogWrite(pwmB,s);
  digitalWrite(dirC,0);
  analogWrite(pwmC,s);  
  server.send(200,"text/plain","turning clockwise");
}


void rotation_anticlock(){
  digitalWrite(dirB,1);
  analogWrite(pwmB,s);
  digitalWrite(dirC,1);
  analogWrite(pwmC,s);  
  server.send(200,"text/plain","turning anticlock");
}


void stap(){
  Serial.println("Stopping");
  analogWrite(pwmB,0);
  analogWrite(pwmC,0);
  server.send(200,"text/plain","stopping");
}

void speedControl(){
  Serial.println("speed");
  s= server.arg("val").toInt();
  server.send(200,"text/plain","speed changed to " + server.arg("val"));
}

void setup() {
Serial.begin(9600);
pinMode(dirB,OUTPUT);
pinMode(dirC,OUTPUT);

pinMode(pwmB,OUTPUT);
pinMode(pwmC,OUTPUT);

Serial.println('\n');
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { 
   delay(500);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  server.on("/forward", forward);
  server.on("/reverse", backward);
  server.on("/stop", stap);
  server.on("/left", left);
  server.on("/right", right);
  server.on("/speed", speedControl);
  server.on("/cw",rotation_clockwise);
  server.on("/ccw",rotation_anticlock);

  server.begin();
}

void loop() {
  server.handleClient();
}
