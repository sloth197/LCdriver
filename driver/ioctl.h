#ifndef VSENSOR_IOCTL_H
#define VSENSOR_IOCTL_H

#include <linux/ioctl.h>

#define VSENSOR_IOCTL_MAGIC 'v'

#define VSENSOR_ON  _IO(VSENSOR_IOCTL_MAGIC, 0)
#define VSENSOR_OFF _IO(VSENSOR_IOCTL_MAGIC, 1)

#endif