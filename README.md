## AWS-IOT ESP8266 device

### Gettng Started

#### Register an IOT thing with AWS
https://aws.amazon.com/iot-core/

#### Create a `secrets.h` file
```c
#define BIN_CRT <binary certificate>
#define BIN_CRT_LEN <binary cert length>
#define BIN_KEY <binary private key>
#define BIN_KEY_LEN <binary key length>
#define AWS_ENDPOINT <"foobar.iot.region.amazonaws.com">
#define UPDATE_TOPIC <"$aws/things/yourThingName/shadow/update">
```

#### Upload the code with Arduino IDE
#### Power the device
#### Connect to the AP
- Look for the wifi with an SSID like `ESP-<some id>`
- Visit 192.168.4.1 in your browser
- Input wifi credentials that the device can connect to

#### See it update the device shadow
