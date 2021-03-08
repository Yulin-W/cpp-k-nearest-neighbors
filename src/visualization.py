import matplotlib.pyplot as plt
import pandas

df = pandas.read_csv("./input.csv", header=None)
groups = df.groupby(df.columns[2])
for name, group in groups:
    plt.plot(group.iloc[:,0], group.iloc[:,1], marker='o', linestyle='', label=name)
plt.show()