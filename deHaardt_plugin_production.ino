// Load Wi-Fi library
#include <WiFi.h>
/*==========================================================================================*/
//Wifi connection and request handling variables
// Replace with your network credentials
const char* ssid     = "Lenovo A7000-a";
const char* password = "ceb4bcee4f7b";
// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;
int stringIndex=0;
String transponderCode="";
String reqSpeed="F";
int transpnderNum=-1;
int _speed=0;
/*==========================================================================================*/
int stringToNum(String string){ //auxiliary function to convert srings to integers
  int value=-1;
  //value = atoi(string);
  value=string.toInt();
  return(value);
}
/*==========================================================================================*/
//Remote control handling Code
//global variables for remote control keypad decoding
int row=0;
int col=0;
int GPIOports[]={0,4,16,17,5,18,19,21,3,1}; //GPIO ports to run on an ESP32
//int GPIOports[]={22,23,24,25,26,27,28,29,30,31};  //GPIO ports to run on an arduino Mega
char start='n';
char LastKey='0';
char keyPressed='0';

void combLUT(char key){ //keypad grid decoding lookup table
   switch (key){
    
    case '1':
      row=5;
      col=1;
      break;
    
    case '2':
     row=5;
     col=2;
     break;
    
    case '3':
     row=5;
     col=3;
     break;
    
    case '4':
     row=4;
     col=1;
     break;
     
    case '5':
     row=4;
     col=2;
     break;

    case '6':
     row=4;
     col=3;
     break;

    case '7':
     row=7;
     col=1;
     break;

    case '8':
     row=7;
     col=2;
     break;

    case '9':
     row=7;
     col=3;
     break;

    case 'L':
     row=8;
     col=1;
     break;

    case 'S':
     row=8;
     col=2;
     break;

    case 'R':
     row=8;
     col=3;
     break;

    case 'P':
     row=9;
     col=1;
     break;

    case 'M':
     row=9;
     col=2;
     break;
    
    case 'H':
     row=9;
     col=6;
     break;

    case 'X':
     row=9;
     col=3;
     break;

    case 'A':
     row=10;
     col=1;
     break;

    case 'B':
     row=10;
     col=2;
     break;

    case 'C':
     row=10;
     col=6;
     break;

    case 'D':
     row=10;
     col=3;
     break;
    default:
      row=0;
      col=0;
      break;
   } 
    
}

void execute(int r, int c){
  digitalWrite(GPIOports[r-1],LOW);
  digitalWrite(GPIOports[c-1],LOW);
  delay(1000);
  digitalWrite(GPIOports[r-1],HIGH);
  digitalWrite(GPIOports[c-1],HIGH);  
  Serial.print("column\t");
  Serial.print(c);
  Serial.print("\nrow\t");
  Serial.print(r);
  Serial.print("\n");
}

void kart_num_speed_change(int transponderNo,int _speed){
  char currentSpeed='n';
  if (_speed==1){
    currentSpeed='P';   
  } else if(_speed==2){
    currentSpeed='M';
  } else if(_speed==3){
    currentSpeed='H';
  } else if(_speed==4){
    currentSpeed='X';
  }
  switch (transponderNo){
      case 90:
        combLUT('1');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
      
      case 91:
        combLUT('3');
        execute(row, col);
        combLUT('2');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
      
      case 92:
        combLUT('3');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
        
      case 93:
        combLUT('4');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
      
      case 94:
        combLUT('5');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
        
      case 95:
        combLUT('6');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
      
      case 96:
        combLUT('7');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
      
      case 97:
        combLUT('8');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
        
      case 98:
        combLUT('9');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
        
      case 99:
        combLUT('1');
        execute(row, col);
        combLUT('1');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
        
      case 0:
        combLUT('1');
        execute(row, col);
        combLUT('2');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
        
      case 49:
        combLUT('3');
        execute(row, col);
        combLUT('1');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
        
      case 50:
        combLUT('1');
        execute(row, col);
        combLUT('4');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
        
      case 76:
        combLUT('1');
        execute(row, col);
        combLUT('5');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
      
      case 77:
        combLUT('1');
        execute(row, col);
        combLUT('6');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
      
      case 79:
        combLUT('1');
        execute(row, col);
        combLUT('7');
        execute(row, col);
        combLUT(currentSpeed);
        execute(row, col);
        break;
      
      default:
        break;
  }
}
/*=======================================================================*/
//initial setup
void setup() {
  Serial.begin(115200);
  Serial.println("GPIO pins setup...\n");
    for (int i=0; i<10; i++){
    pinMode(GPIOports[i],OUTPUT);
    digitalWrite(GPIOports[i],LOW);
    delay(100);
    digitalWrite(GPIOports[i],HIGH);
  }
  Serial.println("Ready !!\n");
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------");
  server.begin();
}
void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            Serial.print("Header length \t");
            Serial.print(header.length());
            Serial.print("\n");
            stringIndex= header.indexOf("/");
            transponderCode += header[stringIndex+1];
            transponderCode += header[stringIndex+2];
            reqSpeed[0]=header[stringIndex+3];
            Serial.print("Transponder#\t");
            Serial.print(transponderCode);
            Serial.print("\nRequested Speed\t");
            Serial.print(reqSpeed);
            Serial.print("\n");
            transpnderNum=stringToNum(transponderCode);
            _speed=stringToNum(reqSpeed);
            kart_num_speed_change(transpnderNum,_speed);
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // Web Page Heading
            client.println("<body><h1>Request OK</h1>");
            client.println("<h1>Kart transponder#: ZDPAE"+transponderCode+"</h1>");
            client.println("<h1>Speed:"+reqSpeed+"</h1>");
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    //reset all container variables
    stringIndex=0;
    transponderCode="";
    reqSpeed="F";
    _speed=-1;
    Serial.println("Client disconnected.");
    Serial.println("---------------------------");
  }
}
