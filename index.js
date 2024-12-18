const express = require("express");
const bodyParser = require("body-parser");
const WebSocket = require("ws");

const app = express();
const port = 8080;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static("public")); // Para servir arquivos estáticos

let lastTemperature = null; // Armazena a última temperatura recebida

// Servidor WebSocket
const wss = new WebSocket.Server({ noServer: true });

// Handle WebSocket connections
wss.on("connection", (ws) => {
  console.log("Cliente conectado via WebSocket");
  ws.send(JSON.stringify({ temperature: lastTemperature || "Nenhuma temperatura recebida ainda" }));
});

// Recebe os dados do ESP32 e transmite via WebSocket
app.post("/data", (req, res) => {
  lastTemperature = req.body.temperature;
  console.log(`Temperatura recebida: ${lastTemperature} °C`);

  // Envia para os clientes WebSocket
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify({ temperature: lastTemperature }));
    }
  });

  res.status(200).send("Dados recebidos com sucesso!");
});

// Configura o servidor HTTP para suportar WebSockets
const server = app.listen(port, () => {
  console.log(`Servidor rodando em http://localhost:${port}`);
});

server.on("upgrade", (request, socket, head) => {
  wss.handleUpgrade(request, socket, head, (ws) => {
    wss.emit("connection", ws, request);
  });
});
