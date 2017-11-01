"""
For testing purpose, write a script to send requests at random weight distribution

"""
import random
from collections import defaultdict


def send(request):
    pass

some_requests = {'r1': 0.5, 'r2': 0.2, 'r3': 0.3}

assert sum(some_requests.values()) == 1

NUM_SAMPLES = 100
samples = []

for request, weight in some_requests.items():
    samples.extend([request] * int(NUM_SAMPLES * weight))

assert len(samples) == NUM_SAMPLES

NUM_OF_REQUESTS = 100000

stats = defaultdict(int)
for _ in range(NUM_OF_REQUESTS):
    r = random.choice(samples)
    send(r)
    stats[r] += 1

print('stats:', dict(stats))
