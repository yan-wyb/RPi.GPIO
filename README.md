## Based on:  
  
RPi.GPIO by Ben Croston  
  https://sourceforge.net/projects/raspberry-gpio-python/  

## License  
RPi.GPIO is distributed under MIT license, but wiringPi uses LGPL 3.  Since this project  
contains code from both projects, it is licensed under the slightly more restrictive LGPL v3.  
  
  
## Building  
1) Install build-essential, python, python-dev, python3, python3-dev, git  
2) use `git clone` to clone it .
3) cd RPi.GPIO-Khadas  
4) sudo python setup.py build install  
5) sudo python3 setup.py build install (add python3)
  
## Test app 
* `cp -r test/ ../` (Use in the installation directory will report an exception).
* How to use it : `cd test/` & `sudo python testVIMxxx.py(or python3 testVIMxx.py)`.
* It just a test program that pulls up or down GPIO every five seconds.
  
## Notes  
Apps require root (eg 'sudo python testapp.py')  
When using BCM mode, RPi BCM numbers are passed to GPIO.xxx and translated internally to Khadas GPIO numbers  
  
