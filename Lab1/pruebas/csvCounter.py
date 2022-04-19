import pandas as pd

df = pd.read_csv("bogota-cadastral-2020-1-All-HourlyAggregate.csv") #===> reads in all the rows, but skips the first one as it is a header.

total_rows=len(df.axes[0]) #===> Axes of 0 is for a row

print("Number of Rows: "+str(total_rows))