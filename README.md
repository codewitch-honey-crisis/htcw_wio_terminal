# ttgo

This library allows you to use the Wio Terminal devkit

```
[env:wio-terminal]
platform = atmelsam
board = seeed_wio_terminal
framework = arduino
lib_ldf_mode = deep
lib_deps = 	SPI
			Wire
			codewitch-honey-crisis/htcw_wio_terminal
monitor_speed = 115200
build_unflags=-std=gnu++11
build_flags=-std=gnu++14
```