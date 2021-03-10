import numpy as np
import pandas as pd
import random

# Random point generator with x, y bounds as +- specified value from origin
def rand_point(x_bound, y_bound):
    random.seed()
    x = random.uniform(-x_bound, x_bound)
    y = random.uniform(-y_bound, y_bound)
    return (x, y)

# Functions for labelling points
def quadrant(x, y):
    if x>=0 and y>=0:
        return 0
    elif x<0 and y>=0:
        return 1
    elif x<0 and y<0:
        return 2
    else:
        return 3

def rings(x, y):
    r = np.sqrt(x**2+y**2)
    if r > 1 and r < 2:
        return 0
    elif r > 3 and r < 4:
        return 1
    elif r > 5 and r < 6:
        return 2
    elif r > 7 and r < 8:
        return 3
    else:
        return 4

def yequalsxbound(x, y):
    if y>=x:
        return 0
    else:
        return 1


# Function for generating data set
def generate_data(nPoint, labeller, x_bound, y_bound, filename):
    points = []
    for i in range(nPoint):
        point = rand_point(x_bound, y_bound)
        points.append((*point, labeller(*point)))
    df = pd.DataFrame(points)
    df.to_csv(filename, index=False, header=False)

# Running generation
generate_data(50000, quadrant, 10, 10, "quadrant.csv")
generate_data(50000, rings, 10, 10, "rings.csv")
generate_data(50000, yequalsxbound, 10, 10, "yequalsxbound.csv")