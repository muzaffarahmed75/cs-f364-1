# Brief description

### Overview
This project implements two independent algorithms to find the strongly-connected components in directed graphs.  
One is the classical algorithm using Depth First Search (a.k.a Kosaraju's Algorithm). The other is a divide-and-conquer algorithm from the paper "A Divide-and-conquer Algorithm for Identifying Strongly Connected Components" by Don Coppersmith, Lisa Fleischer, Bruce Hendrickson and Ali Pınar.  

### Input and running
Build and run by using the command ```./run.sh <input_files>```  
The input must be ```.txt``` files and must represent the graph by an edge-list.  
Sample input has been included in ```data/```.
Execute ```./run.sh data/*``` to run the program on all sample files.  
Any metadata may be present in lines prepended by a # in the input files.  
All output will be generated in ```output/```.
