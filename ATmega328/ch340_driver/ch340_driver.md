
# CH340 driver for Arduino Nano clone
# <http://www.wch.cn/download/CH341SER_MAC_ZIP.html>
# http://fr.aliexpress.com/item/-/32272029870.html

# Check if Apple protection is active
	nvram boot-args

# If protection is deactivated : `nvram: Error getting variable - 'boot-args': (iokit/common) data was not found A`
# If protection is activated : `boot-args	kext-dev-mode=1`

# Activate protection
	nvram -d boot-args

# Deactivate protection
	nvram boot-args=kext-dev-mode=1

