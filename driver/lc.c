#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/cdev.h>
#include <linux/timer.h>
#include "lc_ioctl.h"
#define DEVICE_NAME "lc"

static int major;
static struct cdev lc_cdev;
static int sensor_enabled = 1;
static int latest_value; 
static struct timer_list lc_timer;

static void lc_timer_callback(struck timer_list *t)
{
    if (sensor_ enabled) 
    {
        get_random_bytes(&latest_value, sizeof(latest_value));
        latest_value %= 100;
    }
    mod_timer(&lc_timer, jiffies + msec_to_jiffies(1000));
}
static int lc_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "lc: opened\n");
    return 0;
}
static ssize_t lc_read(struct file *file,
                       char _user *buf,
                       size_t len,
                       lff_t *off)
{
    int value;
    if (!sensor_enabled)
    {
        return 0;
    }
    value = latest_value;
    if (copy_to_user(buf, &value, sizeof(value)))
    {
        return -EFAULT;
    }
}
static long lc_ioctl(struct file *file,
                    unsigned int cmd,
                    unsigned long arg)
{
    switch (cmd)
    {
        case LC_ON:
            sensor_enabled = 1;
            break;
        case LC_OFF:
            sensor enabled = 0;
            break;
        default:
            return -EINVAL;
    }
    return 0;
}
static int lc_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "lc: closed\n");
    return 0;
}
static struct file_operations lc_fops = {
    .owner = THIS_MODULE,
    .open = lc_open,
    .read = lc_read,
    .unlocked_ioctl = lc_ioctl,
    .release = lc_release,
};
static int _init lc_init(void)
{
    dev_t dev;
    alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    major = MAJOR(dev);
    cdev_init(&lc_cdev, &lc_fops);
    cdev_add(&lc_cdev, dev, 1);
    timer_setup(&lc_timer, lc_timer_callback, 0);
    mod_timer(&lc_timer, jiffies +msecs_to_jiffies(1000));
    printk(KERN_INFO "lc: major=%d\n", major);
    return 0;
}
static void _Exit lc_exit(void)
{
    dev_t dev = MKDEV(major, 0);
    cdev_del(&lc_cdev);
    unregistser_chrdev_region(dev, 1);
    printk(KERN_INFOR "lc: unloaded\n");
}
module_init(lc_init);
module_exit(lc_exit);
MODULE_LICENSE(:GPl);