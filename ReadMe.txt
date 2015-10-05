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

/************* TODO
1: Design of structured line:

	We made a seperate struct PlayLine to store the line number, the character 
    name and text as its data member. A seperate struct makes the program 
    structure clearer and easier to extend.

2: Design of Play class and print method:

    In order to support line insertion and printing in order, the play class
    can be designed in a few different fashion, including:

    1) Use a priority queue (heap) to store inserted lines, push each line
       out upon printing. Since fetching sorted list from a heap requires
       modifying it, it requires non-const print method, or a mutable member 
       queue. What's more, all of the lines has to be pushed and popped
       for each time print is called.

    2) Use a list or vector to store lines, sort them upon printing. 
       This method optimizes for insertion time.  If we sort them in a new list,
       we pay extra memory and time overhead but get a const print method. 
       If we sort them in situ, we lost const-ness of print but saved time on 
       both insertion and printing for the second time.

    3) Use a heap or list for insertion, and another list to store sorted lines 
       upon printing. This avoids overhead of unnecessary sorting when printing
       for multiple times with nothing new inserted. But the management of 
       these two storage requires carefulness, especially when we have to make
       them both mutable if we want a const print. It's better to delegate them
       to a seperate manager class.

    4) Use a switch, that allows insertion only when it's turned on, and sort
       the lines upon turning it off. It is basically the most time-and-memory
       efficient design, avoiding all of the shortcomings of the previous designs.
       But it requires extra attention to be paid by outside code, and the 
       assert(sorted) being done runtime is really dangerous when the project
       starts to grow.

    Nevertheless, we chose method 2, used a vector to store inserted lines,
    and sort them on print, leaving a non-const print. It's not that ideal,
    but works good for a small program as a quick start. I'll probably switch
    to method 3 with manager class if the project starts to grow.

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

3: Syntax of the play file:
    
    Basically we adopted the following syntax rules:

    1) Every line is read with the spaces on both end of the line trimmed.

    2) A line starting with '[' (after trimming) is considered comment and not
       processed at all.

    3) The first non-blank line following a blank line or the start of the file, 
       if ending with '.', is considered a character name (eliminating that '.'). 
       Only one character is allowed at a time, and no space is allowed in 
       the name.

    4) The remaining non-blank lines are effective lines, belonging to the 
       last character met. The line number is counted for effective lines only.

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
