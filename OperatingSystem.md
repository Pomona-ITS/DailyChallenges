# Operating System (OS)


Download a CentOS 7 Everything ISO (a digital DVD image) from one of these mirrors: https://www.centos.org/download/

Preferably IN THE OFF HOURS so as not to disrupt the network (it is going to be about 9.4GB) and note how long that takes. 

(for me: 25 minutes at about 6-7 MB/s on a wired 1 GB connection and 10 minutes at 10-20MB/s on wireless!!). 

That is ~1GB a minute, ~60 GB an hour and ~1,5 TB in 24 hours. If you are doing this on a Mac, use "time" 

command before the download command. Use "wget" or "curl" with the download URL. It will look something like this:


time wget http://centos.mirror.ndchost.com/7/isos/x86_64/CentOS-7-x86_64-Everything-1804.iso

or

time curl -o CentOS-7-x86_64-Everything-1804.iso http://centos.mirror.ndchost.com/7/isos/x86_64/CentOS-7-x86_64-Everything-1804.iso

If this is Windows, here is a dissertation's worth of various ways to measure this on Windows: 
https://stackoverflow.com/questions/673523/how-do-i-measure-execution-time-of-a-command-on-the-windows-command-line.

For some of you who don't know yet: you have just done your first ever benchmark. 
The next daily challenge is going to be related to this one and will explain the importance of having a l
ocal repository (repo) for vendoring/artifacts/OS packages/updates.
P.S. If you interrupt the download before it is done you can restart with "wget -c" or "curl -C" or use 
CyberDuck, one of many GUI clients useful for staging multiple downloads and uploads.

Vendoring is explained here: https://stackoverflow.com/questions/26217488/what-is-vendoring

Local OS repos: https://www.certdepot.net/rhel7-set-local-repository-lab/

Artifact or Binary repository: https://en.wikipedia.org/wiki/Binary_repository_manager

Some of the benefits:

accessible even if the original repo goes down

security because you can rebuild the package on the fly etc

[Back to Table of Contents](https://github.com/Pomona-ITS/DailyChallenges/blob/main/README.md)
