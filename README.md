# MagicKitty
Slack enabled kitty/donation box with pretty LEDs!

## Orly?
Attempting to build a little kitty/donation box that will detect when something (hopefully money) is inserted, then fires off a slack message and dazzles some LEDs.

Google GeoLocation API is used to determine an estimated location (posted to Slack when the kitty turns on).

Slack WebHook is required to post a message to the desired Slack channel.

### Config file!
key.h becomes your config file - and should be excluded from being pushed to a repo. This repo includes "keys.h.sample" to show where the following config items are stored:

#### Slack configuration
You will need to configure an "Incoming Webhook" on your Slack space to allow messages to be POST'd. You can find documentation on how to create a new webhook here; https://api.slack.com/incoming-webhooks

#### Google API key
To use the Geolocation API, you will need an API key. The Google doc here should help; https://developers.google.com/maps/documentation/geolocation/intro

The library in use for this API can be found here; https://github.com/gmag11/WifiLocation

#### Wifi connection
This part is easy, just define your SSID and Password to allow your chip to connect.


## Hardware
+ Adafruit huzzah esp8266 - https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/overview
+ Laser module
+ Photo resister sensor module
+ 1k resistor
+ 220ohm resistor
+ FastLED supporting LED strip (for pretty colours, eg; WS2812B)
