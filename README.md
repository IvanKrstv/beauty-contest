# Beauty Contest

![2531_2-scaled](https://github.com/user-attachments/assets/a96f726f-bde4-4582-9008-e5b4ba3b3fd0)

This is a console program that handles an information system for a beauty contest, written in C++. It consists of a main menu, which operates with integer values, that are typed in the relevant place, in order to choose a function from it (don't worry, invalid inputs are handled properly 😉). Down below are all of the functions summarized in a few words. The whole documentation can be found [here](DocumentationBG.docx) but unfortunatelly, it is written in Bulgarian, as the whole project is a task from my university in Bulgaria.

## ⚙ Options

### Loading information from text file
At first, after opening the program, it automatically loads information from a text file if it exists. Otherwise, a message is displayed that the file has not been found.

### Add new participants
When the user types 1 in the terminal, they are able to add as many participants as they would like in the contest manually. This happens after filling in infromation about each of them in the relevant spaces.

### Display all participants
When the user types 2 in the terminal, they are able to see a table with all of the registred participants and the information about them.

### Search participants
When the user types 3 in the terminal, it opens a new submenu with 2 options:
1. Find out who the youngest participant is.
2. Search a participant by name

### Sort the participants in ascending order
When the user types 4 in the terminal,

### Manage file
When the user types 5 in the terminal, it opens a new submenu, which can manage binary files, with 2 options:
1. Saves all the data to a binary file
2. Inputs the data from a binary file

### Other functions
When the user types 6 in the terminal, it opens a new submenu with 3 additional functions for searching and sorting:
1. Displays all participants sorted by age 
2. Search by age
3. Search by gender 

### Split into categories
When the user types 7 in the terminal, 

### Winners from each category
When the user types 8 in the terminal,


When the user types 9 in the terminal, it exits the program and all the data is stored into a .txt file so it could be possible to load it again after reopening the program.
