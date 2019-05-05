#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define DEBUG true

#define USERBUTTON 12 // GPIO012 on ESP or D6 on WeMos
#define SLEEP_INTERVAL_DURATION  10e6 // 10 seconds
#define SLEEP_DURATION_ENGLISH String("10 seconds")
#define CURRENT_SLEEP_COUNT EEPROM.read(CURRENT_SLEEP_INTERVAL_ADDR)
#define MAX_SLEEP_COUNT 3 // 3*10 seconds = 30 seconds
#define CURRENT_SLEEP_INTERVAL_ADDR 30 // EEPROM address to store sleep interval
#define MAX_WIFI_RECONNECT_INTERVAL 20 // 20 seconds
#define MAX_AP_ON_MINUTES 1 // 1 minute

char ssid [50] = "secret";
char password [50] = "secret";
String AP_NamePrefix = "Cactus ";
const char WiFiAPPSK[] = "hutscape";
const char* DomainName = "cactus"; // set domain name domain.local

int userButtonValue = 1;
bool isAPWebServerRunning = false;
int apLoopCount = 0;

ESP8266WebServer server(80);

void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);

  disableWiFi();
  debugPrintln("");
  userButtonValue = digitalRead(USERBUTTON);

  debugPrintln("[INFO] Wakeup sleep count " + String(CURRENT_SLEEP_COUNT) + "/" + String(MAX_SLEEP_COUNT));

  if (!isCurrentSleepCountMax() && !hasUserPressedButton(userButtonValue)) {
    increaseSleepCount();
    debugPrintln("[INFO] Going into deep sleep for " + SLEEP_DURATION_ENGLISH);
    goToSleep();
    return;
  }

  resetSleepCount();

  if (hasUserPressedButton(userButtonValue)) {
    debugPrintln("[INFO] Wakeup on user button press!");
  }

  enableWiFi();
  bool isConnectedToWiFi = connectToWiFi(true);
  if (isConnectedToWiFi) {
    debugPrintln("[INFO] Connected succesfully to WiFi SSID " + WiFi.SSID());
    debugPrintln("[INFO] WiFi connected! IP address: " + WiFi.localIP().toString());
  } else {
    debugPrintln("[ERROR] Connection to WiFi failed");
    debugPrintln("[INFO] Configuring access point");
    initAccessPoint();
    debugPrintln("[INFO] Started access point at IP " + WiFi.softAPIP().toString());

    bool hasMDNSStarted = MDNS.begin(DomainName, WiFi.softAPIP());
    if (!hasMDNSStarted) {
      debugPrintln("[ERROR] mDNS has failed to start");
    }

    startServer();
    debugPrintln("[INFO] WiFi is not configured!");
    debugPrintln("[INFO] Connect to SSID 'Cactus NNNN'");
    debugPrintln("[INFO] Go to http://192.168.4.1");
  }
}

void loop() {
  // TODO: Erase Wifi Credentials via Serial commands

  if (isAPWebServerRunning) {
    MDNS.update();
    server.handleClient();

    if (++apLoopCount > MAX_AP_ON_MINUTES*600) {
      debugPrintln("[INFO] Going into deep sleep for " + SLEEP_DURATION_ENGLISH);
      goToSleep();
    }
    delay(100);
  } else {
    doTask();
    debugPrintln("[INFO] Going into deep sleep after task for " + SLEEP_DURATION_ENGLISH);
    goToSleep();
  }
}

// Print functions
void debugPrintln(String s) {
  if (DEBUG) {
    Serial.println(s);
  }
}

void debugPrint(String s) {
  if (DEBUG) {
    Serial.print(s);
  }
}

void doTask() {
  debugPrintln("[INFO] Do task");
}

// EEPROM functions
bool isCurrentSleepCountMax() {
  return CURRENT_SLEEP_COUNT >= MAX_SLEEP_COUNT;
}

void increaseSleepCount() {
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, CURRENT_SLEEP_COUNT + 1);
  EEPROM.commit();
}

void resetSleepCount() {
  EEPROM.write(CURRENT_SLEEP_INTERVAL_ADDR, 0);
  EEPROM.commit();
}

// Sensor functions
bool hasUserPressedButton(int userButtonValue) {
  return userButtonValue == 0;
}

// Sleep and Wakup functions
void goToSleep() {
  // WiFi.disconnect( true );
  // delay(1);

  ESP.deepSleep(SLEEP_INTERVAL_DURATION, WAKE_RF_DISABLED);
}

// WiFi functions
void enableWiFi() {
  WiFi.forceSleepWake(); // wakeup WiFi modem
  delay(1);
}

void disableWiFi() {
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
}

bool connectToWiFi(bool useCredsFromFlash) {

  if (useCredsFromFlash){
    WiFi.begin();
  } else{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }


  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    if (++count % 10 == 0) {
      debugPrintln(".");
    } else {
      debugPrint(".");
    }

    if (count >= MAX_WIFI_RECONNECT_INTERVAL) {
      if (count % 10 != 0){
        debugPrintln("");
      }
      return false;
    }
  }

  if (count % 10 != 0){
    debugPrintln("");
  }

  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  return true;
}

void initAccessPoint() {
  // TODO: Blink LED to indicate that user has to put in the credentials in AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(createAPName().c_str(), WiFiAPPSK);
}

String createAPName() {
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  return AP_NamePrefix + macID;
}

void startServer() {
  server.on("/", handleRoot);

  const char * headerkeys[] = {"User-Agent","Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);

  server.collectHeaders(headerkeys, headerkeyssize );
  server.begin();

  isAPWebServerRunning = true;
}

void handleRoot() {
  if (server.hasArg("ssid") && server.hasArg("password") && server.hasArg("key")){
    String receivedSSID = server.arg("ssid");

    debugPrintln("[INFO] WiFi SSID received: " + receivedSSID);
    receivedSSID.toCharArray(ssid, 50);

    debugPrintln("[INFO] WiFi password received");
    server.arg("password").toCharArray(password, 50);

    debugPrintln("[INFO] IFTTT key received!");
    // writeKey(server.arg("key"));

    bool hasConectedToWifi = connectToWiFi(false);

    if (!hasConectedToWifi) {
      Serial.println("[ERROR] Cannot connect to WiFi after AP mode!");
      server.sendHeader("Location","/");
      server.sendHeader("Cache-Control","no-cache");
      server.sendHeader("Set-Cookie","ESPSESSIONID=1");
      server.send(301);
      return;
    }

    debugPrintln("[INFO] Connected to WiFi after AP mode!");
    // TODO: Redirect to a success page
    server.send(200);
    delay(1);

    isAPWebServerRunning = false;
    return;
  }

  returnConfigPage();
}

void returnConfigPage() {
  String content = "<html><body><form action='/' method='post'>";

  content += "<h1>Welcome to Cactus@Hutscape</h1>";
  content += "<p>WiFi SSID: <input type='text' name='ssid' placeholder='ssid'></p>";
  content += "<p>WiFi Password:<input type='password' name='password' placeholder='secret'></p>";

  content += "<p>IFTTT Key:<input type='text' name='key' placeholder='IFTTT Key'></p>";
  // IFTTT key from https://ifttt.com/services/maker_webhooks/settings
  // https://maker.ifttt.com/use/{key}

  content += "<input type='submit' name='submit' value='Submit'></form></body></html>";
  server.send(200, "text/html", content);
}
