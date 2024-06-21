# Project Overview

The project has several algorithms implemented in SGX, x86, and SE that return boolean values. These algorithms are used to test side channels in these architectures.


## Environment Setup

The following softwares are required 
1. **Python3** 
    numpy, matplotlib, pandas, seaborn, sk_learn
   ```bash
   pip3 install numpy matplotlib pandas seaborn scikit-learn
   ```
2) **SGX sdk**
   Link: https://github.com/intel/linux-sgx
    

## Directories

- **App:** This directory contains non-enclave SGX code and profiling for each decision program.
- **Enclave:** This directory contains algorithm implementations for SGX.
- **Native:** This directory contains algorithm implementations for native x86.
- **Functional-library:** This directory contains algorithm implementations for SE.
- **Helper:** This directory contains Python scripts for ML training and inference, data generation, and general-purpose helper code.
- **Shared:** This directory contains common header and source files for SGX, SE, and x86 architectures.


## How to Build/Execute the Codes

**Note**
Before executing any of the code, make sure to generate the input data. To do that:

1. Go to the Helper directory, where you will find a Python script named datagen.py.
2. In the main routine, please call the function that generates the input for the desired application.
    
### For SGX:

1. Install the Intel(R) SGX SDK and SGX driver for Linux OS.
2. Build the project using the prepared Makefile:
  - **Hardware Mode, Debug build:**
    ```bash
    make SGX_MODE=HW SGX_DEBUG=1
    ```
  - **Hardware Mode, Pre-release build:**
    ```bash
    make SGX_MODE=HW SGX_PRERELEASE=1
    ``` 
  - **Hardware Mode, Release build:**
    ```bash
    make SGX_MODE=HW
    ```
3. Execute the binary :
There are "run_xx.sh" shell files in the application's root directory. Execute the shell file that corresponds to the target application.
Example:
```bash
    sudo ./run_maxrun.sh # Executes the maxrun SGX application using its data.
```

### For SE:

1. Go to the functional-library directory.
2. Go to one of the desired application's directories.
  Example:
    ```bash
    cd distinctness
    ```
4. Build the binary using the make command; an executable binary with the name 'main' will be generated.
  Use:
    ```bash
    make
    ```
6. Finally, to execute the binary and collect the events, use:
   ```bash
      sudo ./run_native.sh
   ``` 

### For Native:

1. Go to the Native directory.
2. Go to one of the desired application directories.
  Example:
   ```bash
   cd distinctness
   ```
4. Build the binary using the make command.
  Use:
   ```bash
   make
   ```
5. Finally, to execute the binary and collect the events, use:
   ```bash 
   sudo ./run_native.sh
   ``` 

