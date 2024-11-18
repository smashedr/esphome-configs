# ESPHome Configs

ESPHome: https://esphome.io/

Useful Topics:

- Substitutions: https://esphome.io/components/substitutions
- Packages _(New)_: https://esphome.io/components/packages

## General

- [.common.yaml](.common.yaml) - Common configuration used by all devices.
- [include](include) - All sensors and entities used more than once.

## Substitutions

```yaml
substitutions:
  box_num: "01" # Box number prepended to box_name used for hostname and static IP address.
  box_name: "espbox" # Box name appended to box_num, used for hostname.
  type: "esp32" # Platform, for usage see .common.yaml: https://esphome.io/#supported-microcontrollers
  board: "esp32dev" # Board, for usage see .common.yaml: https://esphome.io/#supported-microcontrollers
  comment: "38-pin" # Just a comment to show in ESPHome.
  update_interval: "1min" # Used to define update_interval for many of the included sensors.
  force_update: "true" # Used to define force_update for many of the included sensors.
```
