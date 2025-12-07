from q1_a import pseudo_rand_num_gen, plotHistogram
from q1_b import getPiValues

# count = 100000
count = 100
piValues = getPiValues(count)
error = []
for i in range(count):
    error.append(abs(piValues[i] - 3.14159265358979323846) / abs(piValues[i]))
print(error)
plotHistogram(error)
