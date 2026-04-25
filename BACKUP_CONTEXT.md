# Záložní Kontext

## Rozsah
- Repo: `/home/codex/firmware`
- GitHub fork: `norman67cz/firmware`
- Build server: `10.5.0.146`
- Hlavní deska: `yomama_e22p`
- Související deska: `liberty_meshmess_e22p`
- Větev s úpravami MQTT: `mqtt_custom`

## Aktuální Heady Větví
- `mqtt_custom` -> `b4b05deb8`
- `yomama_e22p` -> `ce4466c94`
- `liberty_meshmess_e22p` -> `ee064c4d3`

Tohle byly poslední potvrzené synchronní heady po merge každé větve s `origin/develop`.

## Hardwarové Poznámky k yomama_e22p
- MCU: nRF52840 ProMicro
- Radio: E22P-868M30S / SX1262
- Kritické zapojení:
  - `E22P_EN` na `P0.17`
  - `T/R CTRL` připojeno na `DIO2`
- Kritická firmware nastavení:
  - `SX126X_DIO3_TCXO_VOLTAGE = 1.8`
  - `SX126X_CURRENT_LIMIT = 140`

### Root Cause Rádia
Původní chyba inicializace rádia `-707` byla způsobená chybějícím TCXO bring-up pro E22P. Po doplnění DIO3 TCXO nastavení na `1.8V` začala fungovat inicializace rádia, RX i normální příjem paketů.

## Bare Build pro yomama_e22p
Účel:
- udržet firmware co nejmenší
- zachovat rádio, BLE, synchronizaci z telefonu a vybrané senzory/moduly

Hlavní výsledky:
- BLE funguje
- párování s telefonem funguje
- synchronizace času z telefonu funguje
- přímé zprávy fungují
- traceroute funguje
- podpora INA je přítomná
- vybrané teplotní a tlakové senzory jsou přítomné

### Důležité Opravy Během Ladění
- `AdminModule` musel být přítomný kvůli synchronizaci času z telefonu
- `PKI` muselo být vrácené kvůli přímým zprávám
- `TextMessageModule` musel zůstat dostupný
- `I2C` muselo zůstat zapnuté kvůli podpoře INA

### Moduly Vrácené do Bare Buildu
- `AdminModule`
- `TextMessageModule`
- `NeighborInfo`
- `Traceroute`
- `PKI` / `KeyVerificationModule`
- `INA219`
- `INA226`
- `INA260`
- `INA3221`
- Podpora teplotních a tlakových senzorů:
  - `AHT10`
  - `BME280`
  - `BMP085`
  - `BMP280`
  - `BMP3XX`
  - `DPS310`
  - `LPS22HB`
  - `MCP9808`
  - `PCT2075`
  - `SHTxx`

### Poznámka k Baterii
- Při napájení jen přes USB byly hodnoty baterie neplatné nebo zavádějící.
- S připojenou skutečnou baterií dávala battery telemetrie smysluplné hodnoty.

## Větev mqtt_custom
Hlavní soubor:
- `src/mqtt/MQTT.cpp`

Co se změnilo v `mqtt_custom`:
- odstranilo se packet-level filtrování `OK_TO_MQTT` pro slyšené pakety
- povolilo se odesílání encrypted / undecoded paketů do MQTT

Co stále zůstává aktivní:
- anti-loop: `via_mqtt`
- alespoň jeden kanál musí mít `uplink_enabled`
- per-channel podmínka:
  - `ch.settings.uplink_enabled || isPKIEncrypted`
- special-case blokace některých typů paketů na default/public MQTT
- publish stále závisí na dostupnosti MQTT linku

Pokud bude cílem v budoucnu posílat do MQTT opravdu úplně vše slyšené z LoRa, další kandidát na odstranění je per-channel podmínka `uplink_enabled` v `src/mqtt/MQTT.cpp`.

## liberty_meshmess_e22p
Tohle je teď skutečná board větev, ne jen draft.

Relevantní soubory:
- `variants/nrf52840/diy/liberty_meshmess_e22p/platformio.ini`
- `variants/nrf52840/diy/liberty_meshmess_e22p/variant.h`
- `variants/nrf52840/diy/liberty_meshmess_e22p/variant.cpp`

## Poznámky k Build Serveru
- Server: `10.5.0.146`
- Pro buildy se používá Docker a docker compose
- Disk/LVM/FS bylo nutné rozšířit, protože se root zaplnil během instalace ESP32 toolchainů
- První build nové platformy může být pomalý kvůli stahování PlatformIO balíků

## Příklad Úspěšného Buildu
Větev:
- `mqtt_custom`

Cíl:
- `heltec-v4`

Artefakty vznikly v:
- `/home/codex/meshtastic-builds/firmware-mqtt_custom_clean/release`

Soubory:
- `firmware-heltec-v4-2.7.22.7cbc1df.bin`
- `firmware-heltec-v4-2.7.22.7cbc1df.factory.bin`
- `firmware-heltec-v4-2.7.22.7cbc1df.mt.json`
- `littlefs-heltec-v4-2.7.22.7cbc1df.bin`
- `firmware-heltec-v4-2.7.22.7cbc1df.elf`

## Doporučený Checklist pro Navázání
1. Před pokračováním ověřit aktuální heady větví vůči GitHubu.
2. Pokud se bude pokračovat na `yomama_e22p`, zkontrolovat `variants/nrf52840/diy/yomama_e22p/platformio.ini`, hlavně `yomama_e22p_bare`.
3. Pokud se bude pokračovat na `mqtt_custom`, otevřít `src/mqtt/MQTT.cpp` a rozhodnout, jestli odstranit i per-channel `uplink_enabled`.
4. Pokud se bude pokračovat na `liberty_meshmess_e22p`, ověřit, že poslední změny z `develop` neovlivnily variantu neočekávaně.
5. Počítat s dlouhým prvním buildem, pokud PlatformIO teprve plní cache.

## Krátké Shrnutí pro Navázání
Pracujeme ve forku `norman67cz/firmware`. `yomama_e22p` je funkční větev pro nRF52840 + E22P s TCXO fixem, funkčním BLE, synchronizací času z telefonu, PKI direct messages, traceroute, INA podporou a vybranými teplotními/tlakovými senzory v bare buildu. `mqtt_custom` mění chování LoRa-to-MQTT forwardu. `liberty_meshmess_e22p` existuje jako samostatně udržovaná board větev.
