# Centro de Productividad IoT — Firmware ESP32

Firmware para el ESP32 del proyecto. Recolecta datos de sensores (temperatura, humedad, luz, sonido, distancia) y los publica por MQTT.

---

## Requisitos

- [VS Code](https://code.visualstudio.com/) con la extensión [PlatformIO](https://platformio.org/install/ide?install=vscode)
- Cable USB (el ESP32 usa micro-USB)
- La app del proyecto instalada en tu celular

---

## Instalación del driver USB

Antes de conectar el ESP32, instalá el driver según tu placa:

- **CH340** (placa azul genérica): ejecutá `drivers/CH340_Driver_Instalador.exe`
- **CP210x** (placa negra DOIT): ejecutá `drivers/CP210x/UpdateParam.bat` como administrador

Reiniciá la PC después de instalar.

---

## Flashear el ESP32

1. Cloná este repo:
   ```
   git clone https://github.com/vonluna-nt/centro-productividad-firmware.git
   ```

2. Abrí la carpeta en VS Code. PlatformIO va a detectar el proyecto automáticamente.

3. Conectá el ESP32 por USB.

4. En la barra inferior de VS Code, hacé clic en **Upload** (flecha →).

5. Esperá a que diga `SUCCESS`. Listo.

---

## Configurar el WiFi desde la app

El ESP32 **no tiene WiFi configurado de fábrica**. Al encenderlo por primera vez (o en una red nueva), entra en modo Bluetooth para recibir las credenciales.

1. Abrí la app en tu celular.
2. Buscá el dispositivo **"CentroProductividad"** en la lista de BLE.
3. Ingresá tu red WiFi y contraseña.
4. El ESP32 se reinicia solo y se conecta.

> Si el ESP32 ya estaba en otra red y no encuentra el WiFi guardado, entra automáticamente en modo Bluetooth para que puedas configurarlo de nuevo.

---

## Sensores conectados

| Sensor | Pin |
|--------|-----|
| DHT (temperatura y humedad) | GPIO 13 |
| LDR (luz) | GPIO 35 |
| KY-037 (sonido) | GPIO 34 |
| VL53L0X (distancia) | SDA GPIO 21 / SCL GPIO 22 |

---

## Solución de problemas

**No aparece el puerto COM en VS Code**
→ Verificá que el driver esté instalado y reiniciá la PC.

**Error al subir: "No serial data received"**
→ Mantené apretado el botón BOOT del ESP32 mientras PlatformIO empieza a subir, soltalo cuando veas los puntos `....`.

**No aparece "CentroProductividad" en la app**
→ Asegurate de que el ESP32 esté encendido y que no tenga WiFi configurado (o que la red guardada no esté disponible).
