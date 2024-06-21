import os 

source_app="maxrun" #"maxrun"#"setintersection" #"validParenthesis"
source_arc="sgx"
source_mode="do_without_prefetch"
source_index=""
root_dir_name="final_result_prefetch"
dest_index="1"

source_res_dir= "../Data/result/"+source_app+"/"+source_arc+"/total/"+source_mode+""+source_index
des_res_dir= "../Data/result/"+source_app+"/"+source_arc+"/total/"+source_mode+""+dest_index

source_clust_dir ="../"+root_dir_name+"/result/clustering/"+source_app+"/"+source_arc+"/"+source_mode+""+source_index
dest_clust_dir ="../"+root_dir_name+"/result/clustering/"+source_app+"/"+source_arc+"/"+source_mode+""+dest_index


source_csv_dir ="../"+root_dir_name+"/all_csv/"+source_arc+"_"+source_app+"_"+source_mode+""+source_index+".csv"
dest_csv_dir ="../"+root_dir_name+"/all_csv/"+source_arc+"_"+source_app+"_"+source_mode+""+dest_index+".csv"

source_plot_dir ="../"+root_dir_name+"/result/plot/"+source_app+"/"+source_arc+"/total/plot/"+source_mode+""+source_index
dest_plot_dir ="../"+root_dir_name+"/result/plot/"+source_app+"/"+source_arc+"/total/plot/"+source_mode+""+dest_index

try:
    os.rename(source_res_dir, des_res_dir)
except OSError as e:
    print(f"Error: {e}")

try:    
    os.rename(source_clust_dir, dest_clust_dir)
except OSError as e:
    print(f"Error: {e}")

try:
    os.rename(source_csv_dir, dest_csv_dir)    
except OSError as e:
    print(f"Error: {e}")

try:
    os.rename(source_plot_dir, dest_plot_dir)
except OSError as e:
    print(f"Error: {e}")
