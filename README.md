# mqttListener

a simple tool to read MQTT-messages

## How to use

Once you compiled the code, you can start it from the terminal of your choice. The first argument passed when starting it is interpreted as the topic to listen to. Every other argument is ignored.

You can also modify the settings.ini to set the host and port where the MQTT broker is running and modify the default topic (when no topic is passed).

The colors need to be known to the hash table (starts at line 15 in main.cpp) to be used.

## Requirements

Requires Qt Core and Qt Mqtt to run.

For using color codes, your Terminal needs to support the syntax.
