# Monitoramento de Temperatura

Este projeto tem como objetivo consolidar o aprendizado sobre conexão Wi-Fi utilizando o NodeMCU ESP32 para envio de dados de temperatura, coletados pelo sensor DHT11, para um servidor Node.js. Os dados podem ser monitorados em tempo real através de uma interface web.

---

## Materiais Utilizados

- **Hardware:**
  - NodeMCU ESP32;
  - Sensor de temperatura DHT11;
  - Cabos de conexão.

- **Software:**
  - IDE Arduino (para programação do ESP32);
  - Visual Studio Code (opcional, para editar o servidor Node.js);
  - Node.js (para executar o servidor).

---

## Funcionalidades

1. Leitura da temperatura ambiente pelo sensor DHT11 conectado ao ESP32.
2. Envio dos dados via HTTP POST para um servidor Node.js.
3. Atualização em tempo real da temperatura através de uma interface web usando WebSockets.

---

## Configuração do Projeto

### **1. Preparação do Hardware**

1. Conecte o sensor DHT11 ao NodeMCU ESP32:
   - **VCC** → Pino 3V3 do ESP32.
   - **GND** → GND do ESP32.
   - **Data** → Pino GPIO2 (ou conforme configurado no código).

2. Certifique-se de que o NodeMCU ESP32 esteja conectado à rede Wi-Fi para envio dos dados.

---

### **2. Configuração do Software**

#### **ESP32**

1. Instale a [IDE Arduino](https://www.arduino.cc/en/software).
2. Configure a IDE para programar o ESP32:
   - Adicione o gerenciador de placas do ESP32 no menu **File > Preferences**.
   - Instale as bibliotecas necessárias, como `DHT11` e `ESP8266WiFi` (ou `WiFi` para ESP32).
3. No arquivo `code.ino`:
   - Configure o nome da rede Wi-Fi (`SSID`) e a senha.
   - Compile e envie o código para o ESP32.

#### **Servidor Node.js**

1. Certifique-se de ter o [Node.js](https://nodejs.org) instalado.
2. Faça o download do projeto.
3. Navegue até a pasta do servidor no terminal e execute:
   ```bash
   npm install
4. Inicie o servidor:
   ```bash
   node index.js
---
#### **Interface Web**
1. Acesse o **index.html** no navegador para visualizar a interface de monitoramento.
2. O servidor e a interface exibirão os dados enviados pelo ESP32 em tempo real.

## 3. Estrutura do Projeto

- **`code.ino`**: Código Arduino para leitura da temperatura e envio dos dados para o servidor.
- **`server.js`**: Código Node.js para receber dados do ESP32 e transmitir via WebSocket.
- **`public/index.html`**: Interface web para visualização dos dados em tempo real.

### Outros arquivos:
- **`package.json`**: Gerenciamento de dependências Node.js.

---

Com isso, você terá um sistema funcional de monitoramento de temperatura com ESP32, Node.js e WebSockets. 🚀