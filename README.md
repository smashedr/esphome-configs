[![GitHub Last Commit](https://img.shields.io/github/last-commit/smashedr/esphome-configs?logo=github&logoColor=white&label=updated)](https://github.com/smashedr/esphome-configs/graphs/commit-activity)
[![GitHub Org Stars](https://img.shields.io/github/stars/cssnr?style=flat&logo=github&logoColor=white)](https://cssnr.github.io/)
[![Discord](https://img.shields.io/discord/899171661457293343?logo=discord&logoColor=white&label=discord&color=7289da)](https://discord.gg/wXy6m2X8wY)

# ESPHome Configs

ESPHome: https://esphome.io/

Useful Topics:

- Substitutions: https://esphome.io/components/substitutions
- Packages _(New)_: https://esphome.io/components/packages

## General

Configs:

- [.common.yaml](.common.yaml) - Common configuration used by all devices.
- [include](include) - All sensors and entities used more than once.

## Substitutions

To see how these substitutions are used, see: [.common.yaml](.common.yaml)

```yaml
substitutions:
  box_num: "01" # Box number appended to box_name used for hostname and IP address.
  box_name: "espbox" # Box name prepended to box_num used for hostname.
  type: "esp32" # Platform, see: https://esphome.io/#supported-microcontrollers
  board: "esp32dev" # Board, see: https://esphome.io/#supported-microcontrollers
  comment: "38-pin" # Just a comment to show in ESPHome.
  update_interval: "1min" # Used to define update_interval for many of the included sensors.
  force_update: "true" # Used to define force_update for many of the included sensors.
```

## microWakeWord Models

| Wake Word     | File                                  | URL for Model                                          |
| ------------- | ------------------------------------- | ------------------------------------------------------ |
| `Computer` \* | [computer.json](models/computer.json) | github://smashedr/esphome-configs/models/computer.json |

\* - Not made by me. See manifest file for details...

Reference: https://esphome.io/components/micro_wake_word
