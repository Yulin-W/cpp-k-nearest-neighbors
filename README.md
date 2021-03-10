# CPP k nearest neighbor
## Example output plots of the code
- Different colors represent different labels, round point represent training set, cross represent input with predicted labels
## Intro
- What the code does
  - Produce label predictions for points on a plane based on training set of labelled points based on the K-nearest neighbours algorithm
  - Produce plot of the training points and predicted input points
## Usage
1. Load training data into training.csv
  - Expected format:
      - CSV
      - Each row corresponds to point
      - Expects 3 values in each row, respectively in order x, y, label
      - Label is expected to be an integer from 0 to 11
2. Load input data into input.csv
  - Expected format:
      - CSV
      - Each row correspond to point
      - Expects 2 values in each row, respectively in order x, y coordinate of the point
3. Set K value in knnlabelmodule.cpp
4. Compile and run knnlabelmodule.cpp to generate output.csv, containing the label predictions for input points read
5. Run visualization.py to plot the training data and input with predicted labels, different label values have different colors (up to 12) with markers for differentiating training data and input data with predicted labels:
   - Training data: round points
   - Input with predicted label: cross
### Notes
- /training includes numerous training sets, copy into /src and rename to training.csv to use.
- /training/data_generator.py is a script used to generate the training data sets in /training.