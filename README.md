# Co-operative Multitasking Demo

This is a little toy I wrote a while back to explore a bit of co-operative multitasking in C. It makes use of a table of processes, a round-robbin scheduler, and a little bit of assembly in order to run a simple little back-and-forth demo of 3 processes.

I'll probably be re-writing it if I make use of it in more serious projects, but thankfully this was quite a bit of fun to develop. 

## The Idea

I felt inspired to take a whack at some light-weight co-operative multitasking primitives, to start dipping my toes into processes while in the down-time of rewriting the build-system of another project. 

Combining what I learned with interrupts with x86_64 calling-conventions made this really simple to throw together. Switching the task was little more than throwing callee-saved registers into a table, and switching to the next task was just loading the new set of calle-saved registers and returning. 

## Debugging Hell

It was surprisingly how easy it was to start getting tasks to switch around, but I have to note that I went through a few days of hell thanks to a simple mistake.

The end-result of the mistake is about on the level of "Why is the task data getting corrupted?", then finding out that the function corrupting the task table was `puts`. Writing static strings with standard-library functions, what a dangerous endeavor apparently!

It turns out I was wrongly initializing the stacks for the new threads. In x86_64, the stack starts at the top and grows down, but I was handing off the bottom of the stack as the initial `rsp` value.

It took quite a few re-reads of the AMD64 ABI for me to realize my stupid error.

