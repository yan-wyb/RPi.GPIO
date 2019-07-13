## Based on:  
  
RPi.GPIO by Ben Croston  
  https://sourceforge.net/projects/raspberry-gpio-python/  

## License  
RPi.GPIO is distributed under MIT license, but wiringPi uses LGPL 3.  Since this project  
contains code from both projects, it is licensed under the slightly more restrictive LGPL v3.  
  
  
## Building  
1) Install build-essential, python, python-dev, git  
2) use `git clone` to clone it .
3) cd RPi.GPIO-Khadas  
4) sudo python setup.py build install  
  
## Test app is `test`
* `cp -r test/ ../` (Use in the installation directory will report an exception).
* How to use it : `cd test/` & `sudo python testVIMxxx.py`.
* It kills a test program that pulls up or down GPIO every five seconds.
  
## Notes  
Apps require root (eg 'sudo python testapp.py')  
When using BCM mode, RPi BCM numbers are passed to GPIO.xxx and translated internally to Odroid GPIO numbers  
  
