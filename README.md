# Car Rental Management Application

## Overview

This is an application that was made as part of the CS253 course offerening in the 2023-24-II Semester. The entire application has been coded in **C++**. For the database management **C++ file handling** has been used. All commands are to be given throught the terminal.

## Structure

The system has been tested to be working properly on **Windows**, and has some functions that might not work properly on **UNIX** based systems as the terminal commands are seperate in both.

There are *4* databases that have been used instead of the *3* given in the Problem Statement, as no information for the manager data was given and since Customer and Employees had different databases it made sense to give even the Manager a different one.

The *customers.csv* and *employees.csv* have the following entries 
`Username,Name,Password,Pending Fine,Customer/Employee_record,Number of Rented Cars`

The *employees.csv* has the following entries
`Username,Name,Password`

The *all_cars.csv* has the following entries.
`UID,Model,Condition,Rented/Not Rented(1/0),Return Date(if rented==1),Rented by(user_id)(if rented==1),Cost per day`


## Usage

To start the application compile the C++ code with `G++ compiler` with `version >= 11.0`. Run the `.exe` file.

You will be provided with prompts at each step, on starting the application, the **main menu** will appear and, you will have options to register as a new customer, login in to the app, and exit the application.

On selecting log-in you will have options to log-in as a *customer,employee or manager*, and you can go back to the *main menu*. The login screen will keep cycling back until successful login is done. 

After successful login the specified user will be prompted to their respective page with all their required functionalities. After this all the functionalities are prompt based.  

## Assumptions

The higher the **customer/employee record** the more cars they can rent at one time. This will be henceforth be reffered to as *score*.
I have assumed that the score is updated once the car is returned. The score is *decreased* by **10 per day** the car is late, and the score is *increased* by **10** if the car is returned on time. I have used a **bin system** to decide the number of cars a user is eligible to rent. The bins are different for customers and employees

**Customer** 
| Lower Bound | Upper Bound | No. of Cars |
| :---------- | :---------: | ----:       |
| 0           |   100       | 1           |
|  100        |   150       | 2           |
| 150         |  200        | 3           |
| 200         |  250        | 4           |
|250          |infinity     | 5           |

**Employees**
| Lower Bound | Upper Bound | No. of Cars |
| :---------- | :---------: | ----:       |
| 0           |   50        | 1           |
|  50         |   100       | 2           |
| 100         |150          | 3           |
| 150         |  200        | 4           |
| 200         |  250        | 5           |
| 250         | 300         | 6           |
| 300         |infinity     | 7           |

The Emploees also get a discount on renting cars of 15% as mentioned in the problem statement.

The **Condition of Cars** can be categorized in *three* categories i.e. `Good , Moderate , Bad`
