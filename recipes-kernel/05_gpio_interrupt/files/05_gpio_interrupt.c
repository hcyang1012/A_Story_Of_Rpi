#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/interrupt.h>


#define MODULE_NAME "MY_04_GPIO_IN"

static int sample_open(struct inode *inode, struct file *file){
    pr_info("sample_open\n");
    return 0;
}

static int sample_close(struct inode *inodep, struct file *filep){
    pr_info("sample_close\n");
    return 0;
}

static ssize_t sample_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos){
    pr_info("sample_write\n");
    return len;
}

static const struct file_operations sample_fops = {
    .owner = THIS_MODULE,
    .write = sample_write,
    .open = sample_open,
    .release = sample_close,
    .llseek = no_llseek,
};


struct miscdevice sample_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = MODULE_NAME,
    .fops = &sample_fops,
};


#if defined (CONFIG_OF)
    static const struct of_device_id my_device_of_match[] = {
        { .compatible = "raspberrypi,my_device_gpio_in"},
        {},
    };
    MODULE_DEVICE_TABLE(of, my_device_of_match);
#endif


int call_count = 0;
static irqreturn_t my_interrupt(int irq, void *data){
	struct device *dev = data;
	call_count++;
	printk("In the ISR : %d\n",call_count); 
	return IRQ_HANDLED;
}

struct gpio_desc *led_gpiod;
struct gpio_desc *input_gpiod;
struct gpio_desc *intr_gpiod;
static int my_device_probe(struct platform_device *pdev){
	struct device *dev = &pdev->dev;
	int input_val;
	int irq;
	int ret;


	printk("Start probing : %s\n",MODULE_NAME);
	led_gpiod = devm_gpiod_get(dev, "leds", GPIOD_ASIS);
	if(IS_ERR(led_gpiod)){
		pr_err("Can't get led_gpiod (%d)\n", PTR_ERR(led_gpiod));
		return -1;
	}
	printk("Found leds-gpio\n");


	input_gpiod = devm_gpiod_get(dev, "input", GPIOD_IN);
	if(IS_ERR(input_gpiod)){
		pr_err("Can't get input_gpiod (%d)\n", PTR_ERR(input_gpiod));
		return -1;
	}
	printk("Found input-gpio\n");

	input_val = gpiod_get_value(input_gpiod);
	printk("Input value : %d\n",input_val);
	gpiod_set_value(led_gpiod,input_val);

	intr_gpiod = devm_gpiod_get_optional(dev,"intr",GPIOD_IN);
	if(IS_ERR(intr_gpiod)){
		pr_err("Can't get intr_gpiod (%d)\n", PTR_ERR(intr_gpiod));
		return -1;
	}
	printk("Found intr-gpio\n");

	irq = platform_get_irq(pdev,0);
	if(irq < 0){
		pr_err("Can't get irq %d \n",irq);
		return -1;
	}
	if(IS_ERR(led_gpiod)){
		pr_err("Can't get led_gpiod (%d)\n", PTR_ERR(led_gpiod));
		return -1;
	}
	printk("Found leds-gpio\n");
	printk("Get irq %d\n",irq);

	ret = devm_request_irq(dev,irq,my_interrupt,IRQF_TRIGGER_RISING,"my_interrupt",dev);
	if(ret_val){
		pr_err("Failed to reserve irq %d(errno : %d)\n",irq,ret);
		return -1;
	}
	printk("Reserve irq\n");
	
	

	return 0;
}

static int my_device_remove(struct platform_device *pdev){
    pr_info("remove success\n");
    return 0;
}

static struct platform_driver my_device_driver = {
    .probe = my_device_probe,
    .remove = my_device_remove,
    .driver = {
            .name = MODULE_NAME, 
            .of_match_table = of_match_ptr(my_device_of_match),
    },
};


static int __init misc_init(void){
    int error;

    error = misc_register(&sample_device);
    if(error){
        pr_err("can't misc_register \n");
        return error;
    }

    error = platform_driver_register(&my_device_driver);
    if(error){
        pr_err("Can't register platform driver\n");
        return error;
    }


    pr_info("misc init success\n");
    return 0;

}


static void __exit misc_exit(void){
    platform_driver_unregister(&my_device_driver);
    misc_deregister(&sample_device);
    pr_info("misc exit success\n");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_DESCRIPTION("Simple Misc Driver");
MODULE_AUTHOR("Heecheol, Yang (heecheol.yang@outlook.com)");
MODULE_LICENSE("GPL");
