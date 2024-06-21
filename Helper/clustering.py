# Import KMeans
from sklearn.cluster import KMeans 
from sklearn.preprocessing import StandardScaler, MinMaxScaler 
from sklearn.pipeline import make_pipeline 
from sklearn.linear_model import LogisticRegression 
from sklearn.svm import LinearSVC, SVC
from sklearn.utils import resample 
import pickle

import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

from sklearn import svm, datasets
from sklearn.inspection import DecisionBoundaryDisplay
from sklearn.inspection import permutation_importance

from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import CategoricalNB
from sklearn.ensemble import RandomForestRegressor
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.utils import resample 

from sklearn.metrics import accuracy_score,f1_score,precision_score,recall_score,roc_curve,auc,RocCurveDisplay,roc_auc_score
from sklearn.metrics import confusion_matrix,ConfusionMatrixDisplay,precision_recall_curve

from sklearn.decomposition import PCA
from sklearn.model_selection import KFold 
import matplotlib.pyplot as plt 
from datareader import ReadData_fromCsv, namesList,NamesToIndexMap #,ReadAllData_fromCsv
from perf_event_names import LABEL
import numpy as np 
import pandas as pd 
import os 
# from eda import PairPlot


CONTEXT_SWITCHES        ="context-switches"
CPU_MIGRATIONS          ="cpu-migrations"

CACHE_MISSES            ="cache-misses"
CACHE_REFERENCES        ="cache-references"
CPU_CYCLES              ="cpu-cycles"
INSTRUCTIONS            ="instructions"
BRANCH_MISSES           ="branch-misses"
BRANCHES                ="branches"
PAGE_FAULTS             ="page-faults"
L1_DCACHE_LOAD_MISSES   ="L1-dcache-load-misses"
L1_DCACHE_LOADS         ="L1-dcache-loads"
L1_DCACHE_STORES        ="L1-dcache-stores"
L1_ICACHE_LOAD_MISSES   ="L1-icache-load-misses"


LLC_LOAD_MISSES         ="LLC-load-misses"
LLC_LOADS               ="LLC-loads"
LLC_STORE_MISSES        ="LLC-store-misses"
LLC_STORES              ="LLC-stores"
SECONDS                 ="execution-time"





# These are applications where the blue curve is to the left of the red curve on the pairplot 
blue_left=[]

# These are applications where the blue curve is to the right of the red curve on the pairplot 
blue_right=[]



# def PlotPermutatoinFeatureImportance(model,model_name,x_test,y_test,attrs,outdir):
#     #plot permutation_importance 
#     result = permutation_importance(model, x_test, y_test, n_repeats=100, random_state=0, n_jobs=8)
#     fig, ax = plt.subplots()
#     sorted_idx = result.importances_mean.argsort()
#     labels=  np.array(namesList)[attrs] #[2:18]
#     sorted_labels = labels[sorted_idx]
#     ax.boxplot(
#         result.importances[sorted_idx].T, vert=False, labels=sorted_labels
#     )
#     ax.set_title("Permutation Importance of each PMU event")
#     ax.set_ylabel("PMU event")
#     ax.grid(True)
#     fig.tight_layout()
#     fileanme = os.path.join(outdir,model_name+"_fature_importance.png")
#     plt.savefig(fileanme)

def Classify_KFOLD(data,attributes=None,plot_cm_roc=False,ploat_pfi=True,outdir="plots"):
    models={
        # "KMeans":KMeans(2),
        "LogisticRegression":LogisticRegression(),
        "SVM(rbf kernel)":SVC(gamma=0.01,kernel="rbf",probability=True),
        "RandomForest":RandomForestClassifier(n_estimators = 1000, random_state = 23,bootstrap=True),
        "GradientBoosting":GradientBoostingClassifier(n_estimators=100, random_state=23)
    }
    # attrs = []
    if attributes == None:
        # features  = data[:,[2,3,5,6,7,8,9,10,11,12,13,14,15,16,17]] #data[:,2:18]#leave out  CONTEXT_SWITCHES        ="context-switches"
                                                                                 #CPU_MIGRATIONS          ="cpu-migrations"
        
        model_name = "combined_model.sav"
    else:
        # features  = data[:,attributes]
        # attrs = attributes
        model_name ="-".join(np.array(namesList)[attributes]) + "_model.sav"

    # features = data[:,attrs]
    # labels = np.squeeze(data[:,18:19])
    kfold = KFold(n_splits=10,shuffle=True,random_state=12)

    res= pd.DataFrame(columns=["Model","Accuracy","Precision","Recall","F1","AUC"])
    # print(data.head)
    for foldnumber, (train_index,test_index) in enumerate(kfold.split(data)):
        print("Fold Number=",foldnumber)
        train = data.iloc[train_index]
        test = data.iloc[test_index]
        # print("train=",np.shape(train),"test=", np.shape(test))


        y_train = train[LABEL] #np.squeeze(train[:,18:19]) 
        y_test =  test[LABEL] #np.squeeze(test[:,18:19]) 
        x_train = train.drop(LABEL,axis=1) #[:,attrs]
        x_test =  test.drop(LABEL,axis=1) #test[:,attrs]
          

        

        # x_train,x_test,  y_train,y_test = train_test_split(features,labels,train_size=0.9,test_size=0.1)
        # scaler = StandardScaler()

        # model = GradientBoostingClassifier(n_estimators=100, random_state=23)
       
        # if plot_cm_roc == True:
        #     result_table = pd.DataFrame(columns=['classifiers', 'fpr','tpr','auc']) #used to plot cm and roc
        

        models_dir  =  os.path.join(outdir,"models")    
        if not os.path.exists(models_dir):    
            os.makedirs(models_dir)

        for key in models:
            model = models[key]
            pipeline = make_pipeline(model)    
            pipeline.fit(x_train,y_train)
                    
            filename = key+"_"+model_name
            final_model_path = os.path.join(models_dir,filename)
            pickle.dump(model, open(final_model_path, 'wb'))

            labels_new = pipeline.predict(x_test)
        
            if attributes == None and ploat_pfi:
                #plot permutation_importance 
                result = permutation_importance(model, x_test, y_test, n_repeats=100, random_state=0, n_jobs=8)
                fig, ax = plt.subplots()
                sorted_idx = result.importances_mean.argsort()
                # attrs = data.columns 
                labels= data.columns #np.array(namesList)[attrs] #[2:18]
                sorted_labels = labels[sorted_idx]
                ax.boxplot(
                    result.importances[sorted_idx].T, vert=False, labels=sorted_labels
                )
                ax.set_title("Permutation Importance of each PMU event")
                ax.set_ylabel("PMU event")
                ax.set_xlabel("Decrease in accuracy score")
                ax.grid(True)
                fig.tight_layout()
                fileanme = os.path.join(outdir,key+"_feature_importance.png")
                plt.savefig(fileanme)
                plt.close()
                #end of plot permutation_importance 

            accuracy = accuracy_score(y_test,labels_new)        
            f1 = f1_score(y_true=y_test,y_pred=labels_new)        
            precision = precision_score(y_true=y_test,y_pred=labels_new)        
            recall = recall_score(y_true=y_test,y_pred=labels_new)    
                # prec0, recall0, _ = precision_recall_curve(y_test, labels_new, pos_label=1)

            yproba = model.predict_proba(x_test)[::,1]
            fpr, tpr, _ = roc_curve(y_test,  yproba)
            aucval = roc_auc_score(y_test, yproba)
            
            # if plot_cm_roc == True:
            #     df0 = pd.DataFrame([[key,fpr, tpr, aucval]],columns=['classifiers', 'fpr','tpr','auc'])
            #     result_table = pd.concat([result_table,df0])  

                        


            # Check if row with 'Name' exists
            # print(res['Model'].values, "and kye= ",key)
            if key in res['Model'].values:
                # print("Updating existing")
                # Update existing row
                res.loc[res['Model'] == key, 'Accuracy'] +=   round(accuracy,2)  # Update 'Age' column for the row with the specified name
                res.loc[res['Model'] == key, 'Precision'] +=   round(precision,2)  # Update 'Age' column for the row with the specified name
                res.loc[res['Model'] == key, 'Recall'] +=   round(recall,2)  # Update 'Age' column for the row with the specified name
                res.loc[res['Model'] == key, 'F1'] +=  round(f1,2)  # Update 'Age' column for the row with the specified name
                res.loc[res['Model'] == key, 'AUC'] +=   round(aucval,2)  # Update 'Age' column for the row with the specified name
            else:
                # Add new row
                # new_row = {'Accuracy': accuracy, 'Precision': precision, 'Recall': recall,'F1':f1, "AUC":aucval}
                # res = res.append(new_row, ignore_index=True) 
                # print("adding new ");
                df = pd.DataFrame([[key,round(accuracy,2),round(precision,2),round(recall,2),round(f1,2),round(aucval,2)]],columns=["Model","Accuracy","Precision","Recall","F1","AUC"])
                res = pd.concat([res,df])

            # Thus in binary classification, the count of true negatives is C_{0,0}, false negatives is C_{1,0}, true positives is C_{1,1} and false positives is C_{0,1}.
            # cm = confusion_matrix(y_true=y_test, y_pred=labels_new, labels=model.classes_,)#model.classes_   
            # df = pd.DataFrame([[key,round(accuracy,2),round(precision,2),round(recall,2),round(f1,2),round(aucval,2)]],columns=["Model","Accuracy","Precision","Recall","F1","AUC"])
            # res = pd.concat([res,df])
            

        # if plot_cm_roc == True:
        #     result_table.set_index('classifiers', inplace=True)


        
        if plot_cm_roc:     
            fig,sub = plt.subplots(2,2,sharex='all', sharey='all')
            # fig.tight_layout(pad=2.0)
            plt.subplots_adjust(wspace=.5,hspace=.5)
            for ax,key in zip(sub.flatten(),models):                                      
                model = models[key]

                ax.set_title(key)
                ConfusionMatrixDisplay.from_estimator(
                            model, x_test, y_test,labels=model.classes_, normalize="all", display_labels=["False","True",],ax=ax)
                # disp = ConfusionMatrixDisplay(confusion_matrix=cm,
                #                             display_labels=model.classes_)
                # disp.plot()
                # plt.subplots(2, 2, sharex='all', sharey='all')

            name =outdir+"/"+str(foldnumber)+"_CM.png"
            plt.savefig(name)
            plt.close()


        #     fig = plt.figure(figsize=(8,6))

        #     for i in result_table.index:
        #         plt.plot(result_table.loc[i]['fpr'], 
        #                 result_table.loc[i]['tpr'], 
        #                 label="{}, AUC={:.3f}".format(i, result_table.loc[i]['auc']))
                
        #     plt.plot([0,1], [0,1], color='orange', linestyle='--',label="Chance Level (AUC = 0.5)")

        #     plt.xticks(np.arange(0.0, 1.1, step=0.1))
        #     plt.xlabel("Flase Positive Rate", fontsize=15)

        #     plt.yticks(np.arange(0.0, 1.1, step=0.1))
        #     plt.ylabel("True Positive Rate", fontsize=15)

        #     plt.title('ROC Curve Analysis', fontweight='bold', fontsize=15)
        #     plt.legend(prop={'size':13}, loc='lower right')

        #     plt.savefig(outdir+"/combined_ROC.png")


        print(res)
    return res 


def Classify(data,attributes=None,plot_cm_roc=False,ploat_pfi=True,outdir="plots"):
    models={
        # "KMeans":KMeans(2),
        "LogisticRegression":LogisticRegression(),
        "SVM(rbf kernel)":SVC(gamma=0.01,kernel="rbf",probability=True),
        "RandomForest":RandomForestClassifier(n_estimators = 1000, random_state = 23,bootstrap=True),
        "GradientBoosting":GradientBoostingClassifier(n_estimators=100, random_state=23)
    }
    attrs = []
    if attributes == None:
        # features  = data[:,[2,3,5,6,7,8,9,10,11,12,13,14,15,16,17]] #data[:,2:18]#leave out  CONTEXT_SWITCHES        ="context-switches"
                                                                                 #CPU_MIGRATIONS          ="cpu-migrations"
        attrs =list(range(2,18))
        model_name = "combined_model.sav"
    else:
        # features  = data[:,attributes]
        attrs = attributes
        model_name ="-".join(np.array(namesList)[attributes]) + "_model.sav"

    features = data[:,attrs]
    labels = np.squeeze(data[:,18:19])
    x_train,x_test,  y_train,y_test = train_test_split(features,labels,train_size=0.9,test_size=0.1)
    # scaler = StandardScaler()

    # model = GradientBoostingClassifier(n_estimators=100, random_state=23)
    res= pd.DataFrame(columns=["Model","Accuracy","Precision","Recall","F1","AUC"])

    if plot_cm_roc == True:
        result_table = pd.DataFrame(columns=['classifiers', 'fpr','tpr','auc']) #used to plot cm and roc
    

    models_dir  =  os.path.join(outdir,"models")    
    if not os.path.exists(models_dir):    
        os.makedirs(models_dir)

    for key in models:
        
        model = models[key]
        pipeline = make_pipeline(model)    
        pipeline.fit(x_train,y_train)
                
        filename = key+"_"+model_name
        final_model_path = os.path.join(models_dir,filename)
        pickle.dump(model, open(final_model_path, 'wb'))

        labels_new = pipeline.predict(x_test)
       
        if attributes == None and ploat_pfi:
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
            ax.set_xlabel("Decrease in accuracy score")
            ax.grid(True)
            fig.tight_layout()
            fileanme = os.path.join(outdir,key+"_feature_importance.png")
            plt.savefig(fileanme)
            #end of plot permutation_importance 

        accuracy = accuracy_score(y_test,labels_new)        
        f1 = f1_score(y_true=y_test,y_pred=labels_new)        
        precision = precision_score(y_true=y_test,y_pred=labels_new)        
        recall = recall_score(y_true=y_test,y_pred=labels_new)    
            # prec0, recall0, _ = precision_recall_curve(y_test, labels_new, pos_label=1)

        yproba = model.predict_proba(x_test)[::,1]
        fpr, tpr, _ = roc_curve(y_test,  yproba)
        aucval = roc_auc_score(y_test, yproba)
        
        if plot_cm_roc == True:
            df0 = pd.DataFrame([[key,fpr, tpr, aucval]],columns=['classifiers', 'fpr','tpr','auc'])
            result_table = pd.concat([result_table,df0])  

                    

        # Thus in binary classification, the count of true negatives is C_{0,0}, false negatives is C_{1,0}, true positives is C_{1,1} and false positives is C_{0,1}.
        # cm = confusion_matrix(y_true=y_test, y_pred=labels_new, labels=model.classes_,)#model.classes_   
        df = pd.DataFrame([[key,round(accuracy,2),round(precision,2),round(recall,2),round(f1,2),round(aucval,2)]],columns=["Model","Accuracy","Precision","Recall","F1","AUC"])
        res = pd.concat([res,df])
        # res[key] = [accuracy,precision,recall,f1,aucval]

    if plot_cm_roc == True:
        result_table.set_index('classifiers', inplace=True)


    
    if plot_cm_roc:     
        fig,sub = plt.subplots(2,2,sharex='all', sharey='all')
        # fig.tight_layout(pad=2.0)
        plt.subplots_adjust(wspace=.5,hspace=.5)
        for ax,key in zip(sub.flatten(),models):                                      
            model = models[key]

            ax.set_title(key)
            ConfusionMatrixDisplay.from_estimator(
                         model, x_test, y_test,labels=model.classes_, normalize="all", display_labels=["0","1",],ax=ax)
            # disp = ConfusionMatrixDisplay(confusion_matrix=cm,
            #                             display_labels=model.classes_)
            # disp.plot()
            # plt.subplots(2, 2, sharex='all', sharey='all')

        name =outdir+"/combined_CM.png"
        plt.savefig(name)
        plt.close()


        fig = plt.figure(figsize=(8,6))

        for i in result_table.index:
            plt.plot(result_table.loc[i]['fpr'], 
                    result_table.loc[i]['tpr'], 
                    label="{}, AUC={:.3f}".format(i, result_table.loc[i]['auc']))
            
        plt.plot([0,1], [0,1], color='orange', linestyle='--',label="Chance Level (AUC = 0.5)")

        plt.xticks(np.arange(0.0, 1.1, step=0.1))
        plt.xlabel("Flase Positive Rate", fontsize=15)

        plt.yticks(np.arange(0.0, 1.1, step=0.1))
        plt.ylabel("True Positive Rate", fontsize=15)

        plt.title('ROC Curve Analysis', fontweight='bold', fontsize=15)
        plt.legend(prop={'size':13}, loc='lower right')

        plt.savefig(outdir+"/combined_ROC.png")

    return res 

def Classify2(data,attr,filename="all.png"):
    # data = pd.DataFrame(data,columns=namesList)

    h = 0.02  # step size in the mesh
    models={
        # "KMeans":KMeans(2),
        "LogisticRegression":LogisticRegression(),
        "SVM":SVC(gamma=0.01,kernel="rbf"),
        "RandomForest":RandomForestClassifier(n_estimators = 1000, random_state = 23,bootstrap=True),
        "GradientBoosting":GradientBoostingClassifier(n_estimators=100, random_state=23)
    }
   

    fig, axes = plt.subplots(
        nrows=len(attr), ncols=len(models) + 1, figsize=(21, 9))

    cm_piyg = plt.cm.PiYG
    cm_bright = ListedColormap(["#ff0000", "#0000ff"])

    for ds_cnt,attributes in enumerate(attr):
        X = data[:,attributes]
        y = np.squeeze(data[:,18:19])

        x_train,x_test,  y_train,y_test = train_test_split(X,y,train_size=0.9,test_size=0.1)

        # create the grid for background colors
        x_min, x_max = X[:,0].min() - 0.5, X[:,0].max() + 0.5
        y_min, y_max = X[:,1].min() - 0.5, X[:,1].max() + 0.5
        xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))

        # plot the dataset first
        # ds_cnt = 0
        ax = axes[ds_cnt, 0]
        if ds_cnt == 0:
            ax.set_title("Input data")
        if ds_cnt == (len(attr)-1):
            ax.set(xlabel=namesList[attributes[0]])    

        ax.set(ylabel=namesList[attributes[1]])

        # plot the training points
        ax.scatter(x_train[:,0], x_train[:,1], c=y_train, cmap=cm_bright, edgecolors="k")
        # and testing points
        ax.scatter(
            x_test[:, 0], x_test[:, 1], c=y_test, cmap=cm_bright, alpha=0.6, edgecolors="k"
        )
        ax.set_xlim(xx.min(), xx.max())
        ax.set_ylim(yy.min(), yy.max())

        if not(ds_cnt == (len(attr)-1)):
            ax.set_xticks(())
        # ax.set_yticks(())
    

        res={}
        for est_idx,key in enumerate(models):
            ax = axes[ds_cnt, est_idx + 1]

            model = models[key]
            pipeline = make_pipeline(model)    
            pipeline.fit(x_train,y_train)
            
            # labels_new = pipeline.predict(x_test)
            score = pipeline.score(x_test, y_test)

            # plot the decision boundary. For that, we will assign a color to each
            # point in the mesh [x_min, x_max]*[y_min, y_max].
            if hasattr(pipeline, "decision_function"):
                Z = pipeline.decision_function(np.column_stack([xx.ravel(), yy.ravel()]))
            else:
                Z = pipeline.predict_proba(np.column_stack([xx.ravel(), yy.ravel()]))[:, 1]

            # put the result into a color plot
            Z = Z.reshape(xx.shape)
            ax.contourf(xx, yy, Z, cmap=cm_piyg, alpha=0.8)

            # plot the training points
            ax.scatter(
                x_train[:, 0], x_train[:, 1], c=y_train, cmap=cm_bright, edgecolors="k"
            )
            # and testing points
            ax.scatter(
                x_test[:, 0],
                x_test[:, 1],
                c=y_test,
                cmap=cm_bright,
                edgecolors="k",
                alpha=0.6,
            )
            ax.set_xlim(xx.min(), xx.max())
            ax.set_ylim(yy.min(), yy.max())

            if not(ds_cnt == (len(attr)-1)):
                ax.set_xticks(())
                ax.set_yticks(())
            else:
                ax.set_yticks(())
                ax.set(xlabel=namesList[attributes[0]])


            if ds_cnt == 0:
                ax.set_title(key)

            ax.text(
                0.95,
                0.06,
                (f"{score:.2f}").lstrip("0"),
                size=15,
                bbox=dict(boxstyle="round", alpha=0.8, facecolor="white"),
                transform=ax.transAxes,
                horizontalalignment="right",
            )

        # name = namesList[attributes[1]]+".png"
    plt.savefig(filename)
        

def ClassifyPerAttribute(data,attrs,outdir="plots"):
    res={
        "LogisticRegression": pd.DataFrame(columns=["Event","Accuracy","Precision","Recall","F1","AUC"]) ,
        "SVM(rbf kernel)": pd.DataFrame(columns=["Event","Accuracy","Precision","Recall","F1","AUC"]) ,
        "RandomForest": pd.DataFrame(columns=["Event","Accuracy","Precision","Recall","F1","AUC"]) ,
        "GradientBoosting": pd.DataFrame(columns=["Event","Accuracy","Precision","Recall","F1","AUC"]) 
    }
   
    for ds_cnt,attributes in enumerate(attrs):
        c_res = Classify(data,attributes=attributes,plot_cm_roc=False,outdir=outdir) #pd.DataFrame([["LogisticRegression",0.7,0.9,0.5,0.6,0.7]], columns=["Model","Accuracy","Precision","Recall","F1","AUC"]) #
        event_name = namesList[attributes[0]]
        for index, row in c_res.iterrows():
            # print(row)
            model = row['Model']
            # print(c_res['Model'])
            # print("Model 0:",model[0])
            df = res[model]
            # print("df=",df)
            item = [event_name,row["Accuracy"],row["Precision"],row["Recall"],row["F1"],row["AUC"]]
            dfi = pd.DataFrame([item],columns=["Event","Accuracy","Precision","Recall","F1","AUC"])
            df = pd.concat([df,dfi])
            res[model] = df 

    for key in res:
        res[key].to_csv(outdir+"/"+key+".csv",index=False)        
    

           

          


def ClassifyBoundariesPlot(data,attributes,outdir="plots"):
    features  = data[:,attributes]#data[:,[names[CACHE_MISSES],names[CACHE_REFERENCES]]]#0:18]
    labels = np.squeeze(data[:,18:19])
   


    # Take the first two features. We could avoid this by using a two-dim dataset
    X = features
    y = labels
    x_train,x_test,  y_train,y_test = train_test_split(X,y,train_size=0.9,test_size=0.1)

    models=(
        # "KMeans":KMeans(2),
        LogisticRegression(),
        SVC(gamma=0.01,kernel="rbf"),
        RandomForestClassifier(n_estimators = 1000, random_state = 23,bootstrap=True),
        GradientBoostingClassifier(n_estimators=100, random_state=23)
     )

    models = (clf.fit(x_train, y_train) for clf in models)

    # title for the plots
    titles = (
        "LogisticRegression",
        "LinearSVC (rbf kernel)",
        "RandomForestClassifier",
        "GradientBoostingClassifier",
    )

    # Set-up 2x2 grid for plotting.
    fig, sub = plt.subplots(2, 2)
    plt.subplots_adjust(wspace=0.4, hspace=0.4)

    X0, X1 = X[:, 0], X[:, 1]

    for clf, title, ax in zip(models, titles, sub.flatten()):
        disp = DecisionBoundaryDisplay.from_estimator(
            clf,
            X,
            response_method="predict",
            cmap=plt.cm.coolwarm,
            alpha=0.8,
            ax=ax,
            xlabel=namesList[attributes[0]],
            ylabel=namesList[attributes[1]],
            )
        ax.scatter(X0, X1, c=y, cmap=plt.cm.coolwarm, s=20, edgecolors="k")
        ax.set_xticks(())
        ax.set_yticks(())
        ax.set_title(title)
        
        score =  clf.score(x_test, y_test)

        ax.text(
            0.95,
            0.06,
            (f"{score:.2f}").lstrip("0"),
            size=15,
            bbox=dict(boxstyle="round", alpha=0.8, facecolor="white"),
            transform=ax.transAxes,
            horizontalalignment="right",
            )

    plt.savefig(outdir+"/classification_boundary.png")

def PlotBoundaries(all,outdir="plots"):
    ClassifyBoundariesPlot(all,[NamesToIndexMap[SECONDS],NamesToIndexMap[BRANCH_MISSES]],outdir=outdir)




# def Train_multiple(apps,modes,archs,data_dir="final_result",out_root="final_result"):
#     # apps = [app] #["distinctness","add","distinctness_leaky","frequency","validParenthesis"] #["add","bubblesort","contains","distinctness","frequency","setintersection8","validParenthesis"] #["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2"]#["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2","contains"]        
#     # modes =[mode] #"do"
#     # archs = [arch] 

#     # for app in apps: 
#     #     for arch in archs:
#     #         for mode in modes:
#     # curr_mode= [mode]
#     all = ReadAllData_fromCsv(apps,modes,archs,data_root=data_dir)    
#     # all = ReadData_fromCsv(app,mode,arch,data_root=data_dir)    
#     if len(all) == 0:
#         return                    
#     outdir="../"+out_root+"/result/clustering/"+apps[0]
#     if not os.path.exists(outdir):    
#         os.makedirs(outdir)

#     res = Classify_KFOLD(all,plot_cm_roc=False,ploat_pfi=False,outdir=outdir)
#     filename = "combined_"+apps[0]+ "all_train_test_res.csv"
#     full_path = os.path.join(outdir,filename)
#     res.to_csv(full_path,index=False) #outdir+"/all_train_test_res_"+app+".csv"

def Train(app,mode,arch,data_dir="final_result",out_root="final_result"):
    # apps = [app] #["distinctness","add","distinctness_leaky","frequency","validParenthesis"] #["add","bubblesort","contains","distinctness","frequency","setintersection8","validParenthesis"] #["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2"]#["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2","contains"]        
    # modes =[mode] #"do"
    # archs = [arch] 

    # for app in apps: 
    #     for arch in archs:
    #         for mode in modes:
    # curr_mode= [mode]
    # all = ReadAllData_fromCsv(app,mode,arch,data_root=data_dir)    
    all = ReadData_fromCsv(app,mode,arch,data_root=data_dir)    
    if len(all) == 0:
        return                    
    outdir="../"+out_root+"/result/clustering/"+app+"/"+arch+"/"+mode
    if not os.path.exists(outdir):    
        os.makedirs(outdir)

    res = Classify_KFOLD(all,plot_cm_roc=True,ploat_pfi=True,outdir=outdir)
    filename = arch+"_"+mode+"_"+app+ "all_train_test_res.csv"
    full_path = os.path.join(outdir,filename)
    res.to_csv(full_path,index=False) #outdir+"/all_train_test_res_"+app+".csv"

def Train_onsome(app,mode,arch,drop_cols,data_dir="final_result",out_root="final_result"):
  
    all = ReadData_fromCsv(app,mode,arch,data_root=data_dir)    
    if len(all) == 0:
        return                    
    outdir="../"+out_root+"/result/clustering/"+app+"/"+arch+"/"+mode
    if not os.path.exists(outdir):    
        os.makedirs(outdir)

    for col in drop_cols:
        all = all.drop(columns=[col])
    print(all.head())
    res = Classify_KFOLD(all,plot_cm_roc=True,ploat_pfi=True,outdir=outdir)
    filename = arch+"_"+mode+"_"+app+ "all_train_test_res.csv"
    full_path = os.path.join(outdir,filename)
    res.to_csv(full_path,index=False) #outdir+"/all_train_test_res_"+app+".csv"
                     
           
            

if __name__ == '__main__':
    apps =  ["maxrun"] #["distinctness","add","distinctness_leaky","frequency","validParenthesis"] #["add","bubblesort","contains","distinctness","frequency","setintersection8","validParenthesis"] #["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2"]#["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2","contains"]        
    modes = ["do"] #"do"
    archs = ["sgx"]
    '''
    Events for contains app are 
    cols_drop=[BRANCH_MISSES,SECONDS,CPU_CYCLES,CACHE_MISSES,INSTRUCTIONS]  
    Result in the do folder 
    '''
    cols_drop = [BRANCH_MISSES,SECONDS,CPU_CYCLES,CACHE_MISSES,INSTRUCTIONS,BRANCHES,LLC_STORES]  
    # cols_drop=[SECONDS,L1_ICACHE_LOAD_MISSES,L1_DCACHE_STORES,L1_DCACHE_LOADS,L1_DCACHE_LOAD_MISSES,INSTRUCTIONS,CPU_CYCLES,BRANCH_MISSES,BRANCHES,CACHE_MISSES]    
    for app in apps: 
        for arch in archs:
            for mode in modes:
                #  Train(app,mode,arch,data_dir="final_result_new",out_root="final_result_new")
                 Train_onsome(app,mode,arch,drop_cols=cols_drop,data_dir="final_result_new",out_root="final_result_new")