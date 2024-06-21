from datareader import ToCSV,ToCVS_One,ToArrayNew
from clustering import Train
from eda import ScatterPlotData,PlotAll,Plot_one




if __name__ == '__main__':
    apps  = ["maxrun"] #["distinctness","add","distinctness_leaky","frequency","validParenthesis"] #["add","bubblesort","contains","distinctness","frequency","setintersection8","validParenthesis"] #["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2"]#["add","frequency","validParenthesis","distinctness","setintersection","bubblesort","setintersection2","contains"]        
    modes = ["do","do_without_prefetch"] #"do"
    archs = ["sgx"] 
    for app in apps: 
        for arch in archs:
            for mode in modes:
                    print("Analysing app={}, mode={}, arch={}".format(app, mode, arch))
                    print("Reading data to csv")
                    ToCVS_One(app=app,mode=mode,arch=arch,out_root="final_result_prefetch",fileParsor=ToArrayNew)
                    print("Training Ml models")
                    Train(app,mode,arch,data_dir="final_result_prefetch",out_root="final_result_prefetch")
                    
                    
                    print("Doing pair plot")
                    Plot_one(app=app,mode=mode,arch=arch,out_dir_root="final_result_prefetch",in_dir="final_result_prefetch")
