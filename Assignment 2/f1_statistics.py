#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jun 04 14:45:33 2022
@author: STUDENT_NAME

This is a file processor that allows to generate relevant statistics from F1 data.
"""
import sys
import pandas as pd
import matplotlib.pyplot as plt
import tkinter as TK 


def format_message(message: str) -> str:
    """Formats a message to be printed out to the standard output.

    Parameters
    ----------
    message : str, required
        The message to be printed out to the standard output.

    Returns
    -------
    str
        The formatted message.
    """
    return '[' + sys.argv[0] + ']: ' + message

def ouput_file(final_result: pd.DataFrame, top_numbers: int) -> None:

    """Formats the final sets and write it in to the standard output.csv file that generated.

    Parameters
    ----------
    final_set : pd.DataFrame, required
        The final set contains the infromation to be saved in to the output.csv file

    top_numbers: int, required
        The top_numbers contains the how many top information user want to saved in to the output.csv file

    Returns
    -------
    None
    
    """
    final_result.head(top_numbers).to_csv('output.csv',mode='w',  index=False, chunksize = top_numbers)


def alph_check_and_resort(reversed_final_set: set) -> None:

    """Resort the order of the set if and only if the winning time are equal for two racers beside each other.

    Parameters
    ----------
    reversed_final_set : set, required
        reversed_final_set contains the number ordered racer list 

    Returns
    -------
    None
    
    """

    for check_point in range(len(reversed_final_set)-1):

            if(reversed_final_set[check_point][1] == reversed_final_set[check_point + 1][1]):
                if(reversed_final_set[check_point][0] > reversed_final_set[check_point + 1][0]):
                    reversed_final_set[check_point] , reversed_final_set[check_point + 1] = reversed_final_set[check_point + 1] , reversed_final_set[check_point]


    

def output_graph(graph_file_name:str, subject:list, statistic:list, title: str, x:str, y:str) -> None:
    """Generate a output graph in jepg format.

    Parameters
    ----------
    subject : list, required
        contains the subjects name

    statistic: list, required
        contains the statistic data
    
    title: str, required
        contains the title for the graph
    
    x: str, required
        The lable on the x-axis of the graph
    
    y: str, required
        The labe on the y-axix of the graph

    name: str, required
        The graph file name

    Returns
    -------
    None
    
    """

    bar_chart = plt.figure(figsize = (16, 16))
    # creating the bar plot
    plt.bar(subject, statistic, color ='green',width = 0.3)
    plt.title(title)
    plt.xlabel(x)
    plt.xticks(rotation='vertical')
    plt.ylabel(y)  
    plt.tight_layout()
    plt.savefig(graph_file_name)

def Q1_Process(diver_file: str, result_file: str) -> None:
    """Process the information for Question 1

    Parameters
    ----------
    diver_file: str, required
        a csv file's name, and the file contains diver information
    
    result_file: str, required
        a csv file's name, and the file contains the race result

    Returns
    -------
    None
    
    """
    
    dataframe_driver_file = pd.read_csv(diver_file)
    dataframe_result_file = pd.read_csv(result_file)

    position_1 = dataframe_result_file.loc[dataframe_result_file['positionOrder'] == 1]
    winner_driver_id = position_1['driverId'].values

    name_count_dict = {}
    for all_driver_id in winner_driver_id:
        name = dataframe_driver_file.loc[dataframe_driver_file['driverId'] == all_driver_id, 'forename'].values[0] + ' ' + dataframe_driver_file.loc[dataframe_driver_file['driverId'] == all_driver_id, 'surname'].values[0]
    
        if name not in name_count_dict:
            name_count_dict[name] = 1 
        else:
            name_count_dict[name] = name_count_dict[name] + 1

    racer_result_set = list(name_count_dict.items())
    racer_result_set.sort(key = lambda x:x[1],reverse = True)
    alph_check_and_resort(racer_result_set)
    ouput_file(pd.DataFrame(racer_result_set, columns= ["subject", "statistic"]), 20 )
    subject = []
    statistic = []
    for item in racer_result_set[:20]:
        subject.append(item[0])
        statistic.append(item[1])
    output_graph("output_graph_q1.jpeg", subject, statistic, "Graph for Q1", "Name", "Winning time")
    
    

def Q2_Process(diver_file: str, result_file: str) -> None:
    """Process the information for Question 2

    Parameters
    ----------
    diver_file: str, required
        a csv file's name, and the file contains diver information
    
    result_file: str, required
        a csv file's name, and the file contains the race result

    Returns
    -------
    None
    
    """

    dataframe_driver_file = pd.read_csv(diver_file)
    dataframe_result_file = pd.read_csv(result_file)
    position_1 = dataframe_result_file.loc[dataframe_result_file['positionOrder'] == 1]
    winner_driver_id = position_1['driverId'].values
    country_set = {}
    for all_driver_id in winner_driver_id:
        countries = dataframe_driver_file.loc[dataframe_driver_file['driverId'] == all_driver_id, 'nationality'].values[0]

        if countries not in country_set:
            country_set[countries] = 1
        else:
            country_set[countries] = country_set[countries] + 1   
    country_result_set = list(country_set.items())
    country_result_set.sort(key = lambda x:x[1],reverse = True)
    alph_check_and_resort(country_result_set)
    ouput_file(country_result_set, 10)
    subject = []
    statistic = []
    for item in country_result_set[:10]:
        subject.append(item[0])
        statistic.append(item[1])
    output_graph("output_graph_q2.jpeg", subject, statistic, "Graph for Q2", "Country Name", "Winning time")



def Q3_Process(constuctor_file: str, result_file: str) -> None:
    """Process the information for Question 3

    Parameters
    ----------
   constuctor: str, required
        a csv file's name, and the file contains diver information
    
    result_file: str, required
        a csv file's name, and the file contains the race result

    Returns
    -------
    None
    
    """

    dataframe_constuctor_file = pd.read_csv(constuctor_file)
    dataframe_result_file = pd.read_csv(result_file)
    position_1 = dataframe_result_file.loc[dataframe_result_file['positionOrder'] == 1]
    winner_constructor_id = position_1['constructorId'].values

    constuctor_file_set = {}

    for all__constructor_id in winner_constructor_id:
        constuctor = dataframe_constuctor_file.loc[dataframe_constuctor_file['constructorId'] == all__constructor_id, 'name'].values[0]

        if constuctor not in constuctor_file_set:
            constuctor_file_set[constuctor] = 1
        else:
            constuctor_file_set[constuctor] = constuctor_file_set[constuctor] + 1
    
    constuctor_result_set = list(constuctor_file_set.items())
    constuctor_result_set.sort(key = lambda x:x[1],reverse = True)
    alph_check_and_resort(constuctor_result_set)
    ouput_file(constuctor_result_set, 10)
  
    subject = []
    statistic = []
    for item in constuctor_result_set[:10]:
        subject.append(item[0])
        statistic.append(item[1])
    output_graph("output_graph_q3.jpeg", subject, statistic, "Graph for Q3", "Constuctor Name", "Winning time")

def Q4_Process(circuits_file: str, races_file: str) -> None:
    """Process the information for Question 4

    Parameters
    ----------
    circuits_file: str, required
        a csv file's name, and the file contains circuits information
    
    races_file: str, required
        a csv file's name, and the file contains the race information

    Returns
    -------
    None
    
    """

    dataframe_circuits_file = pd.read_csv(circuits_file)
    dataframe_race_file = pd.read_csv(races_file)
    
    circuit_id_raced = dataframe_race_file['circuitId'].values
    circuits_id_host_times = {}
    for id_counter in circuit_id_raced:

        if id_counter not in circuits_id_host_times:
            circuits_id_host_times[id_counter] = 1
        else:
            circuits_id_host_times[id_counter] += 1


    country_host_set = {}
    for country_id_count in circuits_id_host_times:
        country_name = dataframe_circuits_file.loc[dataframe_circuits_file['circuitId'] == country_id_count, 'country'].values[0]
        if country_name not in country_host_set:
            country_host_set[country_name] = circuits_id_host_times[country_id_count]
        else:
            country_host_set[country_name] = country_host_set[country_name] + circuits_id_host_times[country_id_count]

    country_host_time_result_set = list(country_host_set.items())
    country_host_time_result_set.sort(key = lambda x:x[1],reverse = True)
    alph_check_and_resort(country_host_time_result_set)
    ouput_file(country_host_time_result_set, 20)
  
    subject = []
    statistic = []
    for item in country_host_time_result_set[:20]:
        subject.append(item[0])
        statistic.append(item[1])
    output_graph("output_graph_q4.jpeg", subject, statistic, "Graph for Q4", "Country Name", "Host time")

   

def Q5_Process(diver_file: str, result_file: str) -> None:
    """Process the information for Question 5

    Parameters
    ----------
    diver_file: str, required
        a csv file's name, and the file contains diver information
    
    result_file: str, required
        a csv file's name, and the file contains the race result

    Returns
    -------
    None
    
    """

    dataframe_driver_file = pd.read_csv(diver_file)
    dataframe_result_file = pd.read_csv(result_file)

    position_1 = dataframe_result_file.loc[(dataframe_result_file['positionOrder'] == 1) & (dataframe_result_file['grid'] != 1)] 
    winner_driver_id = position_1['driverId'].values

    name_count_dict = {}
    for all_driver_id in winner_driver_id:
        name = dataframe_driver_file.loc[dataframe_driver_file['driverId'] == all_driver_id, 'forename'].values[0] + ' ' + dataframe_driver_file.loc[dataframe_driver_file['driverId'] == all_driver_id, 'surname'].values[0]
    
        if name not in name_count_dict:
            name_count_dict[name] = 1 
        else:
            name_count_dict[name] = name_count_dict[name] + 1

    racer_result_set = list(name_count_dict.items())
    racer_result_set.sort(key = lambda x:x[1],reverse = True)   

    ouput_file(racer_result_set, 5) 
    subject = []
    statistic = []
    for item in racer_result_set[:5]:
        subject.append(item[0])
        statistic.append(item[1])
    output_graph("output_graph_q5.jpeg", subject, statistic, "Graph for Q5", "Racer Name", "Winning time")

    pass

def main():
    """The main entry of the program.
    """
    # sample call to function
    #print(format_message('hello'))
    # TODO: Your code here.

    if(len(sys.argv) < 3):

        print("Please Check your command line, the arguments are not enough")

    else:

        question_number = int(sys.argv[1][-1])
        Passed_file = sys.argv[2].replace("--files=", "").split(",")
        #print(question_number)
        #print(Passed_file)

        for question_count in range(1,6):

            #print(count)
            if question_number == question_count:

                #print(f"This is question {question_count}")

                if(question_count == 1):
                    Q1_Process(Passed_file[0], Passed_file[1])
                    
                elif(question_count == 2):
                    Q2_Process(Passed_file[0], Passed_file[1])
                    
                elif(question_count == 3):
                    Q3_Process(Passed_file[0], Passed_file[1])
                    
                elif(question_count == 4):
                    Q4_Process(Passed_file[0], Passed_file[1])
                    
                elif(question_count == 5):
                    Q5_Process(Passed_file[0], Passed_file[1])
                    
                else:
                    print("Please Check your command line, the question arguments you passed in are not exists")
                
        
        




if __name__ == '__main__':
    main()
