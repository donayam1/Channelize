
import numpy as np 
import os 
import matplotlib.pyplot as plt 
from numpy import percentile
from sklearn.preprocessing import StandardScaler, MinMaxScaler
import pandas as pd 
from scipy import stats
from perf_event_names import NamesToIndexMap,namesList,SECONDS, LABEL,CONTEXT_SWITCHES,CPU_MIGRATIONS,PAGE_FAULTS




# names={"context-switches":0,
#        "cpu-migrations":1,
#        "cache-misses":2,
#        "cache-references":3,
#        "cpu-cycles":4,
#        "instructions":5,
#        "branch-misses":6,
#        "branches":7,
#        "page-faults":8,
       
#        "L1-dcache-load-misses":9,
#         "L1-dcache-loads":10,   
#         "L1-dcache-stores":11,     
#         "L1-icache-load-misses":12,          
#         "LLC-load-misses":13,
#         "LLC-loads":14,
#         "LLC-store-misses":15,
#         "LLC-stores":16,
#        "seconds":17,
#        "execution-time":17,
#        "label":18,
#        }

# namesList=[
#        "context-switches",
#        "cpu-migrations",
#        "cache-misses",
#        "cache-references",
#        "cpu-cycles",
#        "instructions",
#        "branch-misses",
#        "branches",
#        "page-faults",
       
#         "L1-dcache-load-misses",
#         "L1-dcache-loads",   
#         "L1-dcache-stores",     
#         "L1-icache-load-misses",          
#         "LLC-load-misses",
#         "LLC-loads",
#         "LLC-store-misses",
#         "LLC-stores",
#        "execution-time"]#,
#     #    "label"]

# namesInverse = {v:k for k,v in names.items()}

"""
Reads a file containing logs with a specific format and determines the label for the data 
based on the file name prefix. If the file name starts with 't_', the label is 1. If 
the file name starts with 'f_', the label is 0 (False). 

Expected log format:
    cache-misses:1198
    cache-references:951531
    context-switches:0
    cpu-migrations:0
    cpu-cycles:17428866
    instructions:17142
    branch-misses:160
    branches:9374
    page-faults:72
    L1-dcache-load-misses:229044
    L1-dcache-loads:1800
    L1-dcache-stores:0
    L1-icache-load-misses:222237
    LLC-load-misses:0
    LLC-loads:46168
    LLC-store-misses:0
    LLC-stores:22609
    seconds:20.1512

Parameters:
    filepath (str): The full path to the file, including the file name.
    filename (str): The file name, without the path.

Returns:
    list: A 1D list if the file exists and is successfully parsed; an empty list otherwise.
"""
def ToArrayNew(filepath,filename):
    label = 0 
    if "t_" in filename:
        label = 1 
    elif "f_" in filename:
        label = 0 
    else:
        print("Error file name does not start with 't_' or 'f_'. ")
        exit(1)
        
    lines = []
    try:
        with open(filepath) as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"File {filepath} not found")
    
    item= []
    for line in lines:
        
        if len(line.strip()) == 0: #if it is an empty string move to the next string 
            continue
        cols = line.split(sep=":")    
        index = NamesToIndexMap[cols[0]]           
        if cols[0] != SECONDS: #"seconds":            
            item.insert(index,int(cols[1])) 
        else: 
            item.insert(index,float(cols[1])) 

    if len(item) == 0:
        return []
    
    item.insert(NamesToIndexMap[LABEL],label)              
    # item.append(label)

    return item 
  
  
'''

Reads a file containing logs with a specific format and determines the label for the data 
based on the file name prefix. If the file name starts with 't_', the label is 1. If 
the file name starts with 'f_', the label is 0 (False). 

# started on Mon Oct 31 10:13:11 2022


 Performance counter stats for './app Data/input/f_rand1.txt':

            84,594      context-switches                                            
                32      cpu-migrations                                              
           333,075      cache-misses              #    4.265 % of all cache refs      (83.52%)
         7,810,248      cache-references                                              (83.53%)
       999,169,510      cpu-cycles                                                    (67.47%)
       714,720,270      instructions              #    0.72  insn per cycle           (83.90%)
         2,940,328      branch-misses             #    4.59% of all branches          (83.91%)
        64,013,705      branches                                                      (81.57%)
               386      page-faults                                                 

       8.893907894 seconds time elapsed

       8.985305000 seconds user
       0.298167000 seconds sys
       
Parameters:
    filepath (str): The full path to the file, including the file name.
    filename (str): The file name, without the path.

Returns:
    list: A 1D list if the file exists and is successfully parsed; an empty list otherwise.       

'''
def ToArray(filepath,filename):
    label = 0 
    if "t_" in filename:
        label = 1 
    elif "f_" in filename:
        label = 0 
    else:
        print("Error file name does not start with t_ or f_")
        exit(1)
    lines = []
    try:
        with open(filepath) as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"File {filepath} not found.")
        
    item= []
    for line in lines:
        
        if len(line.strip()) == 0: #if it is an empty string move to the next string 
            continue
        cols = line.split()
        # print(cols)
        col0 = cols[0].replace(",","")
        col1 = col0.replace('.','',1)
        if col0.isnumeric() == False and col1.isnumeric() == False:
            continue

    
        # index = names[cols[1]]    
        if cols[1] != SECONDS:
            col0 = int(col0)
            item.append(col0) #item.append((index,col0))
        elif cols[1] == SECONDS and cols[2] == "time":
            item.append(float(col0)) #item.append((index,float(col0)))
        else:
            continue
    
    if len(item) == 0:
        return []
        

    # while len(item) < 18:
    #     item.append(0)     
        
    item.insert(NamesToIndexMap[LABEL],label)    
    # item.append(label)

    return item 
    

"""
Reads all files in a directory and returns their contents as a 2D list.

Parameters:
    directory (str): The directory where the files are located.
    fileParser (function): A function that takes a file path (including file name) and the file name, 
                           and returns a 1D list of the file content.
    removeOutliers (bool): If set to True, removes outliers from the data. 
                           This involves removing all data points that have an execution time greater 
                           than 2 times the Interquartile Range (IQR).

Returns:
    list: An empty list if the directory does not exist or is empty. Otherwise, returns a 2D list 
          containing the contents of all the files in the directory.
"""
def DirToArray(directory,fileParsor=ToArrayNew,removeOutliers=True):
    try:
        files = os.listdir(directory)
    except FileNotFoundError:
        files = []
        
    if len(files) == 0:
        return []
    datas = []
    for file in files:
        path = os.path.abspath(os.path.join(directory, file))
        data = fileParsor(path,file)
        if  not (data == None):
            datas.append(data)    
    datas = np.array(datas)   
    
    if removeOutliers == True:
        q25, q75 = percentile(datas[:,[NamesToIndexMap[SECONDS]]], 25), percentile(datas[:,[NamesToIndexMap[SECONDS]]], 75)
        iqr = q75 - q25
        cut_off = iqr * 2
        lower, upper = q25 - cut_off, q75 + cut_off
        outliers_removed = [x for x in datas if  x[NamesToIndexMap[SECONDS]] <= upper]#features[:,0]
        return outliers_removed
    
    else: 
        return datas




def ReadAllData(apps,modes,archs,normalize=True):    
    all = np.empty((0,19))
    for app in apps:
        for m in modes:
            for arc in archs:
                datadir = "../Data/result/"+app+"/"+arc+"/total/"+m+"/"
                data = np.array(DirToArray(datadir))

                features = data[:,0:18]
                labels = data[:,18:19]

                if normalize == True:                
                    scaler = StandardScaler()      #MinMaxScaler()  
                    scaled_data = scaler.fit_transform(features)
                    # all = np.append(all,dos,axis=0)
                    scaled_data = np.append(scaled_data,labels,axis=1)
                else:
                    scaled_data = data 

                all = np.append(all,scaled_data,axis=0)
    return all 

def ToCVS_One(app,mode,arch,res_dir="result",out_root="final_result",fileParsor=ToArrayNew): 
    
    cols = namesList.copy()
    cols.append(LABEL) #"labels"

    outdir = "../"+out_root+"/all_csv"
    if not os.path.exists(outdir):    
        os.makedirs(outdir)
    
    datadir = "../Data/"+res_dir+"/"+app+"/"+arch+"/total/"+mode+"/"  
    
    if not os.path.exists(datadir):
        return 
    
    data = np.array(DirToArray(datadir,fileParsor=fileParsor))
    if len(data) == 0:
        return 
    
    name = arch+"_"+app+"_"+mode+".csv"
        
    df = pd.DataFrame(data,columns=cols)
    

    outfilename = os.path.join(outdir,name)
    # print(outfilename)
    df.to_csv(outfilename,index=False,header=True)
    
def ToCSV(apps,modes,archs,res_dir="result",out_root="final_result",fileParsor=ToArrayNew):    
    for app in apps:
        for mode in modes:
            for arch in archs:
                ToCVS_One(app=app,mode=mode,arch=arch,res_dir=res_dir,out_root=out_root,fileParsor=fileParsor)


"""
Reads log data from a CSV file.

Expected directory structure:
    ../data_root
        all_csv
            arch_app_mode.csv

Parameters:
    app (str): Name of the test application, e.g., 'add', 'contains', 'distinctness', etc.
    mode (str): Mode of application implementation, e.g., 'do', 'normal'.
    arch (str): The target architecture of the application, e.g., 'sgx', 'se', 'native'.
    normalize (bool): If True, normalize each data column using a standard scaler.
    data_root (str): Root directory where the file is stored. It is assumed that the data is stored
                     under the parent directory of the directory this file is under, in a directory 
                     named as specified by this variable.

Returns:
    Pandas DataFrame: A DataFrame containing the data if it exists, or an empty DataFrame if the data does not exist.
""" 
def ReadData_fromCsv(app,mode,arch,normalize=True,data_root="final_result"):    
    fn = arch+"_"+app+"_"+mode+".csv"
    datadir = "../"+data_root+"/all_csv/"+fn 
    if not os.path.exists(datadir):
        return  pd.DataFrame()
    
    data = pd.read_csv(datadir)    
    
    data = data.loc[:, (data != 0).any(axis=0)]
    
    labels = data[LABEL]
    columns_to_drop = [LABEL,CONTEXT_SWITCHES,CPU_MIGRATIONS,PAGE_FAULTS]
    columns_to_drop_existing = [col for col in columns_to_drop if col in data.columns]
    features = data.drop(columns_to_drop_existing, axis=1)

    if normalize == True:    
        # Apply StandardScaler to data_df
        scaler = StandardScaler()
        scaled_data = scaler.fit_transform(features)

        # Create a new DataFrame with scaled data and label
        scaled_df = pd.DataFrame(scaled_data, columns=features.columns)
        combined_df = pd.concat([scaled_df,labels], axis=1)
    else:
        combined_df = data     
    return combined_df


if __name__ == "__main__": #"contains","setintersection8","bubblesort",
    
    apps = ["maxrun"]# ,"validParenthesis","distinctness_leaky","frequency"] #["validParenthesis","distinctness","distinctness_leaky","add","frequency"]#["distinctness","add","bubblesort","contains","frequency","validParenthesis","setintersection8"] #["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2"]#["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2","contains"]    
    modes =["do"]#["do","normal"]
    archs = ["se"]# ,"sgx","se"] 
    
    ToCSV(apps,modes,archs,res_dir="result",out_root="final_result_new",fileParsor=ToArrayNew)
    
    # apps= []
    # modes =["do","normal"] #"do"
    # archs = ["sgx","native","se"]
    # dirs = os.listdir("../final_result_new/result/clustering")
    # for f in dirs:
    #     apps.append(f)    
    # CombineResultsToSingleCsv(apps,modes,archs,data_root="final_result_new")   


    

    
   