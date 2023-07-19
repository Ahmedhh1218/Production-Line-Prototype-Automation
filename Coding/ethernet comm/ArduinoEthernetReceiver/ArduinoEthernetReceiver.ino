#include <EtherCard.h>
#include <IPAddress.h>
const int x;
/* Addresses */
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 }; // mac address
static byte myip[] = { 192, 168, 1, 3 }; // ethernet interface ip address
static byte gwip[] = { 192, 168, 1, 1 }; // gateway ip address
static byte mask[] = { 255, 255, 255, 0 };// subnet mask
// ports
const int dstPort PROGMEM = 1234;

/* Buffer */
byte Ethernet::buffer[700];

void initializeEthernet()
{
  // Begin Ethernet communication
  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0)  // if using Mega use value 53 if using uno use value 10
  { Serial.println("Failed to access Ethernet controller");
    return;}
    
  // Setup static IP address
  ether.staticSetup(myip, gwip, 0, mask);

  // Log configuration
  Serial.println(F("\n[Receiver]"));
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
}

/* callback that prints received packets to the serial port */
void udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len){
  IPAddress src(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);

  Serial.println(data);   // print the data send );
  if(data=='metal')       // dummy condition just for testing
   {int x =0;
  Serial.println(x);
}}



void setup(){

  // Initialize Serial
  Serial.begin(57600); // can be 9600 or any baud rate

  // Initialize Ethernet
  initializeEthernet();
  
  //register udpSerialPrint() to destination port (callback function)
  ether.udpServerListenOnPort(&udpSerialPrint, dstPort);
}

void loop(){
  // receive packets, get ready for callbacks
  ether.packetLoop(ether.packetReceive());
}
