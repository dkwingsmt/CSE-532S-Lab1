CSE 532 Fall 2015 Lab 1

Team Member: 
    Tong Mu (mutong32@gmail.com)
    Jinxuan Zhao (jzhao32@wustl.edu)
    Zeneil Ambekar (ambekar@wustl.edu)

== Usage ==
=== Unpack ===

Unpack the zip file with 7zip.

The extracted folder contains a copy of this ReadMe.txt, and another folder,
where a Visual Studio 2013 solution for this assignment resides. 

> lab1\
> |- ReadMe.txt
> |- lab1\
>    |- lab1\
>    |- lab1_extra\
>    |- common\
>    |- configs\
>    |- lab1.sln
>    |- ...

The solution folder consists of the following folders,

- lab1, for the VS project lab1.
- lab1_extra, for the VS project lab1_extra.
- common, headers and utility functions common across projects.  
- configs, sample configuration files for testing. 

=== Build ===

Open lab1.sln in the solution folder with VS 2013, and build the solution.
This solution consists of 2 VS projects, lab1 and lab1_extra,
and should generate two executable files in Debug or Release folder in the 
solution folder, depends on which profile is choosed.

=== Run ===

Both executables requires command line arguments to run properly; they will 
prompt usage information if no arguments are provided.

Samples of outside files for testing are placed inside the config folder,
including:
- hamlet_act_ii_scene_2.txt. The original play file provided.
- hamlet-34.txt. Another play file we excerpted by our own.
- empty-play.txt. Totally empty. But still a valid play!
- empty-but-one.txt. Empty, except for a lonely character, still with no lines.

The usage for lab1.exe is

    lab1.exe <configuration_file_path>

It reads and parses the configuration file, finds corresponding per-character 
files in the SAME DIRECTORY as the config file, and prints the play into
the standard output.

The usage for lab1_extra.exe is

    lab1_extra.exe <play_file_path> <configuration_file_path>

It reads and parses the play file, and generates a config file accordingly.
It will also generate per-character play files in the SAME DIRECTORY as the 
config file.

=== Example ===

After building the solution, open cmd.exe and cd to the directory for the 
executales.

Generate config files

    lab1_extra.exe ..\configs\hamlet-34.txt ..\configs\hamlet-34_config.txt Hamlet Act II

And print it

    lab1_532.exe ..\configs\hamlet-34_config.txt


== Description ==
=== Overview ===

1: Design of the Play class
  
  We kept the design of structured lines (PlayLine) from the last lab, which
  packages the line number, the character, and the text of a line. It also 
  implements a less than operator.

  The majority of the tasks assigned to Play in the last lab, was assigned 
  to Player instead this time, including reading and ordering. The Play class
  actually performs as a platform for playing, and opens an interface recite()
  for players. 
  
  recite() receives a structured line from players which contains every 
  information needed. As it will be called from multiple players in seperate
  threads, a condition variable as well as a lock are used to keep the order.
  When a line completes its recitation, it increases the line number, releases 
  the lock, and notify all currently waiting players. Only the one holding 
  the right line number will be waken and get the lock.

3: Design of the Player class

  The player object was designed to work as an active object. The instantiation 
  of the thread that performs the reading of the corresponding play fragment file
  is encapsulated in the class. The class also has the following design features:

    1) Encapsulation via class interface
       The only way to interact with a Player object after instantiation is to
       active it and wait for it to stop. The thread internally interacts with
       a play object to append the lines read from its file (via the private
       read() member function) and then contends to print lines to the console
       (via the private act() member function)

    2) Fault Tolerance
       The read() member function ignores any lines that are badly formatted,
       and skip reading them instead of throwing an exception or printing an
       error message.

   In the last lab we mentioned four different sort of methods to keep lines in 
   order for each player. Now that an explicit enter() method is always required, 
   we can safely store the lines out of order upon insertion and sort them just 
   before acting.

3: Syntax of the play file:
    
    The same as the last lab, but allow out-of-order lines for per-character 
    files.

4: The Wrapper Facades we used:

	We used a guard object TGuard, which accepts a procedure for constructor
    and calls it in the destructor. By contructing it with a lambda function
    that joins all the threads, we ensure that threads are joined whatever 
    happens that terminates the block, before the play prints.

5: Design of config generator: 

    The same rule as 3 is used to parse the play file. It reads the character 
    list from the play and the lines for each character, and writes the results
    into correct files.
    
    We tested edges cases such as an empty play or character file (while it's 
    legal). 
    
    We didn't test cases such as illegal file (whether it's play, config or 
    character file).


== Insights, Observations and Questions encountered == 
	
- We can use std::ref so that the thread will update the data structure that's 
  passed in by reference.

- We find that the Wrapper Facade Pattern is a really smart idea that it makes 
  the code more maintainable and portable. 

- It can be observed that the active object pattern is quite useful, as the code
  can be better structured and made easy to read by tying the explicitly tying
  the object lifecycle with that of the thread running its code

- In this lab, we use different threads to read a same file with different targets, 
  but reading only is relatively safer and therefore we are expecting there will 
  be more challenging tasks that involves both reading and writing with threads 
  coming up in the following labs.
***************/
	
== Acknowledgement ==

This project refers to no code from previous assignment by students outside of
this team.
