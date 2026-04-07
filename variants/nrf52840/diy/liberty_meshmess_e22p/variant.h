#pragma once

/*
 * Liberty MeshMess 0.1.1 + nRF52840 Pro Micro + E22-900M30S / E22P-868M30S
 *
 * Updated draft based on Liberty MeshMess schematic:
 * - standard SX126x SPI/BUSY/DIO1/RESET wiring
 * - RF switching handled by board hardware from DIO2
 * - do NOT define explicit TXEN/RXEN MCU pins
 *
 * Notes:
 * - E22-900M30S / E22P-868M30S needs solid 5V power
 * - start testing with low TX power in Meshtastic config
 */

/* ---------- Board identity ---------- */
#define VARIANT_NAME "liberty_meshmess_e22p"
#define HAS_SCREEN 0
#define HAS_BUTTON 0
#define HAS_GPS 0
#define HAS_TELEMETRY 0
#define HAS_SENSOR 0

/* ---------- Radio ---------- */
#define USE_SX1262

/*
 * Liberty MeshMess uses discrete logic to convert SX126x DIO2 into TXEN/RXEN
 * for the E22-900M30S front-end. Therefore DIO2 RF switching should stay enabled.
 */
#define SX126X_DIO2_AS_RF_SWITCH 1

/* Standard nRF52 Pro Micro DIY style mapping used by Liberty MeshMess */
#define LORA_SCK    43   // P1.11
#define LORA_MISO   2    // P0.02
#define LORA_MOSI   47   // P1.15
#define LORA_CS     45   // P1.13
#define LORA_RESET  9    // P0.09
#define LORA_BUSY   29   // P0.29
#define LORA_DIO1   10   // P0.10

/* No direct MCU TXEN/RXEN control on this board */
// #define SX126X_TXEN ...
// #define SX126X_RXEN ...

/* ---------- Serial ---------- */
#ifndef PIN_SERIAL_RX
#define PIN_SERIAL_RX 8
#endif

#ifndef PIN_SERIAL_TX
#define PIN_SERIAL_TX 6
#endif

/* ---------- I2C ---------- */
#ifndef I2C_SDA
#define I2C_SDA 20
#endif

#ifndef I2C_SCL
#define I2C_SCL 24
#endif

/* ---------- Optional indicators ----------
 * Uncomment only after confirming actual assembly options.
 */
// #define LED_PIN 13
// #define LED_STATE_ON 1

/* ---------- Optional battery measurement ----------
 * Leave disabled until actual analog routing is confirmed on your board.
 */
// #define BATTERY_PIN A0
// #define ADC_MULTIPLIER 2.0f

/*
 * Meshtastic runtime suggestions for first bring-up:
 *   region   = EU_868
 *   tx_power = 10
 */
