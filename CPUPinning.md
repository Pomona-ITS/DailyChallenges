# CPU Pinning

CPU Affinity (or CPU pinning)

CPU Affinity (or CPU pinning) is the process of keeping a certain task or thread to a specific CPU core. 
Since recent tasks run by an individual CPU are typically stored in a CPU cache shared among multiple cores, 
pinning a specific process to an individual core allows for fewer cache misses during intense workloads. 
CPU pinning is also a great way to manually control any computer's workload. (For example, if you have a 
quad-core laptop, pinning a VM to 3/4 cores and allocating one for your base OS might improve overall VM 
performance since the system won't choke as easily.)

Here is a YouTube video and two articles on this process.

https://www.youtube.com/watch?v=D8vLVWtFvis

https://en.wikipedia.org/wiki/Processor_affinity

https://www.linuxjournal.com/article/6799

[Back to Table of Contents](https://github.com/Pomona-ITS/DailyChallenges/blob/main/README.md)
