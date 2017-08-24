
System Requirements:

1.) An embedded electronic device with the following peripherals:
      a.) 1 spring-loaded button that may be pushed and held by a user.
      b.) 1 Ethernet interface. Assume that the driver is functional, and the device has a valid IP address and is Internet-accessible. BSD sockets are available to use in the application.
      c.) 1 white LED, controllable by GPIO.
      d.) 1 red LED, controllable by GPIO.
      e.) 1 Battery monitor, read via ADC. Units read are in units of millivolts.
      f.) 1 USB battery charger interface, which may be plugged and unplugged at any time to charge or discharge the battery. Assume that all battery charging functionality is independent and properly working.

2.) When a user pushes the button, the white LED shall illuminate. The white LED shall be illuminated for as long as the button is held down. When the button is released, the white LED shall turn off.

3.) Network Application
      a.) While the button is pushed, a UDP socket shall be opened with a server at the domain "test.ring.com" on port 13469. Every 1 second, the device shall send a packet of 2 bytes to the server with a counter, starting at value 0 and increasing by 1 every packet.
      b.) For every 2-byte UDP packet sent to the server, the server shall return back a 2-byte packet on the same port echoing the counter. If no echo is received within 500ms or the value returned from the server is not equal to the value sent from the device, the device shall re-send the current value. This shall continue until the correct value is received from the server, at which point the device will increment the counter and proceed as normal.
      c.) When the button is released, the socket shall be closed and the counter shall be reset.

4.) Battery Operation
      a.) While the battery voltage is <3.5V, the system shall be put in a non-functional state, meaning the white LED shall not illuminate and the Network Application shall not be executed, even if the button is pushed.
      b.) While the battery voltage is <3.5V, the red LED shall blink at a rate of 2Hz with a 25% duty cycle.
      c.) If the battery voltage returns to an operable level (>= 3.5V), the red LED shall stop blinking and operation shall resume as normal.