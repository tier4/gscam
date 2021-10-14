#include <unistd.h>
#include <fcntl.h>
#include <gscam/jetson_gpio.h>

int export_gpio(int gpio)
{
  int file_descriptor, buffer_length;
  char buffer[BUFFER_SIZE];

  file_descriptor = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
  if (file_descriptor < 0) {
    return file_descriptor;
  }
  buffer_length = snprintf(buffer, sizeof(buffer), "%d", gpio);
  if (write(file_descriptor, buffer, buffer_length) != buffer_length) {
    return file_descriptor;
  }
  close(file_descriptor);
  return 0;
}

int unexport_gpio(int gpio)
{
  int file_descriptor, buffer_length;
  char buffer[BUFFER_SIZE];

  file_descriptor = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
  if (file_descriptor < 0) {
    return file_descriptor;
  }
  buffer_length = snprintf(buffer, sizeof(buffer), "%d", gpio);
  if (write(file_descriptor, buffer, buffer_length) != buffer_length) {
    return file_descriptor;
  }
  close(file_descriptor);
  return 0;
}

int set_gpio_direction(int gpio, gpio_direction direction)
{
  int file_descriptor;
  char buffer[BUFFER_SIZE];

  snprintf(buffer, sizeof(buffer), SYSFS_GPIO_DIR "/gpio%d/direction", gpio);

  file_descriptor = open(buffer, O_WRONLY);
  if (file_descriptor < 0) {
    return file_descriptor;
  }
  if (direction) {
    if (write(file_descriptor, "out", 4) != 4) {
      return file_descriptor;
    }
  }
  else {
    if (write(file_descriptor, "in", 3) != 3) {
      return file_descriptor;
    }
  }
  close(file_descriptor);
  return 0;
}

int set_gpio_state(int gpio, gpio_state state)
{
  int file_descriptor;
  char buffer[BUFFER_SIZE];

  snprintf(buffer, sizeof(buffer), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

  file_descriptor = open(buffer, O_WRONLY);
  if (file_descriptor < 0) {
    return file_descriptor;
  }
  if (state) {
    if (write(file_descriptor, "1", 2) != 2) {
      return file_descriptor;
    }
  }
  else {
    if (write(file_descriptor, "0", 2) != 2) {
      return file_descriptor;
    }
  }
  close(file_descriptor);
  return 0;  
}

int export_gpio_pin(int gpio_pin)
{
  return export_gpio(pin_gpio_mapping[gpio_pin]);
}

int unexport_gpio_pin(int gpio_pin)
{
  return unexport_gpio(pin_gpio_mapping[gpio_pin]);
}

int set_gpio_pin_direction(int gpio_pin, gpio_direction direction)
{
  return set_gpio_direction(pin_gpio_mapping[gpio_pin], direction);
}

int set_gpio_pin_state(int gpio_pin, gpio_state state)
{
  return set_gpio_state(pin_gpio_mapping[gpio_pin], state);
}
