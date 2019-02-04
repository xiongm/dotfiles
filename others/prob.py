from random import randint

hit = 0

for _ in range(10000):
    car_1 = randint(1, 100)
    car_2 = randint(1, 100)
    while car_2 == car_1:
        car_2 = randint(1, 100)
    if abs(car_1 - car_2) == 1:
        hit += 1

print hit
print float(hit)/10000
