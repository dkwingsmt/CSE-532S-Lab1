CSE 532 Fall 2015 Lab 1

Team Member: 
    Tong Mu (mutong32@gmail.com)
    Jinxuan Zhao (jzhao32@wustl.edu)
    Zeneil Ambekar (ambekar@wustl.edu)

== Usage ==
=== Unpack ===

Unpack the zip file with 7zip.

The extracted folder contains a copy of this ReadMe.txt, a sample_result folder
containing sample output from the executables, and the solution folder
for this assignment.

> lab1\
> |- ReadMe.txt
> |- sample_result\
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

    lab1_extra.exe [SCRAMBLE] <play_file_path> <configuration_file_path> <play name>

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

    While we used an explicit guard object TGuard to ensure that all threads are
    joined, since threads belongs to separate Players in this lab, we let 
    the destructor of a Player class to join its own thread.

    Also, lock_guards from STL library were adopted to synchroise between 
    threads.

5: Design of config generator: 
    
    This part is implemented in the same way as we did in lab0, except that

	(1)We fixed hard coding problem by using #define and enum.
		
	(2)When "SCRAMBLE" argument is given, we randomize the vector that holds
	   the lines of each script by using std::random_shuffle. 
	   
	(3)Used a scramble_flag to indicate if commend "SCRAMBLE" is given to 
	    determine whether or not to shift the index of the rest command lines.

6: Edges cases

    Edge cases we've tested include:

    1. An empty play or character file (while it's legal). 
    2. Incorrect spelling of specifier SCRAMBLE in lab1_extra.
    3. Incomplete lines in character files, including a non-empty character file .
       that consists only with incomplete lines.
    
    Edges cases we did not solve or test include:

    1. Noncontinuous line numbers in character files.
    2. Other illegal file formats, for play, config or character files.


== Insights, Observations and Questions encountered == 

- It can be observed that the active object pattern is quite useful, as the code
  can be better structured and made easy to read by tying the explicitly tying
  the object lifecycle with that of the thread running its code

- In this lab, we use different threads to read a same file with different targets, 
  but reading only is relatively safer and therefore we are expecting there will 
  be more challenging tasks that involves both reading and writing with threads 
  coming up in the following labs.

- Argument parsing has already become a little bloated with an optional SCRAMBLE.
  If the requirement keeps growing, we'll need to extract this part into a 
  separate function and develop a unified method of parsing in order to avoid
  duplicate code.

- We encountered some inconsistancy between Visual Studio 2013 and gcc. In gcc,
  moving constructor is one of the standard functions of a class, which means it
  can be implicitly inferred even with customised constructor defined, and it 
  can be set to =default, while it's not the case in VS. That caused a problem 
  that took us a lot of time because the compile kept complaining that a 
  deleted function was called but referring to a line in a standard library file,
  which was in fact caused by the moving constructor of Player that was deleted
  because of customized constructors.

	
== Acknowledgement ==

This project refers to no code from previous assignment by students outside of
this team.
