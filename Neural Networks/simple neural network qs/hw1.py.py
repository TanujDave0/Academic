import random
import matplotlib.pyplot as plt

w = [[1,-1],
     [-1,-1],
     [-1,0]]

b = [1,1,0]

def step_function(x):
    if x >= 0:
        return 1
    else:
        return 0

def hidden_neurons(x, y, i):
    return step_function(w[i][0]*x + w[i][1]*y + b[i])

def output_neuron(y1, y2, y3):
    return step_function(y1+y2-y3-1.5)

def neural_network(x,y):
    return output_neuron(
        hidden_neurons(x,y,0),
        hidden_neurons(x,y,1),
        hidden_neurons(x,y,2)
    )

x1 = []
y1 = []
x2 = []
y2 = []

for i in range(1000):
    x = (random.uniform(-2,2))
    y = (random.uniform(-2,2))

    if neural_network(x,y) == 0:
        x1.append(x)
        y1.append(y)
    else:
        x2.append(x)
        y2.append(y)

print(neural_network(0,1))
print(neural_network(1,0))

plt.plot(x1, y1, 'bo', x2, y2, 'ro')
plt.show()