from datetime import datetime
import matplotlib.pyplot as plt


def getInitialSeed():
    current_time = datetime.now().strftime('%H%M%S')
    print("time is " + current_time)
    return current_time


def pseudo_rand_num_gen(seed, k):
    result = []
    for loop in range(0, k):
        tempstr = str(int(seed) ** 2)
        if len(tempstr) % 2 != 0:
            tempstr = tempstr.zfill(len(tempstr) + 1)
        # slicing only if no of digits >= 4
        if int(len(tempstr)) / 2 - 2 > 0:
            temp = tempstr[int(len(tempstr) // 4): -int(len(tempstr) // 4)]
        else:
            temp = int(tempstr)
        # converting to int for squaring , then converting to string again for slicing.
        # using zfill for padding to length 8
        result.append(int(temp))
        seed = temp
    return result


def plotHistogram(ar):
    plt.hist(ar, bins=20, color='blue', edgecolor='black')
    # each bin represents a range of values. 20 bins means that the list is divided into 20 equal ranges in the graph
    plt.title('Pseudo-Random Number Distribution (Normalized)')
    plt.xlabel('Random Numbers (After Normalization)')
    plt.ylabel('Frequency')
    plt.show()


if __name__ == '__main__':
    kUserInput = int(input('Enter k\n'))
    listRandomNumbers = pseudo_rand_num_gen(getInitialSeed(), kUserInput)
    print(listRandomNumbers)

    # Divide by 10^n where n is the number of digits in the seed
    listRandomNumbers = [num / 10 ** len(str(num)) for num in listRandomNumbers]

    plotHistogram(listRandomNumbers)
