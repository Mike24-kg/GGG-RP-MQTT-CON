# GGG-RP-MQTT-CON
A program to connect razorpay account and saves any amount sent to the account temporarily. Once done it connects to an mqtt topic which an esp32 is subscribed to. Once the specific amount requirement is met, a message is pub to the topic triggering the esp32.
