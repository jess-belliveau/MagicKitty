# MagicKitty
Slack enabled kitty/donation box with pretty LEDs!

## Orly?
Attempting to build a little kitty/donation box that will detect when something (hopefully money) is inserted, then fires off a slack message and dazzles some LEDs.

Google GeoLocation API is used to determine an estimated location (posted to Slack when the kitty turns on).

Slack WebHook is required to post a message to the desired Slack channel.

## Hardware
+ Adafruit huzzah esp8266 - https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/overview
+ Laser module
+ Photo resister sensor module
+ 1k resistor
+ 220ohm resistor
