import pandas as pd 

root_dir = "../final_result_new/result/clustering/"
allcsv = root_dir+"all.csv"
df = pd.read_csv(allcsv)  
print(df)


# Iterate over the rows
for index, row in df.iterrows():
    # Find the maximum value in the row
    
    # Find the column with the value furthest from 0.5
    furthest_value = row.iloc[-4:].apply(lambda x: abs(x - 0.5)).idxmax()
    
    # Get the corresponding value and column name
    selected_value = row[furthest_value]
    selected_column = furthest_value
    
    # Format the new column based on the value comparison
    if selected_value > 5.5 or selected_value < 4.5:
        formatted_value = f"V({selected_value}%)"
    else:
        formatted_value = f"NV({selected_value}%)"
    
    # Add a new column with the formatted value and column name
    df.loc[index, 'Selected Column'] = f"{selected_column} ({formatted_value})"

df.to_csv(root_dir+"labeled.csv")
print(df)