#include <ESP8266WiFi.h>    // Biblioteca Wi-Fi
#include <DHT11.h>          // Biblioteca para o sensor DHT11

// Configurações do Wi-Fi
const char* ssid = "Wifi";          // Nome da sua rede Wi-Fi
const char* password = "Password";     // Senha da rede Wi-Fi

// IP do servidor local (substitua pelo IP do computador na rede local)
const char* serverIP = "192.000.0.000"; // IP do servidor localhost
const int serverPort = 8080;            // Porta do servidor

// Configuração do pino do sensor DHT11
#define DHT11_PIN 2
DHT11 dht11(DHT11_PIN);

WiFiClient client; // Cria o cliente Wi-Fi

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando...");

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado ao Wi-Fi!");
  Serial.print("IP Local do ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Lê a temperatura do DHT11
  int temperature = dht11.readTemperature();

  // Verifica erros de leitura
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Tenta conectar ao servidor
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Conectado ao servidor!");

      // Monta o conteúdo da requisição HTTP POST
      String postData = "temperature=" + String(temperature);

      // Envia a requisição HTTP
      client.println("POST /data");
      client.println("Host: " + String(serverIP) + ":" + String(serverPort));
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.println("Content-Length: " + String(postData.length()));
      client.println();
      client.print(postData);

      // Lê a resposta do servidor
      while (client.connected() || client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }

      client.stop(); // Finaliza a conexão
    } else {
      Serial.println("Falha ao conectar ao servidor.");
    }
  } else {
    Serial.println(DHT11::getErrorString(temperature));
  }

  delay(1000); // Aguarda 5 segundos antes da próxima leitura
}