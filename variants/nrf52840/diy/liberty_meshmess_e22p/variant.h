#ifndef _VARIANT_LIBERTY_MESHMESS_E22P_
#define _VARIANT_LIBERTY_MESHMESS_E22P_

#define VARIANT_MCK (64000000ul)
#define USE_LFRC

#include "WVariant.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PINS_COUNT           (48)
#define NUM_DIGITAL_PINS     (48)
#define NUM_ANALOG_INPUTS    (1)
#define NUM_ANALOG_OUTPUTS   (0)

/*
 * Liberty MeshMess 0.1.1 + nRF52840 Pro Micro + E22-900M30S / E22P-868M30S
 *
 * Based on the Liberty MeshMess schematic:
 * - standard SX126x SPI/BUSY/DIO1/RESET wiring
 * - RF switching handled by external logic from DIO2
 * - no direct MCU TXEN/RXEN control
 * - no onboard GPS or screen
 */

/* Board identity */
#define VARIANT_NAME         "liberty_meshmess_e22p"
#define HAS_SCREEN           0
#define HAS_BUTTON           0
#define HAS_GPS              0
#define HAS_TELEMETRY        0
#define HAS_SENSOR           0

/* Serial */
#define PIN_SERIAL_RX        (0 + 8)
#define PIN_SERIAL_TX        (0 + 6)
#define PIN_SERIAL2_RX       (0 + 6)
#define PIN_SERIAL2_TX       (0 + 8)
#define PIN_SERIAL1_RX       (-1)
#define PIN_SERIAL1_TX       (-1)

/* I2C */
#define WIRE_INTERFACES_COUNT 1
#define PIN_WIRE_SDA         (0 + 20)
#define PIN_WIRE_SCL         (0 + 24)

/* SPI */
#define SPI_INTERFACES_COUNT 1
#define PIN_SPI_MISO         (0 + 2)
#define PIN_SPI_MOSI         (32 + 15)
#define PIN_SPI_SCK          (32 + 11)

#define LORA_MISO            PIN_SPI_MISO
#define LORA_MOSI            PIN_SPI_MOSI
#define LORA_SCK             PIN_SPI_SCK

/* Radio */
#define USE_SX1262

#define SX126X_CS            (32 + 13)
#define SX126X_DIO1          (0 + 10)
#define SX126X_BUSY          (0 + 29)
#define SX126X_RESET         (0 + 9)

#define LORA_CS              SX126X_CS
#define LORA_DIO1            SX126X_DIO1
#define LORA_BUSY            SX126X_BUSY
#define LORA_RESET           SX126X_RESET

/*
 * Liberty MeshMess uses discrete logic to derive TX/RX switching from DIO2,
 * so Meshtastic should let the SX126x drive RF switching on DIO2 directly.
 */
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_RXEN          RADIOLIB_NC
#define SX126X_TXEN          RADIOLIB_NC

/*
 * E22P-class modules on this board need DIO3 TCXO drive enabled.
 * Keep the current limit aligned with the working yomama_e22p bring-up.
 */
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#define SX126X_CURRENT_LIMIT 140

/* LED and battery */
#define PIN_LED1             (0 + 15)
#define LED_BLUE             PIN_LED1
#define LED_STATE_ON         1
// #define BATTERY_PIN        (0 + 31)

#ifdef __cplusplus
}
#endif

#endif
