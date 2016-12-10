SlowSoftI2CMaster
================

Another Software I2C library, very similar to SoftI2CMaster allowing you to use any Arduino pins for SDA and SCL.  The difference to the SoftI2CMaster library is that it is entirely written in C++, so you can use it also on ARM boards, such as Zero and Due. As is stipulated by the title, it is definitely slower.

In principle, you could setup different I2C buses (as masters), but I do not see the point in it. In particular since you only could do I/O on one bus at a time.

As in the case of the SoftI2CMaster library, there exists also a wrapper library that emulates the functionality of the Wire class. 
