import numpy as np 
import random 
import os 


'''
    f- function returns false
    t- function returns true 
'''
def genIsDistinct():
    out_dir = "../Data/input/distinctness/do_se"
    if not os.path.exists(out_dir):    
        os.makedirs(out_dir)
        
    for x in range(0,500):
        size=3000
        rand = random.sample(range(0,size),size)


        name = "../Data/input/distinctness/do_se/t_rand"+str(x)+".txt"
        np.savetxt(name,rand,fmt="%7d")

        dup = x*3
        start = size-dup 
        print("dup=",dup," Start=",start)
        for i in range(start,size):            
            rand[i] = rand[0]

        name = "../Data/input/distinctness/do_se/f_rand"+str(x)+".txt"
        np.savetxt(name,rand,fmt="%7d")  

    # for x in range(1,501):
    #     rand = [(y%((x*100))) for y in random.sample(range(0,60000),60000)]   
    #     name = "../Data/input/distinctness/f_rand"+str(x)+".txt"
    #     np.savetxt(name,rand,fmt="%7d")    

'''
    input generator for distinctness2 program 
'''
# def genPerDuplicateRandomNumers():

#     for x in range(0,500):
#         rand = random.sample(range(1,1000000),50000)

#         rand[49999] = rand[49998]
#         name = "../Data/input/distinctness2/f_rand"+str(x)+".txt"
#         np.savetxt(name,rand,fmt="%7d")


# genPerDuplicateRandomNumers()
#True and false lable has been changed to indicate weather the side channel exposes a potential side channel or not 
'''
    f- function returns false
    t- function returns true 
'''
def genParenthesis(): 

    for x in range(1,500): 
        print(x)
        size = 30_000_000
        rand = random.sample(range(0,size),size) #30000000
        parenthesis = np.array(['(' if x%2==0 else ')' for x in rand])

        name = "../Data/input/validParenthesis/do/t_rand"+str(x)+".txt"
        np.savetxt(name,parenthesis,fmt="%s")


        n = size - (x*30000) #1_000_000
        parenthesis[-n:] = '('
        name = "../Data/input/validParenthesis/do/f_rand"+str(x)+".txt"
        np.savetxt(name,parenthesis,fmt="%s")

# genParenthesis()
'''
    isRandom: generate the duplicates randomly or not 
    dupCount: the number of duplicates 
    size: the maximum data size or maximum duplicate value 
    
    f- function returns false
    t- function returns true 
'''
def selectDupIndexes(isRandom,dupCount,size):
    if isRandom:
        indexes = random.sample(range(0,size),dupCount)
    else:
        indexes = range(0,dupCount)
    
    return indexes

'''
    f- function returns false
    t- function returns true 
'''
def generateFreqency(withRandomDuplicates=False):
    out_dir  =  "../Data/input/frequency/do"    
    if not os.path.exists(out_dir):    
        os.makedirs(out_dir)
        
    for x in range(0,500):
        # x = 0
        size =  60000 #30,000,000
        rand = random.sample(range(0,size),size)
        # parenthesis = np.array(['(' if x%2==0 else ')' for x in rand])

        name = os.path.join(out_dir, "f_0_5_rand"+str(x)+".txt")
        np.savetxt(name,rand,fmt="%07d")


        dupCount = (x+1)*100 #*10000
        indexes = selectDupIndexes(withRandomDuplicates,dupCount,size)

        dupCount=len(indexes)+1 # add one because the number that is being duplicated(12 in this case)  is already 
                                # generated in the above random number generation step and if we come across it while replacing the duplicated numbers 
                                # remove it from the count 
        for i in indexes:
            if rand[i] == 12:
                dupCount -= 1
            else:
                rand[i] = 12
 
        name =os.path.join(out_dir, "t_12_"+str(dupCount)+"_rand"+str(x)+".txt")
        np.savetxt(name,rand,fmt="%07d")

        
'''
    f- function returns false
    t- function returns true 
'''
def generateAdd(mode="normal",arch="native"):
        out_dir = "../Data/input/add/do"
        if not os.path.exists(out_dir):    
            os.makedirs(out_dir)
    # for x in range(0,500):
        # x = 0
        if mode == "do":
            size = 10000
        else:
            size = 30_000_000

        rand = range(1,size+1)
        # parenthesis = np.array(['(' if x%2==0 else ')' for x in rand])
        name = out_dir+"/t_"+str(0)+"_"+str(size)+"_rand"+str(0)+".txt"
        np.savetxt(name,rand,fmt="%07d")



        name = out_dir +"/f_"+str(1)+"_"+str(1)+"_rand"+str(0)+".txt"
        np.savetxt(name,rand,fmt="%07d")       
'''
    f- function returns false
    t- function returns true 
'''
def GenerateSetIntersection():   
    out_dir = "../Data/input/setintersection/native/a"
    if not os.path.exists(out_dir):    
        os.makedirs(out_dir)
    out_dir = "../Data/input/setintersection/native/b"
    if not os.path.exists(out_dir):    
        os.makedirs(out_dir)

    for x in range(0,500):
        print(x)
        size = 30000
        randA = np.array(random.sample(range(0,size),size))
        # parenthesis = np.array(['(' if x%2==0 else ')' for x in rand])
        name = "../Data/input/setintersection/native/a/f_rand"+str(x)+".txt"
        np.savetxt(name,randA,fmt="%07d")
        
        rand =np.array(random.sample(range(size+1,(size*2) + 1),size) )
        # parenthesis = np.array(['(' if x%2==0 else ')' for x in rand])
        name = "../Data/input/setintersection/native/b/f_rand"+str(x)+".txt"
        np.savetxt(name,rand,fmt="%07d")

        n = size - (x*59)
        # for i in range(n,size):
        rand[-n:] = randA[0]       
        name = "../Data/input/setintersection/native/b/t_rand"+str(x)+".txt"
        np.savetxt(name,rand,fmt="%07d") 

'''
    f- function returns false
    t- function returns true 
'''
def GenerateBubbleSort():
    rand = range(0,60000)
    name = "../Data/input/bubblesort/sec/f_rand"+str(0)+".txt" #no branching, not valnerable  
    np.savetxt(name,rand,fmt="%07d")


    for x in range(0,500):
        n = 5; #x*100
        begin = np.array(range(0,n,1))
        end =   np.array(range(59999,n-1,-1))
        rand =  np.concatenate([begin,end])
        print(np.shape(rand))
        name = "../Data/input/bubblesort/nosec/t_rand"+str(x)+".txt" #different level of branching 
        np.savetxt(name,rand,fmt="%07d")

def GenrateContains():
    out_dir = "../Data/input/contains/do_se"
    if not os.path.exists(out_dir):    
        os.makedirs(out_dir)
    rand = range(0,20_000_000)   
    num = 21_000_000   
    digit= num
    for x in range(0,500):
        digit = num + x
        name = "../Data/input/contains/do/f_"+str(digit)+"_rand0.txt" #no branching, not valnerable  
        np.savetxt(name,rand,fmt="%08d")

        name = "../Data/input/contains/do/t_"+str(x)+"_rand0.txt" #no branching, not valnerable  
        np.savetxt(name,rand,fmt="%08d")

'''
f is function returns false 
t is function returns true 
'''
def GenerateMaxRun():
    out_dir = "../Data/input/maxrun/do"
    if not os.path.exists(out_dir):    
        os.makedirs(out_dir)
    for x in range(1,500):
        print(x)
        size =  20_000_000
        rand = np.array(random.sample(range(0,size),size))
        # parenthesis = np.array(['(' if x%2==0 else ')' for x in rand])

        name = out_dir + "/f_"+str(10)+"_rand"+str(x)+".txt"
        np.savetxt(name,rand,fmt="%07d")


        dupCount = size - ((x+1)*3000)        
        rand[-dupCount:] = rand[0] 
        name = out_dir+"/t_"+str(dupCount)+"_rand"+str(x)+".txt"
        np.savetxt(name,rand,fmt="%07d")

if __name__ == "__main__":
    # GenrateContains()
    # GenerateBubbleSort()
    # GenerateSetIntersection()
    # genIsDistinct()
    # generateFreqency(True)

    GenerateMaxRun()
    
    # mode = "do"
    # generateAdd(mode="do")
    # genParenthesis()