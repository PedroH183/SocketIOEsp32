run:
	pio run
	pio run --target upload --upload-port /dev/ttyACM0
	pio device monitor --port /dev/ttyACM0

lst:
	ls /dev/ | grep -e "tty" -e "ACM"