# DBStats

## Purpose 

Provide a tool to quickly draw plots from the result of an SQL query. 

## Installation 

### Dependencies

- qt4
- root6

#### Qt 

Debian packages: 

    qt-sdk # dev package... 
    libqt4-sql-psql # for postgresql support

#### ROOT 

Installation instructions are detailed on [the ROOT website](https://root.cern.ch/root/html534/guides/users-guide/InstallandBuild.html), together with the [requirements](https://root.cern.ch/build-prerequisites).

Remember to use enable the qt option at the configuration step: **./configure --enable-qt**


### Compile dbstats 

    qmake -qt=4 dbstats.pro # generate the Makefile
    make # generates the executable called 'dbstats'

Then you can lauch the program : 

    ./dbstats


### Usage 

1. Connect to your database via the menu File > Database connection
2. Write your query in the upper left text area
3. Click on "Run Query" button below the edit area
4. The lower left panel should now display an overview of the returned data
5. Go to the upper right panel to configure the plot and click on "Draw"

