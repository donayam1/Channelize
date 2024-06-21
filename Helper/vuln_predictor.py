import pickle 
import os 
from datareader import ReadAllData,ReadAllData_fromCsv,namesList
import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd 
from sklearn.metrics import accuracy_score,f1_score,precision_score,recall_score
from eda import PairPlot
from sklearn.inspection import permutation_importance

# models={ 
#       do:{
#                "model_type":
#                {
#                    "event1":"ML_Classifier",
#                    "event2":"ML_Classifier"
#                }
#           },
#           normal:{
#                     "model_type":
#                      {
#                        "event1":"ML_Classifier",
#                        "event2":"ML_Classifier"
#                      }
#           }            
#         }
def LoadModels(base_dir="native",modes=["do","normal"],result_dir_name_start = "result_",models_dir="models"):
    models = {}
    for mode in modes:
        if not (mode in models):
                models[mode]={}
        dir=os.path.join(base_dir,result_dir_name_start+mode,models_dir)
        files = os.listdir(dir)  
        for file in files:
            # print(file)
            parts = file.split("_")
            # print(parts)
            model_type = parts[0]
            event=parts[1]
            
            name=os.path.join(dir,file)
            loaded_model = pickle.load(open(name, 'rb'))
            if not (model_type in models[mode]):
                models[mode][model_type]={}

            models[mode][model_type][event]=loaded_model
        # print(models[mode])
    return models


def PlotPermutatoinFeatureImportance(model,model_name,x_test,y_test,attrs,outdir):
    #plot permutation_importance 
    result = permutation_importance(model, x_test, y_test, n_repeats=100, random_state=0, n_jobs=8)
    fig, ax = plt.subplots()
    sorted_idx = result.importances_mean.argsort()
    labels=  np.array(namesList)[attrs] #[2:18]
    sorted_labels = labels[sorted_idx]
    ax.boxplot(
        result.importances[sorted_idx].T, vert=False, labels=sorted_labels
    )
    ax.set_title("Permutation Importance of each PMU event")
    ax.set_ylabel("PMU event")
    ax.grid(True)
    fig.tight_layout()
    fileanme = os.path.join(outdir,model_name+"_fature_importance.png")
    plt.savefig(fileanme)

def ComputeFutureImportance():

    apps =["frequency"] #["add","distinctness","contains","bubblesort","frequency","validParenthesis","setintersection8"] 
    modes=["normal"]
    archs=["native"]
    data = ReadAllData_fromCsv(apps,modes,archs) #ReadAllData(apps,modes,archs) #ReadAllData_fromCsv(apps,modes,archs) #

    cols = np.array(namesList)
    cols = np.append(cols,"labels")  
    df = pd.DataFrame(data,columns=cols)
    
    
    data = df.to_numpy()
    attrs = list(range(2,18))
    # print(attrs)
    features = data[:,attrs]
    label=data[:,18:19]



    models = LoadModels(modes=["normal"])
    normal_models = models["normal"]

   
   
    for model_name in normal_models:
        model = normal_models[model_name]["combined"]
        PlotPermutatoinFeatureImportance(model,model_name+"_test",features,label,attrs,"./") 

def Test_Combined(mode="normal"):
    # apps=["distinctness","add","contains","bubblesort","frequency","setintersection8","validParenthesis"] #setintersection8
    if mode=="normal":
        apps=["frequency"]#["maxrun"] 
        modes=["normal"]
        archs=["sgx"] #["native"]
    else:
        apps=["distinctness"] #["add","distinctness","contains","bubblesort","frequency","validParenthesis","setintersection8"] 
        modes=["do"]
        archs=["sgx"]

    data = ReadAllData_fromCsv(apps,modes,archs) #ReadAllData(apps,modes,archs) #ReadAllData_fromCsv(apps,modes,archs) #

    cols = np.array(namesList)
    cols = np.append(cols,"labels")  
    df = pd.DataFrame(data,columns=cols)
    
    

    # #TODO re run maxrun function and remove this if part of the code     
    # if mode == "normal":
    #     df.loc[df["labels"]==1.0,"labels"] = 2
    #     df.loc[df["labels"]==0.0,"labels"] = 1
    #     df.loc[df["labels"]==2.0,"labels"] = 0

    # df = df.loc[df["labels"]==1]
    data = df.to_numpy()
    attrs = list(range(2,18))
    features = data[:,attrs]
    label=data[:,18:19]



    models = LoadModels(modes=["normal"])
    normal_models = models["normal"]

    res = []
    class_res= pd.DataFrame(columns=["Model","Accuracy","Precision","Recall","F1"])
    for model_name in normal_models:
        print(model_name)
        model = normal_models[model_name]["combined"]
        labels_new = model.predict(features)
        
        
        labels_new_prob = model.predict_proba(features) #(normal_models[model]["combined"].predict_proba(features)[:,1] >= 0.8).astype(bool)   
        # (clf.predict_proba(X_test)[:,1] >= 0.3).astype(bool)
        np.savetxt(model_name+"_res.txt",labels_new_prob) 


        accuracy = accuracy_score(label,labels_new)        
        f1 = f1_score(y_true=label,y_pred=labels_new)        
        precision = precision_score(y_true=label,y_pred=labels_new)        
        recall = recall_score(y_true=label,y_pred=labels_new) 
        df = pd.DataFrame([[model_name,round(accuracy,2),round(precision,2),round(recall,2),round(f1,2)]],columns=["Model","Accuracy","Precision","Recall","F1"])
        class_res = pd.concat([class_res,df])


        
        unique, counts = np.unique(labels_new, return_counts=True)  
        unique = [int(x) for x in unique]
        

        count1 = 0
        if 1 in unique:
            count1 = counts[1]

        accu = count1/sum(counts)
        # print(accu)

        c_dict = dict(zip(unique, counts))
        print(c_dict)
        res.append([model_name,accu])



        plt.scatter(features[:,1],features[:,15],c=labels_new)
        plt.xlabel(namesList[3])
        plt.ylabel(namesList[17])
        plt.savefig(model_name+"_res.png")  

       

  
    #TODO uncomment this to save the classification result 
    dir = "sgx/result_"+mode+"/" #native
    path = os.path.join(dir,"all_res.csv")
    class_res.to_csv(path,index=False)

    print(res)
    vuln=[]
    for sub_res in res:
        if mode == "normal":
            if sub_res[1] <= 0.2 or sub_res[1] >= 0.8:
                vuln.append(0)
            else:
                vuln.append(1)
        else:             
            if sub_res[1] >= 0.4 and sub_res[1] <= 0.6:
                vuln.append(0)
            else:
                vuln.append(1)

    print(vuln)


def Test_Per_Channel(mode="normal"):
    # apps=["distinctness","add","contains","bubblesort","frequency","setintersection8","validParenthesis"] #setintersection8
    if mode=="normal":
        apps=["maxrun"] #["add","distinctness"]#
        modes=["normal"]
        archs=["native"]
    else:
        apps=["add","distinctness","contains","bubblesort","frequency","validParenthesis","setintersection8"] 
        modes=["do"]
        archs=["native"]

    data = ReadAllData_fromCsv(apps,modes,archs) #ReadAllData(apps,modes,archs) #ReadAllData_fromCsv(apps,modes,archs) #

    cols = np.array(namesList)
    cols = np.append(cols,"labels")  
    df = pd.DataFrame(data,columns=cols)
    
    

    #TODO re run maxrun function and remove this if part of the code     
    # if mode == "normal":
    #     df.loc[df["labels"]==1.0,"labels"] = 2
    #     df.loc[df["labels"]==0.0,"labels"] = 1
    #     df.loc[df["labels"]==2.0,"labels"] = 0

    # df = df.loc[df["labels"]==1]
    data = df.to_numpy()
    features = data[:,2:18]
    label=data[:,18:19]



    models = LoadModels(modes=["normal"])
    normal_models = models["normal"]

    results={}
    
    for model in normal_models:
        print(model)        
        res = []
        class_res= pd.DataFrame(columns=["Model","Accuracy","Precision","Recall","F1"])
        for index in range(2,len(namesList)-1):
            event_name = namesList[index]
            event_name = "-".join([event_name,namesList[-1]])
            attributes=[index,18]
            features = data[:,attributes]
            label=data[:,18:19]
            labels_new = normal_models[model][event_name].predict(features)
            
            
            # labels_new_prob = normal_models[model][event_name].predict_proba(features) #(normal_models[model]["combined"].predict_proba(features)[:,1] >= 0.8).astype(bool)   
            # # (clf.predict_proba(X_test)[:,1] >= 0.3).astype(bool)
            # np.savetxt(model+"_res.txt",labels_new_prob) 


            accuracy = accuracy_score(label,labels_new)        
            f1 = f1_score(y_true=label,y_pred=labels_new)        
            precision = precision_score(y_true=label,y_pred=labels_new)        
            recall = recall_score(y_true=label,y_pred=labels_new) 
            df = pd.DataFrame([[event_name,round(accuracy,2),round(precision,2),round(recall,2),round(f1,2)]],columns=["Model","Accuracy","Precision","Recall","F1"])
            class_res = pd.concat([class_res,df])


            
            unique, counts = np.unique(labels_new, return_counts=True)  
            unique = [int(x) for x in unique]
            

            count1 = 0
            if 1 in unique:
                count1 = counts[1]

            accu = count1/sum(counts)
            # print(accu)

            c_dict = dict(zip(unique, counts))
            print(c_dict)
            res.append([event_name,accu])

        results[model] = res
         #TODO uncomment this to save the classification result 
        dir = "native/result_"+mode+"/"
        path = os.path.join(dir,model+"_test.csv")
        class_res.to_csv(path,index=False)

            # plt.scatter(features[:,1],features[:,15],c=labels_new)
            # plt.xlabel(namesList[3])
            # plt.ylabel(namesList[17])
            # plt.savefig(model+"_res.png")    

    
       

       

        print(results)


if __name__ == "__main__":
    modes = ["do"]
    for mode in modes:
        Test_Combined(mode=mode)
    # ComputeFutureImportance()
        # Test_Per_Channel(mode=mode)

