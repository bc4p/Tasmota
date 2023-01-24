/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

/*
Examples :

// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4617                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID1
#define STA_SSID1         "YourSSID"             // [Ssid1] Wifi SSID

#undef  STA_PASS1
#define STA_PASS1         "YourWifiPassword"     // [Password1] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST         "your-mqtt-server.com" // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER         "YourMqttUser"         // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS         "YourMqttPass"         // [MqttPassword] Optional password

// You might even pass some parameters from the command line ----------------------------
// Ie:  export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE -DMY_IP="192.168.1.99" -DMY_GW="192.168.1.1" -DMY_DNS="192.168.1.1"'

#ifdef MY_IP
#undef  WIFI_IP_ADDRESS
#define WIFI_IP_ADDRESS     MY_IP                // Set to 0.0.0.0 for using DHCP or enter a static IP address
#endif

#ifdef MY_GW
#undef  WIFI_GATEWAY
#define WIFI_GATEWAY        MY_GW                // if not using DHCP set Gateway IP address
#endif

#ifdef MY_DNS
#undef  WIFI_DNS
#define WIFI_DNS            MY_DNS               // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

#ifdef MY_DNS2
#undef  WIFI_DNS2
#define WIFI_DNS2           MY_DNS2              // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

// !!! Remember that your changes GOES AT THE BOTTOM OF THIS FILE right before the last #endif !!!
*/




// -- MQTT - Domoticz -----------------------------
#undef USE_DOMOTICZ                             // Enable Domoticz (+6k code, +0.3k mem)
  #undef DOMOTICZ_IN_TOPIC    "domoticz/in"     // Domoticz Input Topic
  #undef DOMOTICZ_OUT_TOPIC   "domoticz/out"    // Domoticz Output Topic

// -- MQTT - Tasmota Discovery ---------------------
#undef USE_TASMOTA_DISCOVERY                      // Enable Tasmota Discovery support (+2k code)

// -- Telegram Protocol ---------------------------
//#define USE_TELEGRAM                             // Support for Telegram protocol (+49k code, +7.0k mem and +4.8k additional during connection handshake)
  #undef USE_TELEGRAM_FINGERPRINT "\xB2\x72\x47\xA6\x69\x8C\x3C\x69\xF9\x58\x6C\xF3\x60\x02\xFB\x83\xFA\x8B\x1F\x23" // Telegram api.telegram.org TLS public key fingerpring

// -- KNX IP Protocol -----------------------------
//#define USE_KNX                                  // Enable KNX IP Protocol Support (+9.4k code, +3k7 mem)
  #undef USE_KNX_WEB_MENU                       // Enable KNX WEB MENU (+8.3k code, +144 mem)

// -- Time ----------------------------------------
#undef USE_TIMERS                               // Add support for up to 16 timers (+2k2 code)
  #undef USE_TIMERS_WEB                         // Add timer webpage support (+4k5 code)
  #undef USE_SUNRISE                            // Add support for Sunrise and sunset tools (+16k)
    #undef SUNRISE_DAWN_ANGLE DAWN_NORMAL       // Select desired Dawn Angle from (DAWN_NORMAL, DAWN_CIVIL, DAWN_NAUTIC, DAWN_ASTRONOMIC)

    // -- Compression ---------------------------------
#undef USE_UNISHOX_COMPRESSION                  // Add support for string compression in Rules or Scripts

// -- Rules or Script  ----------------------------
// Select none or only one of the below defines USE_RULES or USE_SCRIPT
#undef USE_RULES                                // Add support for rules (+8k code)
//  #define USE_EXPRESSION                         // Add support for expression evaluation in rules (+3k2 code, +64 bytes mem)
//    #define SUPPORT_IF_STATEMENT                 // Add support for IF statement in rules (+4k2 code, -332 bytes mem)
//  #define USER_RULE1 "<Any rule1 data>"          // Add rule1 data saved at initial firmware load or when command reset is executed
//  #define USER_RULE2 "<Any rule2 data>"          // Add rule2 data saved at initial firmware load or when command reset is executed
//  #define USER_RULE3 "<Any rule3 data>"          // Add rule3 data saved at initial firmware load or when command reset is executed

//#define USE_SCRIPT                               // Add support for script (+17k code)
//  #define USE_SCRIPT_FATFS 4                     // Script: Add FAT FileSystem Support
//  #define SUPPORT_MQTT_EVENT                     // Support trigger event with MQTT subscriptions (+3k5 code)

//#define USER_BACKLOG "<Any command separated by a semicolon (;)>"  // Add commands executed at firmware load or when command reset is executed

// -- Optional modules ----------------------------
#undef ROTARY_V1                                // Add support for Rotary Encoder as used in MI Desk Lamp (+0k8 code)
  #undef ROTARY_MAX_STEPS     10                // Rotary step boundary
#undef USE_SONOFF_RF                            // Add support for Sonoff Rf Bridge (+3k2 code)
  #undef USE_RF_FLASH                           // Add support for flashing the EFM8BB1 chip on the Sonoff RF Bridge. C2CK must be connected to GPIO4, C2D to GPIO5 on the PCB (+2k7 code)
#undef USE_SONOFF_SC                            // Add support for Sonoff Sc (+1k1 code)
#undef USE_TUYA_MCU                             // Add support for Tuya Serial MCU
  #undef TUYA_DIMMER_ID       0                 // Default dimmer Id
  #undef USE_TUYA_TIME                          // Add support for Set Time in Tuya MCU
#undef USE_ARMTRONIX_DIMMERS                    // Add support for Armtronix Dimmers (+1k4 code)
#undef USE_PS_16_DZ                             // Add support for PS-16-DZ Dimmer (+2k code)
#undef USE_SONOFF_IFAN                          // Add support for Sonoff iFan02 and iFan03 (+2k code)
#undef USE_BUZZER                               // Add support for a buzzer (+0k6 code)
#undef USE_ARILUX_RF                            // Add support for Arilux RF remote controller (+0k8 code, 252 iram (non 2.3.0))
#undef USE_SHUTTER                              // Add Shutter support for up to 4 shutter with different motortypes (+11k code)
#undef USE_DEEPSLEEP                            // Add support for deepsleep (+1k code)
#undef USE_EXS_DIMMER                           // Add support for ES-Store Wi-Fi Dimmer (+1k5 code)
//  #define EXS_MCU_CMNDS                          // Add command to send MCU commands (+0k8 code)
//#define USE_HOTPLUG                              // Add support for sensor HotPlug
#undef USE_DEVICE_GROUPS                        // Add support for device groups (+5k5 code)
  #undef DEVICE_GROUPS_ADDRESS 239,255,250,250  // Device groups multicast address
  #undef DEVICE_GROUPS_PORT 4447                // Device groups multicast port
  #undef USE_DEVICE_GROUPS_SEND                 // Add support for the DevGroupSend command (+0k6 code)
#undef USE_PWM_DIMMER                           // Add support for MJ-SD01/acenx/NTONPOWER PWM dimmers (+2k3 code, DGR=0k7)
  #undef USE_PWM_DIMMER_REMOTE                  // Add support for remote switches to PWM Dimmer (requires USE_DEVICE_GROUPS) (+0k6 code)
//#define USE_KEELOQ                               // Add support for Jarolift rollers by Keeloq algorithm (+4k5 code)
#undef USE_SONOFF_D1                            // Add support for Sonoff D1 Dimmer (+0k7 code)
#undef USE_SHELLY_DIMMER                        // Add support for Shelly Dimmer (+3k code)
  #undef SHELLY_CMDS                            // Add command to send co-processor commands (+0k3 code)
  #undef SHELLY_FW_UPGRADE                      // Add firmware upgrade option for co-processor (+3k4 code)
//  #define SHELLY_VOLTAGE_MON                     // Add support for reading voltage and current measurment (-0k0 code)

// -- Optional light modules ----------------------
//#define USE_LIGHT                                // Add support for light control
#undef USE_WS2812                               // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram) - Disable by //
//  #define USE_WS2812_DMA                         // ESP8266 only, DMA supports only GPIO03 (= Serial RXD) (+1k mem). When USE_WS2812_DMA is enabled expect Exceptions on Pow
  #undef USE_WS2812_RMT  0                      // ESP32 only, hardware RMT support (default). Specify the RMT channel 0..7. This should be preferred to software bit bang.
//  #define USE_WS2812_I2S  0                      // ESP32 only, hardware I2S support. Specify the I2S channel 0..2. This is exclusive from RMT. By default, prefer RMT support
//  #define USE_WS2812_INVERTED                    // Use inverted data signal
  #undef USE_WS2812_HARDWARE  NEO_HW_WS2812     // Hardware type (NEO_HW_WS2812, NEO_HW_WS2812X, NEO_HW_WS2813, NEO_HW_SK6812, NEO_HW_LC8812, NEO_HW_APA106, NEO_HW_P9813)
  #undef USE_WS2812_CTYPE     NEO_GRB           // Color type (NEO_RGB, NEO_GRB, NEO_BRG, NEO_RBG, NEO_RGBW, NEO_GRBW)
#undef USE_MY92X1                               // Add support for MY92X1 RGBCW led controller as used in Sonoff B1, Ailight and Lohas
#undef USE_SM16716                              // Add support for SM16716 RGB LED controller (+0k7 code)
#undef USE_SM2135                               // Add support for SM2135 RGBCW led control as used in Action LSC (+0k6 code)
#undef USE_SM2335                               // Add support for SM2335 RGBCW led control as used in SwitchBot Color Bulb (+0k7 code)
#undef USE_BP5758D                              // Add support for BP5758D RGBCW led control as used in some Tuya lightbulbs (+0k8 code)
#undef USE_SONOFF_L1                            // Add support for Sonoff L1 led control
#undef USE_ELECTRIQ_MOODL                       // Add support for ElectriQ iQ-wifiMOODL RGBW LED controller (+0k3 code)
#undef USE_LIGHT_PALETTE                        // Add support for color palette (+0k7 code)
#undef USE_LIGHT_VIRTUAL_CT                     // Add support for Virtual White Color Temperature (+1.1k code)
#undef USE_DGR_LIGHT_SEQUENCE                   // Add support for device group light sequencing (requires USE_DEVICE_GROUPS) (+0k2 code)
//#define USE_LSC_MCSL                             // Add support for GPE Multi color smart light as sold by Action in the Netherlands (+1k1 code)

// -- Counter input -------------------------------
#undef USE_COUNTER                              // Enable inputs as counter (+0k8 code)

// -- One wire sensors ----------------------------
#undef USE_DS18x20                              // Add support for DS18x20 sensors with id sort, single scan and read retry (+2k6 code)
//  #define W1_PARASITE_POWER                      // Optimize for parasite powered sensors
//  #define DS18x20_USE_ID_ALIAS                   // Add support aliasing for DS18x20 sensors. See comments in xsns_05 files (+0k5 code)

// -- I2C sensors ---------------------------------
#undef USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)
#undef I2CDRIVERS_0_31        0xFFFFFFFF          // Enable I2CDriver0  to I2CDriver31
#undef I2CDRIVERS_32_63       0xFFFFFFFF          // Enable I2CDriver32 to I2CDriver63
#undef I2CDRIVERS_64_95       0xFFFFFFFF          // Enable I2CDriver64 to I2CDriver95

    #undef USE_VEML6070_RSET    270000          // VEML6070, Rset in Ohm used on PCB board, default 270K = 270000ohm, range for this sensor: 220K ... 1Meg
    #undef USE_VEML6070_SHOW_RAW                // VEML6070, shows the raw value of UV-A
    #undef MGS_SENSOR_ADDR    0x04              // Default Mutichannel Gas sensor i2c address
    #undef USE_APDS9960_GESTURE                   // Enable APDS9960 Gesture feature (+2k code)
    #undef USE_APDS9960_PROXIMITY                 // Enable APDS9960 Proximity feature (>50 code)
    #undef USE_APDS9960_COLOR                     // Enable APDS9960 Color feature (+0.8k code)
    #undef USE_APDS9960_STARTMODE  0              // Default to enable Gesture mode
    #undef USE_ADE7953                            // [I2cDriver7] Enable ADE7953 Energy monitor as used on Shelly 2.5 (I2C address 0x38) (+1k5)
    #undef USE_DISPLAY_MODES1TO5                // Enable display mode 1 to 5 in addition to mode 0
    #undef USE_DISPLAY_LCD                      // [DisplayModel 1] [I2cDriver3] Enable Lcd display (I2C addresses 0x27 and 0x3F) (+6k code)
    #undef USE_DISPLAY_SSD1306                  // [DisplayModel 2] [I2cDriver4] Enable SSD1306 Oled 128x64 display (I2C addresses 0x3C and 0x3D) (+16k code)
    #undef USE_DISPLAY_MATRIX                   // [DisplayModel 3] [I2cDriver5] Enable 8x8 Matrix display (I2C adresseses see below) (+11k code)
      #undef MTX_ADDRESS1     0x71              // [DisplayAddress1] I2C address of first 8x8 matrix module
      #undef MTX_ADDRESS2     0x74              // [DisplayAddress2] I2C address of second 8x8 matrix module
      #undef MTX_ADDRESS3     0x75              // [DisplayAddress3] I2C address of third 8x8 matrix module
      #undef MTX_ADDRESS4     0x72              // [DisplayAddress4] I2C address of fourth 8x8 matrix module
      #undef MTX_ADDRESS5     0x73              // [DisplayAddress5] I2C address of fifth 8x8 matrix module
      #undef MTX_ADDRESS6     0x76              // [DisplayAddress6] I2C address of sixth 8x8 matrix module
      #undef MTX_ADDRESS7     0x00              // [DisplayAddress7] I2C address of seventh 8x8 matrix module
      #undef MTX_ADDRESS8     0x00              // [DisplayAddress8] I2C address of eigth 8x8 matrix module
    #undef USE_DISPLAY_SEVENSEG                 // [DisplayModel 11] [I2cDriver47] Enable sevenseg display (I2C 0x70-0x77) (<+11k code)

// -- Low level interface devices -----------------
#undef USE_DHT                                  // Add support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor (1k6 code)

// -- IR Remote features - subset of IR protocols --------------------------
#undef USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 (+4k3 code, 0k3 mem, 48 iram)
  #undef IR_SEND_INVERTED          false        // Invert the output. (default = false) e.g. LED is illuminated when GPIO is LOW rather than HIGH.
                                                 // Setting inverted to something other than the default could easily destroy your IR LED if you are overdriving it.
                                                 // Unless you REALLY know what you are doing, don't change this.
  #undef IR_SEND_USE_MODULATION    true         // Do we do frequency modulation during transmission? i.e. If not, assume a 100% duty cycle.

  #undef USE_IR_SEND_NEC                        // Support IRsend NEC protocol
  #undef USE_IR_SEND_RC5                        // Support IRsend Philips RC5 protocol
  #undef USE_IR_SEND_RC6                        // Support IRsend Philips RC6 protocol

  // Enable IR devoder via GPIO `IR Recv` - always enabled if `USE_IR_REMOTE_FULL`
  #undef USE_IR_RECEIVE                         // Support for IR receiver (+7k2 code, 264 iram)
    #undef IR_RCV_BUFFER_SIZE      100          // Max number of packets allowed in capture buffer (default 100 (*2 bytes ram))
    #undef IR_RCV_TIMEOUT          15           // Number of milli-Seconds of no-more-data before we consider a message ended (default 15)
    #undef IR_RCV_MIN_UNKNOWN_SIZE 6            // Set the smallest sized "UNKNOWN" message packets we actually care about (default 6, max 255)
    #undef IR_RCV_WHILE_SENDING    0            // Turns on receiver while sending messages, i.e. receive your own. This is unreliable and can cause IR timing issues
    #undef IR_RCV_TOLERANCE        25           // Base tolerance percentage for matching incoming IR messages (default 25, max 100)

    

#endif  // _USER_CONFIG_OVERRIDE_H_
