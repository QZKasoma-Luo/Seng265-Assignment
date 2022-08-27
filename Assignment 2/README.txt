Author: QingZe Luo
Email: luo.kasoma@gmail.com

INTRODUCTION
------------

This program (f1_statistics.py) is designed for X86 based Ubuntu(VERSION="18.04.6 LTS (Bionic Beaver)", HOME_URL="https://www.ubuntu.com/") based on python3 with import library of Pandas, tkinter and matplotlib.pyplot etc.
please check your python3 verison is at 3.6.9 or later before running f1_statistics.py to avoid any possible error, you can use "python3" in the bash shell to get the version of the python3 you are currently using in your
system.

The function of the f1_statistics.py is mainly to generate output file(.csv) and statistical bar chart (.jepg) through the question number and file (.csv) from the user command, please check if
you have the corrsepond file and file extension before running f1_statistics.py .

There are 5 type questions:

	Q1: Who are the top 20 drivers with most wins in F1 history?
	Q2: What are the top 10 countries with most race-winners in F1 history?
	Q3: What are the top 10 constructors with most wins in F1?
	Q4: What are the top 20 countries with most hosted F1 races?
	Q5: Who are the top 5 drivers with most wins in F1 history who started a race not being on pole position?

Reminder:The Program (f1_statistics.py) will delete the previous output file and generate a new output file and a graph with the same name (output.csv) and information under the path of
where the program (f1_statistics.py) locates if you try to run the program (f1_statistics.py) multiple times with the same question with or without the same data in the file.


INSTALLATION
------------
 
There are some chances that your system are missing some of the critical libraries that the program (f1_statistics.py) needs, the following information will guide you through the installation.

 * For Pandas(Home URL:https://pandas.pydata.org/docs/reference/io.html): You can use the command " sudo apt-get install python3-pandas" anywhere in your bash shell and select yes as "Y" to install Pandas.

 * For tkinter(Home URL:https://docs.python.org/3/library/tkinter.html): You can use the command " sudo apt-get install python3-tk" anywhere in your bash shell and select yes as "Y" to install tkinter.

 * For matplotlib.pyplot(Home URL:https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.html): You can use the command " sudo apt-get install python3-matplotlib." anywhere in your bash shell and select yes as "Y" to 
   install matplotlib.

If the system still prints out the error massage as "module missing", then please check the modules you have download are for "python3" not "python"


Sample Command line
-------------------
A sample command line to call the program would be:  "./f1_statistics.py --question=1 --files=drivers.csv,results.csv"