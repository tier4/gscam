#ifndef __GSCAM_JETSON_GPIO_H
#define __GSCAM_JETSON_GPIO_H

#include <map>

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define BUFFER_SIZE 64

typedef int gpio_direction;
typedef int gpio_state;

enum gpio_directions {
	input  = 0,
	output = 1
};

enum gpio_states {
  low = 0,
  high = 1,
};

// Mapping of GPIO number to pin number
static std::map<int, int> pin_gpio_mapping {
  {51, 408},
  {52, 350},
  {53, 446},
  {54, 445}
};

int export_gpio(int gpio);
int unexport_gpio(int gpio);
int set_gpio_direction(int gpio, gpio_direction direction);
int set_gpio_state(int gpio, gpio_state state);

int export_gpio_pin(int gpio_pin);
int unexport_gpio_pin(int gpio_pin);
int set_gpio_pin_direction(int gpio_pin, gpio_direction direction);
int set_gpio_pin_state(int gpio_pin, gpio_state state);

#endif // GSCAM_JETSON_GPIO_H