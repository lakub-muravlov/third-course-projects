import redis
import os.path

env = "news_indiv"
file_name = "pub.txt"

client = redis.Redis(host='127.0.0.1', port=6379)

p = client.pubsub()
p.subscribe(env)

while True:
    message = p.get_message()
    if message:
        if os.path.exists(file_name):
            f = open(file_name, "a")
            f.write(str(message['data']))
        else:
            f = open(file_name, "w")
            f.write(str(message['data']))
