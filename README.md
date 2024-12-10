[![GitHub Last Commit](https://img.shields.io/github/last-commit/smashedr/esphome-configs?logo=github&logoColor=white&label=updated)](https://github.com/smashedr/esphome-configs/graphs/commit-activity)
[![GitHub Org Stars](https://img.shields.io/github/stars/cssnr?style=flat&logo=github&logoColor=white)](https://cssnr.github.io/)
[![Discord](https://img.shields.io/discord/899171661457293343?logo=discord&logoColor=white&label=discord&color=7289da)](https://discord.gg/wXy6m2X8wY)

# ESPHome Configs

- [Packages](#packages)
- [Substitutions](#substitutions)
- [Voice Assistant](#voice-assistant)
- [Micro Wake Word](#micro-wake-word)

ESPHome: https://esphome.io/

## Packages

- https://esphome.io/components/packages.html

This is a WIP but very powerful!

| Package    | File                                          | URL |
| ---------- | --------------------------------------------- | --- |
| Common     | [include/common.yaml](include/common.yaml)    | WIP |
| Debug      | [include/debug.yaml](include/debug.yaml)      | WIP |
| Status LED | [include/debug.yaml](include/status_led.yaml) | WIP |

## Substitutions

- https://esphome.io/components/substitutions

This is now a WIP with Packages coming soon...

To see how these substitutions are used, see: [.common.yaml](include/common.yaml)

```yaml
substitutions:
  # required
  box_num: "01" # Box number appended to box_name used for hostname and IP address.
  box_name: "espbox" # Box name prepended to box_num used for hostname.
  type: "esp32" # Platform, see: https://esphome.io/#supported-microcontrollers
  board: "esp32dev" # Board, see: https://esphome.io/#supported-microcontrollers
  comment: "38-pin" # Just a comment to show in ESPHome.
  # common package
  update_interval: "1min" # Used to define update_interval for many of the included sensors.
  force_update: "true" # Used to define force_update for many of the included sensors.
  # status_led package
  status_led: "main_led"
```

## Voice Assistant

- https://esphome.io/components/voice_assistant

Packages coming soon...

This is a WIP but already looking very good!

Current Progress: [esptest51.yaml](esptest51.yaml)

## Micro Wake Word

- https://github.com/kahrendt/microWakeWord
- https://esphome.io/components/micro_wake_word

Packages coming soon...

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
