// This #include statement was automatically added by the Particle IDE.
#include "HttpClient/HttpClient.h"

HttpClient http;
int reading = 0;
int currts = 0;
double volts = 0.0;
int analogPin = A0;

http_header_t headers[] = {
//    { "Host", "ec2-35-166-193-108.us-west-2.compute.amazonaws.com" },
    { "Content-Type", "application/json" },
    { NULL, NULL }
};

http_request_t request;
http_response_t response;

void setup() {
    //pinMode(A0, INPUT);
    request.hostname = "ec2-35-166-193-108.us-west-2.compute.amazonaws.com";
    request.port = 4248;
    //request.path = "/api/put";
    Serial.begin(9600);
    Particle.variable("analog", reading);
    Particle.variable("volts", volts);
    Particle.variable("currts", currts);
}

void loop() {
  reading = analogRead(analogPin);
  volts = reading * 3.3 / 4096.0;
  //request.body = '[{\"metric\":\"lightVolts\",\"timestamp\":currts,\"value\":volts,\"tags\":{\"env\":\"test\"}}]';
  //http.post(request,response,headers);
  request.path = "/api/put";
  String jsonString = "{";
  jsonString += "\"metric\":\"lightVolts\",";
  jsonString += "\"timestamp\":";
  jsonString += String(Time.now());
  jsonString += String(millis()).substring(2,5);
  jsonString += ",\"value\":";
  jsonString += String(volts);
  jsonString += ",\"tags\":{\"env\":\"Stephens_Test\"}}";
  request.body = jsonString;
  http.post(request, response, headers);
  
  
  //{"metric":"lightVolts","timestamp":482815530172,"value":1.111011,"tags":{"env":"test"}}
  
  //request.body = '[{\"metric\":\"lightVolts\",\"timestamp\":Time.now(),\"value\":volts,\"tags\":{\"env\":\"test\"}}]' 
        
        //microString = microString + "lightVolts" + "," + String(Time.now()) + String(millis()).substring(2,5) + "," + String(volts) + " \n";
   // curl -d '[{\"metric\":\"lightVolts\",\"timestamp\":1482836116,\"value\":0.074934,\"tags\":{\"env\":\"test\"}}]'  http://ec2-35-166-193-108.us-west-2.compute.amazonaws.com:4248/api/put/;

  delay(500);
}
