# ESP-LightStrip  

This is a simple ESP8266-01 based PCB to allow the control of WS2812 light strips over WiFi/Bluetooth. 
 
This is for use at your own risk, I am not an electrical engineer by any means. I would appreciate any input on improvements both for features and safety.  
  
| Part        | Quantity           | Description  | Link   
| ------------- |-------------:| -----| ---
| 2N3906-APCT-ND | 1 | 2N3906 Transistor | [Link](https://www.digikey.com/product-detail/en/micro-commercial-co/2N3906-AP/2N3906-APCT-ND/950592) |  
| CP-037A-ND | 1 | DC Barrel Jack | [Link](https://www.digikey.com/product-detail/en/cui-inc/PJ-037A/CP-037A-ND/1644545) 
| ED10562-ND | 1 | Pin Header |  [Link](https://www.digikey.com/product-detail/en/on-shore-technology-inc/OSTVN03A150/ED10562-ND/1588863)
| 1568-1235-ND | 1 | ESP8266-01S | [Link](https://www.digikey.com/product-detail/en/sparkfun-electronics/WRL-13678/1568-1235-ND/5725944)
| RNCP0805FTD1K00CT-ND | 1 | 1kOhm Resistor 0805 | [Link](https://www.digikey.com/product-detail/en/stackpole-electronics-inc/RNCP0805FTD1K00/RNCP0805FTD1K00CT-ND/2240568)
| P3.3KDACT-ND | 1 | 3.3kOhm Resistor 0805 | [Link](https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERA-6AEB332V/P3.3KDACT-ND/1465959)
| 587-5399-1-ND | 1 | 47uF Capacitor 0805 | [Link](https://www.digikey.com/product-detail/en/taiyo-yuden/AMK212BBJ476MD-T/587-5399-1-ND/7067075)

Rev1 was tested with WS2812 strips @ ~200 LEDs. Highly recommend [ElegantOTA](https://github.com/ayushsharma82/ElegantOTA) for flashing, as it allows you flash once in a programming board, then solder into one of the PCBs permanently. I currently run a basic web server that responds to web requests from [Homebridge-better-http-rgb](https://www.npmjs.com/package/homebridge-better-http-rgb) for unofficial Apple HomeKit integration. 

Rev3 is uploaded here. I am currently waiting on the PCBs, so please note that the design has not yet been tested. 
