# mouse hack for minecraft
* The kids playing minecraft "bridge" games are addicted to some mouse could do lots clicks.
* It could be done by using software.
  * but the kids believed this is abuse! 
* then we can do it in hardware way. 
  * I prefer `circuit python` boards but didn't find any usb host interface.
  * ~~keyestudio: uno + usb host shield 1.5~~
    * usb host shield works great, signal parsed correctly.
    * But UNO cannot act as `HID`.
  * Bought another keyestudio `Leonardo`.
  ```
    The Leonardo differs from other boards using separate USB-Serial chip in that the ATmega32u4 has built-in USB communication, eliminating the need for a secondary processor. 
  ```  
    * USB host shields must have ICSP. Because Leonardo use ICSP for SPI interface.
  * maybe `teensy 4.0` + `usb hub extension` works. will try next version.


Below are from [mustaffxx](https://github.com/mustaffxx/usb-host-shield-mouse).

# usb-host-shield-mouse

When playing around a [USB HOST SHIELD 2.0](https://github.com/felis/USB_Host_Shield_2.0) with my Logitech G502 i've notice that examples not working with my mouse. The problem is that examples use HID Boot Protocol and G502 uses HID Report Protocol. 

# Hardware
Arduino Leonardo;  
USB Host Shield 2.0;  
Logitech G502;  
Computer;  

## What does it do?

Interpret ~~16-bit~~(actually 8-bits) data from x and y axis, mouse clicks, mouse wheel and replicate to computer.

```
[USB Mouse] --> [USB Host Shield 2.0] --> [Arduino Leonardo] --FAKE HID USB--> [Computer]
```

## To Do

- Parse 16-bit precision.

## Credits
* [mustaffxx](https://github.com/mustaffxx/usb-host-shield-mouse).
* [Yukawa](https://titanwolf.org/Network/Articles/Article?AID=ee7d3b48-cb5b-49eb-83c4-e6ff634cd7d1#gsc.tab=0) - base
