import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import pandas

# Constants for visualization
TRAIN_MARKER = 'o'
INPUT_MARKER = 'x'
COLORS = ['b', 'g', 'r', 'c', 'm', 'y', 'k', "orange", "darkred", "teal", "midnightblue", "indigo"]

# Plot training data
df_training = pandas.read_csv("./training.csv", names=["x", "y", "label"])
groups_training = df_training.groupby("label")
for name, group in groups_training:
    plt.plot(group.iloc[:,0], group.iloc[:,1], marker=TRAIN_MARKER, linestyle='', color=COLORS[name%len(COLORS)])

# Plot input and output data
df_input = pandas.read_csv("./input.csv", names=["x", "y"])
df_output = pandas.read_csv("./output.csv", names=["label"])
df_io = pandas.concat([df_input, df_output], axis=1)
groups_io = df_io.groupby("label")
for name, group in groups_io:
    plt.plot(group.iloc[:,0], group.iloc[:,1], marker=INPUT_MARKER, linestyle='', color=COLORS[name%len(COLORS)])

# Show plot
plt.show()