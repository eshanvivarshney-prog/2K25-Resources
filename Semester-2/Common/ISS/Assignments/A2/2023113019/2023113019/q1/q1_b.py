from q1_a import pseudo_rand_num_gen
import random


def checkIfCircle(x, y):
    if (x ** 2) + (y ** 2) <= 1:
        return True
    else:
        return False


def getCountInCircle(array, count):
    ind2 = int(count / 2)
    count_in_circle = 0
    for i in range(0, ind2 - 1):
        if checkIfCircle(array[i], array[ind2 + i]):
            count_in_circle += 1
    return count_in_circle


def getPi(count_in_circle, count_in_square):
    pi_calculated = 3.14
    # putting this as default value for cases where no point falls in square or circle: only initial cases
    if count_in_square and count_in_circle:
        pi_calculated = 4 * count_in_circle / count_in_square
    # print(count_in_circle, pi_calculated)
    return pi_calculated

def getPiValues(count):
    ar = pseudo_rand_num_gen("215035", count)
    # print(ar)
    array = []
    piValues = []
    for i in range(count):
        x = 10 ** (len(str(ar[i])))
        array.append(((2 * ar[i]) / x) - 1)
        piValues.append(getPi(getCountInCircle(array, i), i / 2))
    # print(piValues)
    # print(array)
    return piValues


if __name__ == '__main__':
    # count = 100000
    count = 100
    pi_method1 = getPiValues(count)[-1]
    pi_method2 = 0
    counter2 = 0

    xAr = [random.uniform(-1, 1) for i in range(count)]
    yAr = [random.uniform(-1, 1) for i in range(count)]
    for i in range(count):
        if checkIfCircle(xAr[i], yAr[i]):
            counter2 += 1
    print(counter2)
    pi_method2 = getPi(counter2, count / 2)

    print('Using my own seed: Pi : ', pi_method1)
    print("Using random.random : Pi: ", pi_method2)
