[![GitHub Last Commit](https://img.shields.io/github/last-commit/smashedr/esphome-configs?logo=github&logoColor=white&label=updated)](https://github.com/smashedr/esphome-configs/graphs/commit-activity)
[![GitHub Org Stars](https://img.shields.io/github/stars/cssnr?style=flat&logo=github&logoColor=white)](https://cssnr.github.io/)
[![Discord](https://img.shields.io/discord/899171661457293343?logo=discord&logoColor=white&label=discord&color=7289da)](https://discord.gg/wXy6m2X8wY)

# ESPHome Configs

- [Packages](#packages) <-- this is a **MUST SEE!**
- [Substitutions](#substitutions)
- [Voice Assistant](#voice-assistant)
- [Micro Wake Word](#micro-wake-word)

ESPHome: https://esphome.io/

## Substitutions

- https://esphome.io/components/substitutions

This is now a WIP with Packages coming soon, but seems stable...

To see how these substitutions are used, see: [include/common.yaml](include/common.yaml)

```yaml
substitutions:
  # required
  box_num: "01" # Box number appended to box_name used for hostname and IP address.
  box_name: "espbox" # Box name prepended to box_num used for hostname.
  type: "esp32" # Platform, see: https://esphome.io/#supported-microcontrollers
  board: "esp32dev" # Board, see: https://esphome.io/#supported-microcontrollers
  comment: "38-pin" # Just a comment to show in ESPHome.
  # provided by package: common
  update_interval: "1min" # Used to define update_interval for many of the included sensors.
  force_update: "true" # Used to define force_update for many of the included sensors.
```

## Packages

- https://esphome.io/components/packages.html

This is a **WIP** but **very powerful!**

Click on the package name for info on using the package and the file name for full details.

| Package                             | File                                                               | URL |
| ----------------------------------- | ------------------------------------------------------------------ | --- |
| [common](#common)                   | [include/common.yaml](include/common.yaml)                         | WIP |
| [debug](#debug)                     | [include/debug.yaml](include/debug.yaml)                           | WIP |
| [status_led](#status_led)           | [include/status_led.yaml](include/status_led.yaml)                 | WIP |
| [voice_assistant](#voice_assistant) | [include/va/voice_assistant.yaml](include/va/voice_assistant.yaml) | WIP |
| [micro_wake_word](#micro_wake_word) | [include/va/micro_wake_word.yaml](include/va/micro_wake_word.yaml) | WIP |
| [pmsx003](#pmsx003)                 | [include/pmsx003/pmsx003.yaml](include/pmsx003/pmsx003.yaml)       | WIP |
| [apds9960](#apds9960)               | [include/apds9960/apds9960.yaml](include/apds9960/apds9960.yaml)   | WIP |
| [ld2420](#ld2420)                   | [include/ld2420/ld2420.yaml](include/ld2420/ld2420.yaml)           | WIP |
| [ld2450](#ld2450)                   | [include/ld2450/ld2450.yaml](include/ld2450/ld2450.yaml)           | WIP |

**Note:** All components included in a package can be `removed` or `extended` as desired...

### common

These are my common configurations shared with all boxes. You probably don't want to use these without modification.

### debug

- https://esphome.io/components/debug

Use this to easily enable the `debug` platform on ESPHome.

### status_led

- https://esphome.io/components/status_led

This combines the `status_led` platform with an `identify` button.

| Variable   | Default    | Description               |
| ---------- | ---------- | ------------------------- |
| pin        | -          | PIN for LED Binary Output |
| status_led | `main_led` | ID of the `status_led`    |

```yaml
packages:
  status_led: !include
    file: include/status_led.yaml
    vars:
      pin: GPIO18 # required
      status_led: name_for_id
```

### voice_assistant

- https://esphome.io/components/voice_assistant

| Variable        | Default    | Description                  |
| --------------- | ---------- | ---------------------------- |
| microphone      | `va_mic`   | ID of `microphone`           |
| script_va_start | `va_start` | ID of script to `start` va   |
| sorting_weight  | `-30`      | `sorting_weight` of VA group |

```yaml
voice_assistant: !include
  file: include/va/voice_assistant.yaml
  vars:
  models:
    - microphone: "va_mic"
    - script_va_start: "va_start"
    - sorting_weight: "-30"
```

This package provides the voice_assistant, a button to activate, and a web_server sorting_group.

This requires the script a `va_start` script provided by `micro_wake_word`. If only using va, add:

```yaml
script:
  - id: va_start
    mode: restart
    then:
      - logger.log: "Running script: va_start"
      - if:
          condition:
            - voice_assistant.is_running:
          then:
            - logger.log: "va_start: voice_assistant.stop"
            - voice_assistant.stop:
          else:
            - logger.log: "va_start: micro_wake_word.stop"
            - wait_until:
                condition:
                  not:
                    microphone.is_capturing:
                timeout: 1000ms
            - logger.log: "va_start: voice_assistant.start"
            - voice_assistant.start:
```

This will stop the VA if it is running, otherwise start the VA; making it a toggle.  
At minimum add: `- voice_assistant.start:`.

### micro_wake_word

- https://esphome.io/components/micro_wake_word

| Variable         | Default      | Description              |
| ---------------- | ------------ | ------------------------ |
| sorting_group_id | `sg_va`      | ID of VA `sorting_group` |
| model            | `hey_jarvis` | Name or URL of `model`   |

```yaml
micro_wake_word: !include
  file: include/va/micro_wake_word.yaml
  vars:
  models:
    - model: "hey_jarvis"
    - sorting_group_id: "sg_va"
```

This package provides the micro_wake_word, a switch to enable/disable it and save state, an on_boot to ensure state; plus scripts:

- micro_wake_enable
- va_start
- va_end

You will want to extend these, and use them in your workflow for those actions...

### pmsx003

- https://esphome.io/components/sensor/pmsx003

| Variable     | Default | Description                   |
| ------------ | ------- | ----------------------------- |
| pms_num      | 01      | Number Appended to `name`(s)  |
| rx_pin       | GPIO16  | PIN for `rx_pin`              |
| tx_pin       | GPIO17  | PIN for `tx_pin`              |
| force_update | true    | Set `force_update` for sensor |

```yaml
packages:
  pmsx003: !include
    file: include/pmsx003/pmsx003.yaml
    vars:
      pms_num: 01
      rx_pin: GPIO16
      tx_pin: GPIO17
      force_update: true
```

You may want to extend the sensor for `on_value` automations:

```yaml
sensor:
  - id: !extend pm_sensor
    pm_2_5:
      on_value_range:
```

### apds9960

- https://esphome.io/components/sensor/apds9960

| Variable       | Default | Description                                 |
| -------------- | ------- | ------------------------------------------- |
| box_num        | 01      | Number Appended to `name`(s)                |
| sorting_weight | 50      | web_server: sorting_group: `sorting_weight` |

```yaml
packages:
  apds9960: !include
    file: include/apds9960/apds9960.yaml
    vars:
      box_num: 01
      sorting_weight: 50
```

This package captures each gesture and publishes them to a text sensor with the last value, UP, DOWN, RIGHT, or LEFT.

You will probably want to extend the `last_gesture` sensor to add automation for the `on_value`:

```yaml
text_sensor:
  - platform: template
    id: !extend last_gesture
    on_value:
      then:
        - logger.log:
            format: "Direction: %s"
            args: ["x.c_str()"]
```

This also adds a `sorting_group` to the `web_server`. If you don't use `web_server` 3 this can be disabled:

```yaml
web_server: !disable
```

### ld2420

- https://esphome.io/components/sensor/ld2420

| Variable | Default | Description                  |
| -------- | ------- | ---------------------------- |
| box_num  | 01      | Number Appended to `name`(s) |
| rx_pin   | GPIO16  | PIN for `rx_pin`             |
| tx_pin   | GPIO17  | PIN for `tx_pin`             |

```yaml
packages:
  ld2420: !include
    file: include/ld2420/ld2420.yaml
    vars:
      rx_pin: GPIO16
      tx_pin: GPIO17
```

You may want to extend the presence sensor for `on_press` automations:

```yaml
binary_sensor:
  - id: !extend presence_sensor
    has_target:
      on_press:
        then:
          - logger.log: "Presence Detected"
      on_release:
        then:
          - logger.log: "No Presence"
```

Attempting to include this in the package then overriding it throws a duplicate ID error on `presence`.

_Note: If you palan to extend the `uart:` definition, the `ld2420:` definition must come before it!_

### ld2450

- https://github.com/uncle-yura/esphome-ld2450

| Variable | Default | Description                  |
| -------- | ------- | ---------------------------- |
| box_num  | 01      | Number Appended to `name`(s) |
| rx_pin   | GPIO16  | PIN for `rx_pin`             |
| tx_pin   | GPIO17  | PIN for `tx_pin`             |

```yaml
packages:
  ld2450: !include
    file: include/ld2450/ld2450.yaml
    vars:
      rx_pin: GPIO16
      tx_pin: GPIO17
```

The `presence` binary_sensor needs to be added manually and optionally moving/still:

```yaml
binary_sensor:
  - platform: ld2450
    has_target:
      name: "Presence ${box_num}"
      id: presence
      on_press:
        then:
          - logger.log: "Presence Detected"
      on_release:
        then:
          - logger.log: "No Presence"
    has_moving_target:
      name: "Moving Target ${box_num}"
    has_still_target:
      name: "Still Target ${box_num}"
```

_Note: This is because this is a custom component and does not allow assigning an ID to the platform._

## Voice Assistant

- https://esphome.io/components/voice_assistant

Packages coming soon...

This is a WIP but already looking very good!

Current Progress: [esptest51.yaml](esptest51.yaml)

## Micro Wake Word

- https://esphome.io/components/micro_wake_word
- https://github.com/kahrendt/microWakeWord

Packages coming soon... Micro Wake Word Models coming soon...

| Wake Word     | File                                  | URL for Model                                          |
| ------------- | ------------------------------------- | ------------------------------------------------------ |
| `Computer` \* | [computer.json](models/computer.json) | github://smashedr/esphome-configs/models/computer.json |

\* Not made by me. See manifest file for details...

Example Configuration:

```yaml
micro_wake_word:
  vad:
  models:
    - model: hey_jarvis
    - model: github://smashedr/esphome-configs/models/computer.json@master
  on_wake_word_detected:
    then:
      - voice_assistant.start:
```

Tip: Micro Wake Word will respond slightly faster with increased CPU frequency on ESP32:

```yaml
esp32:
  board: "${board}"
  framework:
    type: esp-idf
    version: recommended
    sdkconfig_options:
      CONFIG_ESP32_DEFAULT_CPU_FREQ_240: "y"
```

_Reference: https://esphome.io/components/esp32_  
_Reference: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/kconfig-reference.html_
