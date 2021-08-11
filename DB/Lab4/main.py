import redis

if __name__ == '__main__':
    r = redis.Redis()

    if 'integervalue' in r:
        del r['integervalue']
    pipe = r.pipeline()

    pipe.set('integervalue', 10)
    pipe.incr('integervalue')
    pipe.incr('integervalue')

    pipe.execute()