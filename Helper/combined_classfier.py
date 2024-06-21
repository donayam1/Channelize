import numpy as np 
from clustering import ReadAllData,namesList
import pandas as pd 
import matplotlib.pyplot as plt 
#1 yello -> vulnerable 
#0 brown -> non vulnerable 

apps  =["add"]
modes =["do","normal"]
archs =["native"]

cols = namesList.copy()
cols.append('label')

data = ReadAllData(apps,modes=["do"],archs=archs)
df = pd.DataFrame(data,columns=cols)
df.loc[df['label']==1, 'label'] = 0

data_n = ReadAllData(apps,modes=["normal"],archs=archs)
df_n= pd.DataFrame(data_n,columns=cols)
df_n.loc[df_n['label']==0, 'label'] = 1
vuln = df_n.loc[df_n['label']==1]

all_data = pd.concat([df,vuln])
print(all_data.head())

plt.scatter(all_data['execution-time'],all_data['cache-misses'],c=all_data['label'])
# plt.legend()
plt.savefig("new_scatter.png")