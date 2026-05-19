#include <Arduino.h>
#include "config.h"
#include "wifi_manager.h"
#include "ble_provisioning.h"
#include "mqtt_client.h"
#include "sensors.h"

static bool bleMode = false;
unsigned long lastSensorPublish = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n--- Centro de Productividad IoT ---");

    sensors_init();

    if (wifi_has_credentials()) {
        bool connected = wifi_connect();
        if (!connected) {
            Serial.println("Boot: No se pudo conectar. Borrando credenciales y entrando en modo BLE...");
            wifi_clear_credentials();
            bleMode = true;
            ble_provisioning_start();
        } else {
            mqtt_init();
        }
    } else {
        bleMode = true;
        ble_provisioning_start();
    }

    Serial.println("--- SISTEMA LISTO ---");
}

void loop() {
    if (bleMode) {
        if (ble_provisioning_loop()) {
            Serial.println("Provisioning completo. Reiniciando...");
            delay(1000);
            ESP.restart();
        }
        return;
    }

    // Normal WiFi + MQTT operation
    wifi_loop();

    if (wifi_is_connected()) {
        mqtt_loop();

        if (capturing) {
            unsigned long now = millis();
            if (now - lastSensorPublish >= SENSOR_INTERVAL) {
                lastSensorPublish = now;

                char buffer[512];
                unsigned long ts = get_current_ts();
                if (sensors_to_json(buffer, sizeof(buffer), ts)) {
                    if (mqtt_publish(buffer)) {
                        Serial.printf("MQTT: Publicado -> %s\n", buffer);
                    }
                }
            }
        }
    }
}
