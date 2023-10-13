import pandas as pd
import numpy as np
import matplotlib.pylab as plt
import idx2numpy # very helpful library

# np.random.seed(555)
# loading the training and test datasets
train_images_data_old = idx2numpy.convert_from_file('train-images.idx3-ubyte')
train_images_data = []
train_labels_data = idx2numpy.convert_from_file('train-labels.idx1-ubyte')

test_images_data_old = idx2numpy.convert_from_file('t10k-images.idx3-ubyte')
test_images_data = []
test_labels_data = idx2numpy.convert_from_file('t10k-labels.idx1-ubyte')

for i in range(train_images_data_old.shape[0]):
    train_images_data.append(train_images_data_old[i].flatten())

for i in range(test_images_data_old.shape[0]):
    test_images_data.append(test_images_data_old[i].flatten())

# print(len(train_images_data))

def _step_function(x):
    if x >= 0:
        return 1
    else:
        return 0

step_function = np.vectorize(_step_function)

def multi_category_PTA(n, e, N, ep_max):
    W = np.random.uniform(-1.0, 1.0, (10, 784))
    
    errors = []
    epoch = 0

    while epoch <= ep_max and (epoch == 0 or errors[epoch-1]/(N+0.0) > e):
        # calc mis classifications
        errors.append(0)

        for i in range(N):
            v = np.dot(W, train_images_data[i])

            j = np.argmax(v)

            if j != train_labels_data[i]:
                errors[epoch] += 1
        
        print("epoch number:", epoch, ", errors:", errors[epoch], ", error:", (errors[epoch]/(N+0.0)), ", trying to reach:", e, end = '\r')

        epoch += 1

        d = np.zeros(10)
        for i in range(N):
            d[train_labels_data[i]] = 1

            inner = np.array([n * (d - step_function(np.dot(W, train_images_data[i])))]).T

            W = W + np.dot(inner, np.array([train_images_data[i]]))

            d[train_labels_data[i]] = 0
    
    print()
    if epoch == ep_max:
        print("Stopped at maximum epochs:", ep_max)
    elif errors[epoch-1] == 0:
        print("Stopped due to convergence")
        
    print()
    return W, epoch, errors

def test(N, W):
    error = 0
    
    for i in range(N):
        v = np.dot(W, test_images_data[i])

        j = np.argmax(v)

        if j != test_labels_data[i]:
            error += 1
    
    return error

fig, axs = plt.subplots(3)

def perform(n, e, N, ep_max, gc, subplot, plot):
    print("Performing the multi category PTA for n =", n, ", e =", e, ", N =", N, ", max epochs = ", ep_max)

    W, epoch, missclass = multi_category_PTA(n, e, N, ep_max)
    error = test(10000, W)

    print("The error rate for N =", N , "is :", (error/10000.0), '\n')

    print("mean of the iterations:", np.mean(missclass))

    if plot:
        axs[subplot].plot(np.arange(0, len(missclass)), missclass, gc)

max_epochs = 150

# perform(1, 0, 50, max_epochs, 'g-', 0, True)
# perform(1, 0, 1000, max_epochs, 'r-', 1, True)
# perform(1, 0, 60000, max_epochs, 'b-', 2, True)

perform(100, 0.13, 60000, max_epochs, 'b-', 0, True)
perform(1, 0.13, 60000, max_epochs, 'b-', 1, True)
perform(0.01, 0.13, 60000, max_epochs, 'b-', 2, True)

# axs[0].set_title("N = 50")
# axs[1].set_title("N = 1000")
# axs[2].set_title("N = 60000")


plt.show()