#include "WiFi.h"

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("\n🌐 WiFi Scanner Initialized...");
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  Serial.println("\n🔍 Scanning for WiFi networks...");
  Serial.println("=====================================");

  int numNetworks = WiFi.scanNetworks();

  if (numNetworks == 0) {
    Serial.println("❌ No networks found.");
  } else {
    Serial.printf("✅ Found %d networks:\n\n", numNetworks);
    
    for (int i = 0; i < numNetworks; i++) {
      Serial.printf("📶 [%d] SSID: %s\n", i + 1, WiFi.SSID(i).c_str());
      Serial.printf("   🔹 Signal Strength: %d dBm %s\n", 
                    WiFi.RSSI(i), getSignalStrength(WiFi.RSSI(i)));
      Serial.printf("   🔒 Encryption: %s\n\n", 
                    (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "🔓 Open" : "🔐 Secured");
    }
  }

  Serial.println("=====================================");
  Serial.println("⏳ Next scan in 10 seconds...");
  
  delay(10000);
}

const char* getSignalStrength(int rssi) {
  if (rssi >= -50) return "📡 Excellent";
  if (rssi >= -60) return "👍 Good";
  if (rssi >= -70) return "👌 Fair";
  if (rssi >= -80) return "⚠️ Weak";
  return "❌ Very Weak";
}
