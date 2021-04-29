# Arrays vs Lists

Has to do with our discussion about Arrays vs Lists in one of our team meetings. Mike had written this very
nifty comparison in C++. I am saving the .cpp file in GitHub and challenging you to figure out how to compile
it and run on your system. He did this on Windows. I saved his output, so you know what to expect on your
system. The results may vary. 


# This is one of the most interesting topics in CS/Programming and this project aims to do the following:

- Make sure everyone is familiar with how to compile C++ code (Windows, Mac, or Linux) 
which requires setting up your environment and getting familiar with the tool sof the trade like VIsual Studio.

- Make sure everyone successfully runs this [.cpp](https://github.com/Pomona-ITS/DailyChallenges/blob/main/attachments/ArrayVsLists.cpp) file and saves their output

- When there are several submissions we will discuss

- Learning to read the code (especially someone else's


Mike's output:

```

D:\temp\array_vs_linked_list\ArrayVsList\Release>ArrayVsList.exe
----------
Using 10000000 numbers....
----------
Setup begins...
Array setup started...
Array setup finished!
Linked list setup started...
Linked list setup finished!

ARRAY creation and population time: 14 milliseconds
LINKED LIST creation and population time: 491 milliseconds

Array lookup started...
Array lookup finished!
Linked list lookup started...
Linked list lookup finished...
Linked list cleverer lookup started...
Linked list cleverer[ererererer] lookup finished!

ARRAY lookup time for ALL numbers: 2 milliseconds
(last number found was 9999999)
LINKED LIST lookup time for numbers, skipping by 10,000 each time(!): 13279 milliseconds
(last number found was 9990000)

Now imagine how much longer a naive list lookup for ALL the numbers would take!
(Hint: Less than 10,000 times as long...but not much less...)

And finally....

LINKED LIST CLEVER lookup time for ALL numbers: 35 milliseconds
(last number found was 9999999)
Optimization helps!

The tradeoff between flexibility and speed is a programmer's oldest nemesis, and closest companion.
Or something equally zen.

D:\temp\array_vs_linked_list\ArrayVsList\Release

```

[Back to Table of Contents](https://github.com/Pomona-ITS/DailyChallenges/blob/main/README.md)
