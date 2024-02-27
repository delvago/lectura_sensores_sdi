#include <SDI12.h>//Version 2.1.4
#define SERIAL_BAUD 115200
#define DATA_PIN 25

/** Define the SDI-12 bus */
SDI12 mySDI12(DATA_PIN);

//String myCommand = "1R0!"; Estructura del código necesario para realizar una lectura SDI
/***********************/
/*********************************************************
 * VARIABLES GLOBALES
 ********************************************************/
 
/********************************************************/
/*********************************************************
 * FUNCIONES
 ********************************************************/
 /*********************************************************
 * Devuelve el valor de temperatura del suelo
 * solicitado de uno de los sensores Teros, necesita de 
 * la función getValue para funcionar
 ********************************************************/
String lectura_temperatura_suelo_teros(String sensor){
  String myCommand = sensor + "R0!";
  mySDI12.sendCommand(myCommand);
  delay(300);
  String respuesta_sensor = "";
  while(mySDI12.available()){
    char c = mySDI12.read();
    respuesta_sensor += c;  // Concatena cada caracter a la variable respuesta_sensor
  }
  String string_temperatura_sensor = "";
  string_temperatura_sensor = getValue(respuesta_sensor,'+',2);//index es 1 para humedad y 2 para temperatura en Teros12
  //double entero_temperatura_sensor = atof(string_temperatura_sensor.c_str());
  
 return string_temperatura_sensor;  
}
 /*********************************************************
 * Devuelve el valor de humedad del suelo
 * solicitado de uno de los sensores Teros, necesita de 
 * la función getValue para funcionar
 ********************************************************/
String lectura_humedad_suelo_teros(String sensor){
  String myCommand = sensor + "R0!";
  mySDI12.sendCommand(myCommand);
  delay(300);
  String respuesta_sensor = "";
  while(mySDI12.available()){
    char c = mySDI12.read();
    respuesta_sensor += c;  // Concatena cada caracter a la variable respuesta_sensor
  }
  String string_humedad_sensor = "";
  string_humedad_sensor = getValue(respuesta_sensor,'+',1);//index es 1 para humedad y 2 para temperatura en Teros12
  double entero_humedad_sensor = atof(string_humedad_sensor.c_str());
  double humedad_real = ((3.879e-4*entero_humedad_sensor)-0.6956)*100;//Formula para Teros
  String humedad_real_string = String(humedad_real,4);
  
 return humedad_real_string;
}
 /*********************************************************
 * Devuelve el valor de temperatura del suelo
 * solicitado de uno de los sensores Echo, necesita de 
 * la función getValue para funcionar
 ********************************************************/
String lectura_temperatura_suelo_echo(String sensor){
  String myCommand = sensor + "R0!";
  mySDI12.sendCommand(myCommand);
  delay(300);
  String respuesta_sensor = "";
  while(mySDI12.available()){
    char c = mySDI12.read();
    respuesta_sensor += c;  // Concatena cada caracter a la variable respuesta_sensor
  }
  String string_temperatura_sensor = "";
  string_temperatura_sensor = getValue(respuesta_sensor,'+',3);//index es 1 para humedad y 3 para temperatura en Echo Se necesita corroborar
  //double entero_temperatura_sensor = atof(string_temperatura_sensor.c_str());
  
 return string_temperatura_sensor;  
}
 /*********************************************************
 * Devuelve el valor de temperatura del suelo
 * solicitado de uno de los sensores Echo, necesita de 
 * la función getValue para funcionar
 ********************************************************/
 String lectura_humedad_suelo_echo(String sensor){
  String myCommand = sensor + "R0!";
  mySDI12.sendCommand(myCommand);
  delay(300);
  String respuesta_sensor = "";
  while(mySDI12.available()){
    char c = mySDI12.read();
    respuesta_sensor += c;  // Concatena cada caracter a la variable respuesta_sensor
  }
  String string_humedad_sensor = "";
  string_humedad_sensor = getValue(respuesta_sensor,'+',1);//index es 1 para humedad y 3 para temperatura en Echo Se necesita corroborar
  double entero_humedad_sensor = atof(string_humedad_sensor.c_str());
  double humedad_real = ((4.3e-6*pow(entero_humedad_sensor,3))-(5.5e-4*pow(entero_humedad_sensor,2))+(2.92e-2*entero_humedad_sensor)-(5.3e-2))*100;//Formula para Echo
  String humedad_real_string = String(humedad_real,4);
 return humedad_real_string;
}
/********************************************************* 
 * Obtiene los valores de Humedad o Temperatura del suelo 
 * del String que se obtiene de la lectura del sensor
 * mediante el protocolo SDI.
 ********************************************************/
String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "-1";
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial)
    ;
  Serial.println("Opening SDI-12 bus...");
  mySDI12.begin();
  delay(500);  // allow things to settle
}

void loop() {
  Serial.print("Temperatura del suelo Sensor 0: ");
  Serial.print(lectura_temperatura_suelo_teros("0"));
  Serial.println("°C");
  Serial.print("Humedad del suelo (VWC) Sensor 0: ");
  Serial.print(lectura_humedad_suelo_teros("0"));
  Serial.println("%");
  Serial.println("");

  Serial.print("Temperatura del suelo Sensor 1: ");
  Serial.print(lectura_temperatura_suelo_teros("1"));
  Serial.println("°C");
  Serial.print("Humedad del suelo (VWC) Sensor 1: ");
  Serial.print(lectura_humedad_suelo_teros("1"));
  Serial.println("%");
  Serial.println("");
  
  delay(2000);
}
