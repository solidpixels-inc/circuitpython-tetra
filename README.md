# Build custom Circuitpython

To make a new build, create a <span style="color:red">.env</span> file and place the name of the board, you can see the list of supported boards [here](https://github.com/adafruit/circuitpython/tree/8.2.9/ports/espressif/boards).

For example:

```
#.env file content
BOARD=yd_esp32_s3_n16r8
```

Then go to your terminal and run

```
docker-compose up --build
```

The result will be posted in the local folder named `build` in 2 formats, firmware.bin, firmware.uf2

## How to flash the device

1. Configure [esptool.py](https://docs.espressif.com/projects/esptool/en/latest/esp32/installation.html) in your computer
2. Set the device into bootloader mode if necessary
3. Erase flash and upload firmware (replace /dev/tty.wchusbserial56E10097551 with your's device port)

```
esptool.py --chip esp32-S3 --port /dev/tty.wchusbserial56E10097551 erase_flash
esptool.py --port /dev/tty.wchusbserial56E10097551 write_flash -z 0x0 build/firmware.bin
```

4. You can use screen to test your changes

```
screen /dev/tty.usbmodem84722E9ED08A1 115200
```

## How to extend Circuitpython

Based on [this guide](https://learn.adafruit.com/extending-circuitpython/inside-the-virtual-machine), Circuitpython can be extended to use C modules. There is an example module called mymodule, it's present in the ./shared-bindings and ./shared-module folders.

If you want to create a new module, create the folder in the same locations and update the docker-compose.yml file. Add it to the volumes section, for example.

```
volumes
  - ./shared-bindings/mymodule:/circuitpython/shared-bindings/mymodule
  - ./shared-module/mymodule:/circuitpython/shared-module/mymodule
```

Then you can rebuild the source code. In case it doesn't update, try deleting the Docker container and image.
