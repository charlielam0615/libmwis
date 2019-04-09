# A Maximum Weighted Independent Set Greedy Solver for Python
This programm is modified from [jcoupey's mwis code](https://github.com/jcoupey/mwis). I basically just used 
[pybind11](https://github.com/pybind/pybind11) to write an interface to Python.

## Prerequisites
'''
conda install pybind11
'''

## Compile
```
cd src/ && make && cd ..
```

## Run test
'''
cd lib && python test.py
'''