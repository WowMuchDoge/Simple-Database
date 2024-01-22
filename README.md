# Simple Database
Simple Database is a simple and lightweight database designed for simplicity and written in C++. Currently, table operations are only accessible through a Command Line Interface (CLI).

## Features
- **Table Operations:** You can perform basic table operations, for example ADD_ROW() and ADD_COLUMN().
- **File IO:** You can load and save file state with commands, this is currently done with text files.
- **Basic Error Handling:** Easy to read and understand errors when you make a mistake.
- **Types:** Currently four types are supported: Integer, Double, Boolean, and String

## Documentation
The following text will explain the operation of this database.

### Installation:
To use the database you must first install it, to do this you can either go to the releases page and grab the latest binary, or build the source code yourself by cloning the repository and running the command `make` inside of the repository's root directory. You can now put it in a `bin` directory or wherever you please, I don't care.

### Running:
If you run the binary file without any arguments, you will be defaulted into a REPL of sorts (not really) where you can execute commands repeatedly. If you run with an argument, it will execute all of the commands inside of that file and exit the program (currently the program loads and saves state through text files).

### Database Methods:
#### Currently, Simple Database supports six methods: 

- **ADD_COLUMN("&lt;name&gt;", &lt;type&gt;):** Specify the name of the column and the type, for example: `ADD_COLUMN(INT "int_col")`, this will add a column called "int_col", and that row will have integers. If a column has been created while rows have also been created, the value of the element in the newly created row will be of a garbage value, this is why it is important to create all of your columns before adding rows. Ensure that the type is one of these: `INT`, `DOUBLE`, `BOOL`, or `STRING`.
- **ADD_ROW(&lt;element&gt;...):** Specify elements in a new row, for example, if I had a column of type BOOL, and another column after that of type INT, a row method would look like `ADD_ROW(TRUE 328)`. Ensure that you do not provide too many arguments, as the error will state you are missing a parenthesis because that is what the program expects when enough arguments have been provided.
- **GET_ELEMENT("&lt;name&gt;" &lt;index&gt;):** Specify the name of the column and row index of the element you would like to get, for example: `GET_ELEMENT("int_col" 0)` would print the first element (remember indices start from zero) of column `"int_col"`. Ensure the column exists and the index is not out of range, otherwise it will throw an error.
- **EDIT_ROW(&lt;index&gt;, &lt;element&gt;...):** Specify the index of the row in which you would like to edit, and then (similar to the `ADD_ROW()` method), enter in the elements you would like to replace the row with. For example, `EDIT_ROW(0 FALSE 823)`. Ensure that the index is not out of range or it will through an error and that the number of arguments matches the number of columns, similar to the `ADD_ROW()` method.
- **REMOVE_COLUMN("&lt;name&gt;"):** Removes column at specified index. Make sure the name is the actual name of a column or it will error (hopefully).
- **EDIT_ELEMENT("&lt;name&gt;" &lt;index&gt;):** Edit an element at the specified column and row index, for example `EDIT_ELEMENT("int_col" 0 823)`. Ensure the column name exists and the row index is within range.
- **EDIT_COLNAME("&lt;name to change&gt;", "&lt;changed name&gt;")** Change the name of a column by specifying the name of the column to be changed and the changed name.
- **REMOVE_ROW(&lt;index&gt;):** Removes a row based on the specified index. Similar to the `REMOVE_COLUMN()` method, make sure the index does not exceed the number of rows you have minus one, or else it will throw an error.

That is all the database methods for directly interacting with the table, I know it is fairly limited but eventually, I might get back and add more for editing specific elements and such, but for now, this is really all you need to manipulate a table.

### Commands

While you are in the sort of pseudo-REPL, you can execute commands. Now this does not work if commands are within files, if you do put them there the program will just throw `Unkown Identifier` errors (again, hopefully). Currently, there are four commands you can execute:

- **help:** Running this just prints out a string that just prints a less detailed version of the docs you are currently reading.
- **exit:** Running this just quits out of the `while(true)` loop and exits out of the program.
- **save &lt;filename&gt;:** Running this will save the current state in a text file. The program does this by writing database methods to a text file that will if run, bring the program to the exact state it was in when you ran the command.
- **load &lt;filename&gt;:** Runs the commands within a text file, it will not delete the state you are currently in but add to it the commands that are within that text file.
- **clear rows:** Clears all the rows but keeps columns.
- **clear columns:** Clears all table state.

### Exit Codes
There are a few place in this code that use the `exit()` function to quit the program instead of throwing an exception. These do not throw an exception because they should be impossible to reach with the program's control flow, but if somehow you trick my dumb error handler it will exit with one of the codes below.

- **Exit Code 10:** Somewhere in the program you provided too few args and the program didn't catch it.
- **Exit Code 11:** Somewhere in the program you provided too many args and the program didn't catch it.
- **Exit Code 20:** Somehow a type was given that the program didn't understand.
- **Exit Code 21:** A method was provided that the program did not understand.
- **Exit Code 30:** An index was provided that was out of range of an array or vector (hopefully you get this instead of a segmentation fault).
- **Exit Code 40:** The specified file could not be opened.

While hopefully you will never get one of these errors, there are here if you need them. These should also be useful if you are editting the repository yourself.

This is all there is to the operation of this database, it is dead simple and quite honestly utter garbage. Any actual usage would require creating some sort of API and that is a problem for future me (or maybe future you if you want to fork this repo). Though even if you could use this, it would be stupid to because programs like SQLite exists which are faster and far more feature rich than this ever will be, so have fun screwing around but my word of warning: never actually use this.