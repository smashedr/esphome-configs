// #include <esp_log.h>
#include <esp_heap_caps.h>

#ifdef __cplusplus
  extern "C" {
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
  }
#endif
uint8_t temprature_sens_read();


class SystemStatsSensor : public PollingComponent {
 public:
  Sensor *core_temp_sensor = new Sensor();
  Sensor *heap_free_sensor = new Sensor();

  SystemStatsSensor() : PollingComponent(900 * 1000) {}

  float get_setup_priority() const override { return esphome::setup_priority::LATE; }

  void setup() override {
  }

  void update() override {
    float core_temp = temprature_sens_read();
    core_temp_sensor->publish_state((core_temp - 32) / 1.8);

    // float heap_free = esp_get_free_heap_size();
    // heap_free_sensor->publish_state(heap_free / 1000);

    uint32_t freeHeapBytes = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    uint32_t totalHeapBytes = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
    float percentageHeapFree = freeHeapBytes * 100.0f / (float)totalHeapBytes;
    heap_free_sensor->publish_state(percentageHeapFree);
  }
};
