SlowSoftI2CMaster
================

Another Software I2C library, very similar to SoftI2CMaster, allowing you to use any Arduino pins for SDA and SCL.  The difference to the SoftI2CMaster library is that it is entirely written in C++, so you can use it also on ARM boards, such as Zero and Due. And you can use any pin on the ATMega256. As is stipulated by the title, it is definitely slower. On an UNO it runs with roughly 40kHz, on an ARM board with around 70 kHz. 

In principle, you could setup different I2C buses (as masters), but I do not see the point in it. In particular since you only could do I/O on one bus at a time.

You can use the the library in a way such that the internal pullup resistors of the AVR are used. However, note that this implies that when switching between HIGH and LOW the bus will temporarily in a high-impedance state, which is outside the I2C specification. Furthermore, the internal pull-ups are around 50k and so might not deliver enough current. Be careful when using this option and consider it as a potential source of errors.

As in the case of the SoftI2CMaster library, there exists a [wrapper library](https://github.com/felias-fogg/SlowSoftWire) that emulates the functionality of the Wire class.

This software is published under the [LGPL](http://www.gnu.org/licenses/lgpl-3.0.html)
