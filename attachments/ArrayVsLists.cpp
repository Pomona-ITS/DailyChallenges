<<<<<<< HEAD
// Simple array vs linked-list performance in C/++

// "Array" is a specific term meaning "one contiguous area of memory".
// "LINKED list" is a specific term meaning "separate nodes in memory, each holding a value and pointer to other nodes".
// However, "list" just means "the best structure for the use to which it will be put", so "list" can mean EITHER THING and a bunch of other things.
// Be careful!

// Having an experienced programmer write this is a bit like having Michelangelo paint your kitchen but \/\/hate\/er.  :^)

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* srand, rand */

// these are C++11, so HAVE THAT :^)
#include <chrono>

struct ListNode
{
	ListNode *next;
	int value;
};

int main()
{
	const int NUM_NUMBERS = 10000000;

	printf("----------\nUsing %d numbers....\n----------\n", NUM_NUMBERS);  // "printf" is pronounced "printh"*

	// -- SETUP --

	printf("Setup begins...\n");

	// TIME JUNK
	__int64 arrayStartTime, arrayEndTime,
		listStartTime, listEndTime,
		listStartTime2, listEndTime2;

	// we're going to include memory allocation in the time elapsed

	printf("Array setup started...\n");

	// -----
	// so telling time at a good resolution (less than seconds) in C++ is a whole stupid THING, just trust me that this works and is why we need C++11
	arrayStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// ARRAY
	// + one chunk of memory, takes the least space possible
	// + consistent lookup time of an element in a known position
	// + consistent insert time regardless of size or placement of the item to insert
	// - no easy way to resize without allocating another giant chunk of memory and copying values to it
	// - no deleting unless you use a specific value to mean "this entry is deleted", called a "sentinel value"

	int *arrayMem;

	// allocate one giant chunk of memory
	arrayMem = new int[NUM_NUMBERS]; // one memory allocation, but changing the size is NOT POSSIBLE

	// fill the array with the numbers IN ORDER
	for(int i = 0; i < NUM_NUMBERS; i++)
	{
		arrayMem[i] = i;
	}

	// that's it for the array
	arrayEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	// -----

	printf("Array setup finished!\n");
	printf("Linked list setup started...\n");

	listStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// -----
	// LINKED LIST
	// + size can change
	// + can insert and delete elements in any spot at any time
	// - takes much more memory than an array
	// - lookup of an item in a known position is much slower
	// - finding out whether an item is in the list is somewhat slower
	
	// and we're going to create it the fastest way which avoids having an if() in the loop each time, for a million times

	ListNode *listHead = nullptr, *listTail = nullptr;

	// add the first value - normally you don't get to sexily optimize this, 
	// you have to either check if listHead==0 each time OR build the list BACKWARD so you're setting listHead each time...
	// but we're gonna do it the faster galaxy-brain way for this example
	{
		ListNode *node = new ListNode;
		node->next = 0;
		node->value = 0;
		listHead = node;
		listTail = node;
	}
	// add the rest of the values, placing them at the tail each time
	for(int i = 1; i < NUM_NUMBERS; i++)
	{
		ListNode *node = new ListNode; // a separate memory allocation per node
		node->value = i;
		node->next = 0; // track the pointers of the next node so it's possible to follow the chain down the list
		listTail->next = node;
		listTail = node;
	}

	listEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	printf("Linked list setup finished!\n");

	// print info
	printf("\nARRAY creation and population time: %lld milliseconds\n", (arrayEndTime - arrayStartTime));
	printf("LINKED LIST creation and population time: %lld milliseconds\n\n", (listEndTime - listStartTime));

	// looking up all elements, to get a feel for average-case lookup performance

	printf("Array lookup started...\n");

	// -----
	arrayStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// ARRAY

	int arrayVal = -1;
	for(int i = 0; i < NUM_NUMBERS; i++)
	{
		// we know exactly where each number is in memory, so just get that location specifically!
		arrayVal = arrayMem[i]; // gotta do something that will matter outside the loop or the compiler will optimize this line away to no code at all!
	}

	arrayEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	printf("Array lookup finished!\n");
	printf("Linked list lookup started...\n");


	// -----
	listStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// LINKED LIST

	int listVal = -1;
	// okay here's the deal, this is SO MUCH slower	like on the order of thousands of times, so we're going to SKIP BY 10000!
	// and it's STILL gonna be startlingly slower!
	for(int i = 0; i < NUM_NUMBERS; i += 10000) 
	{
		// Now we have to TRAVEL DOWN THE LIST to find each one, which means for 999,999 we're travelling 999,999 nodes,
		// but then for 1,000,000 we're travelling 1,000,000 MORE nodes AGAIN!  So this is MUCH slower.
		ListNode *checkNode = listHead;
		for(int listPos = 0; listPos < i; listPos++)
		{
			checkNode = checkNode->next;
		}

		if(checkNode) // if we didn't reach the end of the list
			listVal = checkNode->value; // gotta do something that will matter outside the loop or the compiler will optimize this line away to no code at all!
										// this is also a pointer lookup, so this is slower too

        // OF COURSE, YOU CAN DO THIS BETTER if you know you're looking for all the numbers in order (just keep a ptr and do next-> once per loop),
		// but we're assuming we don't actually know which number we want compared to the previous number, which is likely in real use

		// "OF COURSE, YOU CAN DO THIS BETTER if you know ____ by writing specific code for this one case" is generally true when programming, 
		// and is called "optimization".
		// Good programmers know when to spend time optimizing for a particular case, and when not to.  Usually it's trial-and-error for like ten years.  :^P
	}

	listEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	printf("Linked list lookup finished...\n");

	printf("Linked list cleverer lookup started...\n");

	listStartTime2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// Now we're gonna do it by just moving to the previous node, pretending we were smart programmers.
	// This is still slower than an array, but it's faster than the above naive attempt.

	int listVal2 = -1;
	// okay here's the deal, this is SO MUCH slower	like on the order of thousands of times, so we're going to SKIP BY 10000!
	// and it's STILL gonna be startlingly slower!
	ListNode *checkNode = listHead; // start at the beginning
	for(int i = 0; i < NUM_NUMBERS; i++)
	{
		if(checkNode) // if we didn't reach the end of the list
			listVal2 = checkNode->value; // gotta do something that will matter outside the loop or the compiler will optimize this line away to no code at all!
										// this is also a pointer lookup, so this is slower too

		checkNode = checkNode->next; // now we're just moving to the next node each time
	}

	listEndTime2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	printf("Linked list cleverer[ererererer] lookup finished!\n");

	// we're printing the arrayVal/listVal so that the code in the loops has to be RUN because the RESULT IS USED.  Take that, optimizing compilers!
	printf("\nARRAY lookup time for ALL numbers: %lld milliseconds\n(last number found was %d)\n", (arrayEndTime - arrayStartTime), arrayVal);
	printf("LINKED LIST lookup time for numbers, skipping by 10,000 each time(!): %lld milliseconds\n(last number found was %d)\n", (listEndTime - listStartTime), listVal);
	printf("\nNow imagine how much longer a naive list lookup for ALL the numbers would take!\n(Hint: Less than 10,000 times as long...but not much less...)\n");
	printf("\nAnd finally....\n\nLINKED LIST CLEVER lookup time for ALL numbers: %lld milliseconds\n(last number found was %d)\nOptimization helps!\n", (listEndTime2 - listStartTime2), listVal2);

	printf("\nThe tradeoff between flexibility and speed is a programmer's oldest nemesis, and closest companion.\nOr something equally zen.\n");

	return 0; // Zero means "everything is fine".  This is not usually what zero means, but here, that's what zero means.  Welcome to programming!  :^P
}

=======
// Simple array vs linked-list performance in C/++

// "Array" is a specific term meaning "one contiguous area of memory".
// "LINKED list" is a specific term meaning "separate nodes in memory, each holding a value and pointer to other nodes".
// However, "list" just means "the best structure for the use to which it will be put", so "list" can mean EITHER THING and a bunch of other things.
// Be careful!

// Having an experienced programmer write this is a bit like having Michelangelo paint your kitchen but \/\/hate\/er.  :^)

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* srand, rand */

// these are C++11, so HAVE THAT :^)
#include <chrono>

struct ListNode
{
	ListNode *next;
	int value;
};

int main()
{
	const int NUM_NUMBERS = 10000000;

	printf("----------\nUsing %d numbers....\n----------\n", NUM_NUMBERS);  // "printf" is pronounced "printh"*

	// -- SETUP --

	printf("Setup begins...\n");

	// TIME JUNK
	__int64 arrayStartTime, arrayEndTime,
		listStartTime, listEndTime,
		listStartTime2, listEndTime2;

	// we're going to include memory allocation in the time elapsed

	printf("Array setup started...\n");

	// -----
	// so telling time at a good resolution (less than seconds) in C++ is a whole stupid THING, just trust me that this works and is why we need C++11
	arrayStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// ARRAY
	// + one chunk of memory, takes the least space possible
	// + consistent lookup time of an element in a known position
	// + consistent insert time regardless of size or placement of the item to insert
	// - no easy way to resize without allocating another giant chunk of memory and copying values to it
	// - no deleting unless you use a specific value to mean "this entry is deleted", called a "sentinel value"

	int *arrayMem;

	// allocate one giant chunk of memory
	arrayMem = new int[NUM_NUMBERS]; // one memory allocation, but changing the size is NOT POSSIBLE

	// fill the array with the numbers IN ORDER
	for(int i = 0; i < NUM_NUMBERS; i++)
	{
		arrayMem[i] = i;
	}

	// that's it for the array
	arrayEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	// -----

	printf("Array setup finished!\n");
	printf("Linked list setup started...\n");

	listStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// -----
	// LINKED LIST
	// + size can change
	// + can insert and delete elements in any spot at any time
	// - takes much more memory than an array
	// - lookup of an item in a known position is much slower
	// - finding out whether an item is in the list is somewhat slower
	
	// and we're going to create it the fastest way which avoids having an if() in the loop each time, for a million times

	ListNode *listHead = nullptr, *listTail = nullptr;

	// add the first value - normally you don't get to sexily optimize this, 
	// you have to either check if listHead==0 each time OR build the list BACKWARD so you're setting listHead each time...
	// but we're gonna do it the faster galaxy-brain way for this example
	{
		ListNode *node = new ListNode;
		node->next = 0;
		node->value = 0;
		listHead = node;
		listTail = node;
	}
	// add the rest of the values, placing them at the tail each time
	for(int i = 1; i < NUM_NUMBERS; i++)
	{
		ListNode *node = new ListNode; // a separate memory allocation per node
		node->value = i;
		node->next = 0; // track the pointers of the next node so it's possible to follow the chain down the list
		listTail->next = node;
		listTail = node;
	}

	listEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	printf("Linked list setup finished!\n");

	// print info
	printf("\nARRAY creation and population time: %lld milliseconds\n", (arrayEndTime - arrayStartTime));
	printf("LINKED LIST creation and population time: %lld milliseconds\n\n", (listEndTime - listStartTime));

	// looking up all elements, to get a feel for average-case lookup performance

	printf("Array lookup started...\n");

	// -----
	arrayStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// ARRAY

	int arrayVal = -1;
	for(int i = 0; i < NUM_NUMBERS; i++)
	{
		// we know exactly where each number is in memory, so just get that location specifically!
		arrayVal = arrayMem[i]; // gotta do something that will matter outside the loop or the compiler will optimize this line away to no code at all!
	}

	arrayEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	printf("Array lookup finished!\n");
	printf("Linked list lookup started...\n");


	// -----
	listStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// LINKED LIST

	int listVal = -1;
	// okay here's the deal, this is SO MUCH slower	like on the order of thousands of times, so we're going to SKIP BY 10000!
	// and it's STILL gonna be startlingly slower!
	for(int i = 0; i < NUM_NUMBERS; i += 10000) 
	{
		// Now we have to TRAVEL DOWN THE LIST to find each one, which means for 999,999 we're travelling 999,999 nodes,
		// but then for 1,000,000 we're travelling 1,000,000 MORE nodes AGAIN!  So this is MUCH slower.
		ListNode *checkNode = listHead;
		for(int listPos = 0; listPos < i; listPos++)
		{
			checkNode = checkNode->next;
		}

		if(checkNode) // if we didn't reach the end of the list
			listVal = checkNode->value; // gotta do something that will matter outside the loop or the compiler will optimize this line away to no code at all!
										// this is also a pointer lookup, so this is slower too

        // OF COURSE, YOU CAN DO THIS BETTER if you know you're looking for all the numbers in order (just keep a ptr and do next-> once per loop),
		// but we're assuming we don't actually know which number we want compared to the previous number, which is likely in real use

		// "OF COURSE, YOU CAN DO THIS BETTER if you know ____ by writing specific code for this one case" is generally true when programming, 
		// and is called "optimization".
		// Good programmers know when to spend time optimizing for a particular case, and when not to.  Usually it's trial-and-error for like ten years.  :^P
	}

	listEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	printf("Linked list lookup finished...\n");

	printf("Linked list cleverer lookup started...\n");

	listStartTime2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// Now we're gonna do it by just moving to the previous node, pretending we were smart programmers.
	// This is still slower than an array, but it's faster than the above naive attempt.

	int listVal2 = -1;
	// okay here's the deal, this is SO MUCH slower	like on the order of thousands of times, so we're going to SKIP BY 10000!
	// and it's STILL gonna be startlingly slower!
	ListNode *checkNode = listHead; // start at the beginning
	for(int i = 0; i < NUM_NUMBERS; i++)
	{
		if(checkNode) // if we didn't reach the end of the list
			listVal2 = checkNode->value; // gotta do something that will matter outside the loop or the compiler will optimize this line away to no code at all!
										// this is also a pointer lookup, so this is slower too

		checkNode = checkNode->next; // now we're just moving to the next node each time
	}

	listEndTime2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	printf("Linked list cleverer[ererererer] lookup finished!\n");

	// we're printing the arrayVal/listVal so that the code in the loops has to be RUN because the RESULT IS USED.  Take that, optimizing compilers!
	printf("\nARRAY lookup time for ALL numbers: %lld milliseconds\n(last number found was %d)\n", (arrayEndTime - arrayStartTime), arrayVal);
	printf("LINKED LIST lookup time for numbers, skipping by 10,000 each time(!): %lld milliseconds\n(last number found was %d)\n", (listEndTime - listStartTime), listVal);
	printf("\nNow imagine how much longer a naive list lookup for ALL the numbers would take!\n(Hint: Less than 10,000 times as long...but not much less...)\n");
	printf("\nAnd finally....\n\nLINKED LIST CLEVER lookup time for ALL numbers: %lld milliseconds\n(last number found was %d)\nOptimization helps!\n", (listEndTime2 - listStartTime2), listVal2);

	printf("\nThe tradeoff between flexibility and speed is a programmer's oldest nemesis, and closest companion.\nOr something equally zen.\n");

	return 0; // Zero means "everything is fine".  This is not usually what zero means, but here, that's what zero means.  Welcome to programming!  :^P
}

>>>>>>> Revert "Moving projects to ONHOLD"
// * = Gotcha!  It isn't really pronounced "printh", but if you SAY "printh", every C++ programmer will know what you mean.  (^.~)
