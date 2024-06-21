import pandas as pd 
import numpy as np 
# data viz
from matplotlib.colors import ListedColormap
import matplotlib.pyplot as plt
from matplotlib import rcParams
import seaborn as sns

# apply some cool styling
plt.style.use("ggplot")
rcParams['figure.figsize'] = (6,  6)
from perf_event_names import LABEL,CACHE_MISSES,L1_DCACHE_STORES

from datareader import namesList,ReadData_fromCsv
# from clustering import namesList
import os 


# CONTEXT_SWITCHES        ="context-switches"
# CPU_MIGRATIONS          ="cpu-migrations"
# CACHE_MISSES            ="cache-misses"
# CACHE_REFERENCES        ="cache-references"
# CPU_CYCLES              ="cpu-cycles"
# INSTRUCTIONS            ="instructions"
# BRANCH_MISSES           ="branch-misses"
# BRANCHES                ="branches"
# PAGE_FAULTS             ="page-faults"
# L1_DCACHE_LOAD_MISSES   ="L1-dcache-load-misses"
# L1_DCACHE_LOADS         ="L1-dcache-loads"
# L1_DCACHE_STORES        ="L1-dcache-stores"
# L1_ICACHE_LOAD_MISSES   ="L1-icache-load-misses"
# L1_DCACHE_STORES        ="L1-dcache-stores"
# LLC_LOAD_MISSES         ="LLC-load-misses"
# LLC_LOADS               ="LLC-loads"
# LLC_STORE_MISSES        ="LLC-store-misses"
# LLC_STORES              ="LLC-stores"
# SECONDS                 ="seconds"





def ScatterPlotDataAll(apps, modes,archs,attrs,outdir):
    for app in apps:
        for mode,attr in zip(modes,attrs):
            for arch in archs:  
                 ScatterPlotData(app,mode,arch,attr,outdir)

def ScatterPlotDataMany(apps, modes,archs,attr,out_dir="final_result",in_dir="final_result"):
    for app in apps:
        for mode in modes:
            for arch in archs:
                ScatterPlotData(app, mode,arch,attr,out_dir=out_dir,in_dir=in_dir)            

def ScatterPlotData(app, mode,arch,attr,out_dir="final_result",in_dir="final_result"):
    data = ReadData_fromCsv(app=app,mode=mode,arch=arch,data_root=in_dir) 
    if len(data) == 0 :
        return 
    # datadir = "../Data/result/"+app+"/"+arc+"/total/"+m+"/"
    outdir = "../"+out_dir+"/result/plot/"+app+"/"+arch+"/total/plot/"+mode+"/"
    # print("Ploating ", datadir)
    if not os.path.exists(outdir):    
        os.makedirs(outdir)
    # outdir = outdir+"/result/scatter_plot/" + app
    # if not os.path.exists(outdir):    
    #     os.makedirs(outdir)

    x = data[attr[0]]
    y = data[attr[1]]
    # features = data[:,0:18]
    labels = data[LABEL]

    # for index,name in enumerate(namesList):
    #     for j in range(index+1,len(namesList)):
    #         x = features[:,index]
    #         y = features[:,j]
    fig, ax = plt.subplots()      
    # plt.figure(0)
    cm_bright = ListedColormap(["#ff0000","#0000ff"])
    scatter = ax.scatter(x,y,c=labels,alpha=0.5,marker='x', label=labels, cmap=cm_bright, edgecolors="k")
    # handles, labels = scatter.legend_elements()
    # print(labels) #['$\\mathdefault{0}$', '$\\mathdefault{1}$']
    fontsize=16
    plt.legend(fontsize=fontsize)  # Adjust fontsize as needed
    # ax.legend(["vuln","no_vuln"])
    # produce a legend with the unique colors from the scatter
    # print(*scatter.legend_elements()[0])
    legend1 = ax.legend([*scatter.legend_elements()[0]],["False","True"], #["No_Duplicate","Duplicate"]
                    loc="upper left", title="Function results",bbox_to_anchor=(0, 1))
    ax.add_artist(legend1)


    plt.xlabel(attr[0],fontsize=fontsize)
    plt.ylabel(attr[1],fontsize=fontsize)
    plt.xticks(fontsize=fontsize)  # Adjust fontsize as needed
    plt.yticks(fontsize=fontsize)  # Adjust fontsize as needed
    # plt.legend(fontsize=10)  # Adjust fontsize as needed
    plt.tight_layout()
    filename = app+"_"+arch+"_"+mode+"_"+attr[0]+attr[1] + ".png"
    path = os.path.join(outdir,filename)
    plt.savefig(path)
    
    plt.close()
            

def PairPlot(df,outdir,outfilename):
    color_dict = dict({1:'#ff3000',
                  0:'#00a0ff'
                  })
    label_to_marker = {1: 'o', 0: 'x'}
    scatter_kws = {'s': 100, 'alpha': 0.5}
    # sns.pairplot(df, 
    #          hue=LABEL,palette=color_dict, plot_kws=scatter_kws, corner=True)
    
    sns.pairplot(df, hue=LABEL, palette=color_dict, plot_kws=scatter_kws, corner=True)#, markers=[label_to_marker.get(x) for x in df[LABEL].unique()])
    
    # g= sns.pairplot(df,hue=LABEL,palette=color_dict,corner=True)
    outfilename = os.path.join(outdir,outfilename)
    plt.savefig(outfilename)
    plt.close()

            

def Plot_one(app,mode,arch,attr=None,out_dir_root="final_result",in_dir="final_result"):    
  
    # datadir = "../Data/result/"+app+"/"+arc+"/total/"+m+"/"
    outdir = "../"+out_dir_root+"/result/plot/"+app+"/"+arch+"/total/plot/"+mode+"/"
    # print("Ploating ", datadir)
    if not os.path.exists(outdir):    
        os.makedirs(outdir)

    data = ReadData_fromCsv(app=app,mode=mode,arch=arch,data_root=in_dir) #np.array(DirToArray(datadir))
    # if len(data) == 0:
    #     continue

    if not (attr == None):
        features = data[:,attr] 
        col_names = [namesList[x] for x in attr]
        
        #genrate output file name by combining the event names using _
        name = "_".join(col_names) 
        name = name+".png"                      
        outfilename = name #os.path.join(outdir,name)

    else:
        features = data
        col_names = data.columns #namesList.copy()
        # col_names.append("labels") 
        outfilename="all_minmax.png"

    # scaler = MinMaxScaler()   #StandardScaler() #
    # features= scaler.fit_transform(features)
    # labels =  data[:,18:19].astype(int)
    
    df = data #pd.DataFrame(data=features,columns=col_names)
    # df['labels'] = labels
    PairPlot(df,outdir,outfilename)
    # plotCorrelationHeatMap(df,outdir)




def PlotAll(apps,modes,archs,attr=None,out_dir_root="final_result",in_dir="final_result"):    
    for app in apps:
        for m in modes:
            for arc in archs:
                Plot_one(app,m,arc,out_dir_root,in_dir)
                # # datadir = "../Data/result/"+app+"/"+arc+"/total/"+m+"/"
                # outdir = "../"+out_dir_root+"/result/plot/"+app+"/"+arc+"/total/plot/"+m+"/"
                # # print("Ploating ", datadir)
                # if not os.path.exists(outdir):    
                #     os.makedirs(outdir)

                # data = ReadData_fromCsv(app=app,mode=m,arch=arc,data_root=in_dir) #np.array(DirToArray(datadir))
                # # if len(data) == 0:
                # #     continue

                # if not (attr == None):
                #     features = data[:,attr] 
                #     col_names = [namesList[x] for x in attr]
                    
                #     #genrate output file name by combining the event names using _
                #     name = "_".join(col_names) 
                #     name = name+".png"                      
                #     outfilename = name #os.path.join(outdir,name)

                # else:
                #     features = data
                #     col_names = data.columns #namesList.copy()
                #     # col_names.append("labels") 
                #     outfilename="all_minmax.png"

                # # scaler = MinMaxScaler()   #StandardScaler() #
                # # features= scaler.fit_transform(features)
                # # labels =  data[:,18:19].astype(int)
               
                # df = data #pd.DataFrame(data=features,columns=col_names)
                # # df['labels'] = labels
                # PairPlot(df,outdir,outfilename)
                # # plotCorrelationHeatMap(df,outdir)



if __name__ == "__main__":   
    features =['execution-time', L1_DCACHE_STORES] #names[CPU_CYCLES], names[INSTRUCTIONS],
   
    apps = ["maxrun"] #["validParenthesis","distinctness","distinctness_leaky","add","frequency"]#["distinctness","add","bubblesort","contains","frequency","validParenthesis","setintersection8"] #["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2"]#["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2","contains"]    
    modes =["dodo0"]#["do","normal"]
    archs = ["sgx"] #["native","sgx",] #"sgx",
    # ScatterPlotDataAll()
    ScatterPlotDataMany(apps, modes,archs,features,out_dir="final_result_seed_Nov5_submitted",in_dir="final_result_seed_Nov5_submitted")

    # PlotAll(apps=apps,modes=modes,archs=archs,out_dir_root="final_result_new",in_dir="final_result_new")

   