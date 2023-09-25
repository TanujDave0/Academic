#imports
import random
import matplotlib.pyplot as plt
import numpy as np

random.seed(555)
N = 100
subplots = 2

fig, axs = plt.subplots(subplots)

# initializing all vars
w0 = random.uniform(-0.25, 0.25)
w1 = random.uniform(-1,1)
w2 = random.uniform(-1,1)

print("w0, w1, w2 picked uniformly are:", w0, ",", w1, ",", w2)

# the set of 100 uniform points in [-1,1]^2
S = []

for i in range(N):
    S.append([random.uniform(-1,1), random.uniform(-1,1)])

S1 = []
S0 = []
d = []

# assigning to S1 or S0
for [x1,x2] in S:
    if (w0 + w1*x1 + w2*x2) >= 0:
        S1.append([x1,x2])
        d.append(1)
    else:
        S0.append([x1,x2])
        d.append(0)

# print("S:", S)
# print("S0:", S0)
# print("S1:", S1)

# plotting the line and points
S1x = [x for [x,y] in S1]
S1y = [y for [x,y] in S1]
S0x = [x for [x,y] in S0]
S0y = [y for [x,y] in S0]

line_x = np.array([-1,0,1])
line_y = (-w0 - w1*line_x)/w2

# plotting the lines and the points
axs[0].plot(line_x, line_y, 'k-') # black line
axs[0].plot(S1x, S1y, 'bo') # blue circles for S1
axs[0].plot(S0x, S0y, 'gs') # green squares for S0

# picking random weights for PTA
wt0 = random.uniform(-1, 1)
wt1 = random.uniform(-1,1)
wt2 = random.uniform(-1,1)

print("The random weights picked for PTA are:", wt0, ",", wt1, ",", wt2)

# step function
def step(x):
    if x >=0:
        return 1
    else:
        return 0

# function to check if weights produce a desired solution
def solution(w, X, D):
    mul = []
    sol = []
    ans = 0
    
    mul = np.matmul(X,w)

    sol = [step(x) for x in mul]

    for i in range(len(D)):
        if sol[i] != D[i]:
            ans = ans + 1

    return ans

# the perceptron training algorithm
def PTA(W, X, D, n):
    w = W.copy()
    mis = []
    epoch = 0
    size = len(D)
    wrong = solution(w, X, D)

    while wrong > 0:
        mis.append(wrong)
        epoch = epoch + 1

        for i in range(size):
            y = step(np.dot(X[i],w))

            if y == 1 and D[i] == 0:
                # w = w - n*X[i]
                for j in range(len(w)):
                    w[j] = w[j] - n*X[i][j]
            elif y == 0 and D[i] == 1:
                for j in range(len(w)):
                    w[j] = w[j] + n*X[i][j]
        
        wrong = solution(w, X, D)
    
    mis.append(wrong)

    return epoch, mis, w

# adding 1 to the coordiantes for PTA
S = [[1,x,y] for [x,y] in S]

# the function that calls the PTA for specific N and plots the
# produced line using the produced  weights
def PTA_for_n(n, w_arr, col1, col2):
    epoch1, mis1, w1 = PTA(w_arr, S, d, n)

    print("total epochs taken for n =", n, ": ", epoch1)
    # print("misclassification for each iteration for n =", n , ": ", mis1)
    print("the final weights for n =", n, ": ", w1)

    # plotting the line using the updated weights
    line_x_1 = np.array([-1,0,1])
    line_y_1 = (-w1[0] - w1[1]*line_x_1)/w1[2]
    axs[0].plot(line_x_1, line_y_1, col1)

    # plotting the misclassification line for
    axs[1].plot([i for i in range(epoch1+1)], mis1, col2)


PTA_for_n(1, np.array([wt0, wt1, wt2]), 'r-.', 'r-')
PTA_for_n(10, np.array([wt0, wt1, wt2]), 'y-.', 'y-')
PTA_for_n(0.1, np.array([wt0, wt1, wt2]), 'm-.', 'm-')


axs[0].axis([-1, 1, -1, 1])
axs[0].legend(['Boundary', 'S1', 'S0', 'B2', 'B3', 'B4'], loc = 'upper right')
axs[1].legend(['n = 1', 'n = 10', 'n = 0.1'], loc = 'upper right')
axs[0].set_title("S1, S0 and the Boundaries")
axs[1].set_title("The misclassification for different Ns")
plt.show()