import numpy as np
import matplotlib.pyplot as plt
import pandas as pd 
import os

def LoadData(names,path):
    # names=["GradientBoosting.csv","LogisticRegression.csv","RandomForest.csv","SVM(rbf kernel).csv"]
    # path="/Users/donayam/Documents/SecurityClosure/results/native/"
    dirs_base_name = "result_"
    modes = ["normal","do"]


    files_normal={}
    files_do={}
    for mode in modes:
        dir = dirs_base_name+mode
        base_dir = os.path.join(path,dir)

        for name in names:
            full_path = os.path.abspath(os.path.join(base_dir,name))
            df = pd.read_csv(full_path)
            # print(df.head())
            if mode == "do":
                files_do[name] = df 
            else:
                files_normal[name] = df 
        
    return files_do,files_normal

color={"DO":"#00a0ff","Normal":"#ff3000"}
def RadarPlot(datas,subject0,uppers,lowers,conf_intervals, fills,labels,ax):
    angles=np.linspace(0,2*np.pi,len(subject0), endpoint=False)
    angles=np.concatenate((angles,[angles[0]]))
    subjects = subject0.copy()
    subjects.append(subjects[0])

    for data,upper,lower,conf_interval,fill,label in zip(datas,uppers,lowers,conf_intervals,fills,labels):
        data.append(data[0])
        upper.append(upper[0])
        lower.append(lower[0])
        ax.plot(angles, data, 'o-', c=color[label],  linewidth=1, label=label)

        if fill == True:
            # ax.tick_params(pad=20)
            ax.tick_params(axis='both', which='major', labelsize=7)
            ax.fill(angles, data, color=color[label], alpha=0.25, )
        if conf_interval:
            plt.fill_between(angles, upper, lower, facecolor='b', alpha=0.2)

    ax.set_thetagrids(angles * 180/np.pi, subjects)

    # ax.set_rmax(1)
    # ax.set_rticks([]) 


    plt.gcf().canvas.draw()
    angles = np.linspace(0,2*np.pi,len(subjects))
    angles = angles + -np.pi/2
    angles = np.rad2deg(angles)
    labels = []
    for label, angle in zip(ax.get_xticklabels(), angles):
        x,y = label.get_position()
        lab = ax.text(x,y, label.get_text(), transform=label.get_transform(),
                    ha=label.get_ha(), va=label.get_va(),size=20)
        lab.set_rotation(angle)
        
        labels.append(lab)
    ax.set_xticklabels([])



    plt.grid(True)
    plt.tight_layout()
    
    # Shrink current axis by 20%
    # box = ax.get_position()
    # ax.set_position([box.x0, box.y0, box.width * 0.9, box.height])

    # Put a legend to the right of the current axis
    ax.legend(loc='upper right', bbox_to_anchor=(1.1,1))
    # plt.legend(bbox_to_anchor=(-0, 0))


names=["all_res.csv"]#["GradientBoosting_test.csv","LogisticRegression_test.csv","RandomForest_test.csv","SVM(rbf kernel)_test.csv","all_res.csv"]
path="native/"

files_do,files_normal = LoadData(names,path)
plt.style.use('ggplot')

metrics=["Accuracy","Precision","Recall","F1"] #,"AUC"

for name in names:
    if "Event" in files_do[name].columns:
        subjects = list(files_do[name]["Event"])
    else:
        subjects = list(files_do[name]["Model"])
    for metric in metrics:
        # print(name)
        do_metrix = list(files_do[name][metric])
        do_upper= [x+(x*0.2) for x in do_metrix]
        do_lower= [x-(x*0.2) for x in do_metrix]


        normal_metrix = list(files_normal[name][metric])
        normal_upper= [x+(x*0.1) for x in normal_metrix]
        normal_lower= [x-(x*0.1) for x in normal_metrix]

        uppers=[do_upper,normal_upper]
        lowers=[do_lower,normal_lower]

        datas=[do_metrix,normal_metrix]
        
        con_interval=[True,False]

        # print(np.shape(datas))
        labels=["DO","Normal"]
        # print(datas)
    
        fills=[False,False]

        fig,(ax) = plt.subplots(1,1,subplot_kw={'projection': 'polar'})
        fig.set_figwidth(8)
        fig.set_figheight(6)

        RadarPlot(datas,subjects,uppers,lowers,con_interval,fills,labels,ax)
        # RadarPlot(alice,bob,subjects,ax1)
        plt.savefig("native/result_normal/"+name+"_"+metric+"_fig.png")
        plt.close()
        # plt.show()