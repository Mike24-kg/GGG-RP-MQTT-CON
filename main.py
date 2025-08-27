from flask import Flask, request
import requests
import time
from pyngrok import ngrok
import json 
import paho.mqtt.client as mqtt
usernme = "#"
passwrd = "#"

client = mqtt.Client(protocol=mqtt.MQTTv311)
client.username_pw_set(usernme,passwrd)
client.connect("#", 1883, 60)
client.loop_start()
topic ="#/test"
app = Flask(__name__)

@app.route('/webhook', methods=['POST'])
def webhook():
    if request.method == 'POST':
        
        data = json.loads(request.data)
        payment_entity = data['payload']['payment']['entity']
        payment_metadata = payment_entity['notes']

        amount = str(payment_entity.get('amount'))[:-2]
        id = payment_entity.get('vpa')
        
        message = "Amount received:" +  amount + "||Received from:" + id
        print(message)
        if not client.is_connected():
            print("❌ MQTT client not connected at time of publish.")
        client.publish(topic,message)
        print(f"Published to topic '{topic}'")
        return "Webhook received!"
public_url = ngrok.connect(5000)
print(public_url)
app.run()
