# MockSensor2

Intro:
This is a school project where we simulated some 200ish car sensors that sent true/false data to the heap, where it only had 70 bytes to work with during one second before the data had to be deleted. 
I can't say I did this all by myself as I got help from both my teacher and my partner, but at least it works.

Side note, please ignore the very obvious comments in the code, they are for me personally as I'm learning new syntax. 


Description:

fileGenerator: 
I made this source file super simple and hard coded a file generator that only ever prints out 10 files that changes data between each file in a very predictable way.
This is not like actual car sensors at all, but it becomes good testing data, which is what I needed for the fileReader source file.

fileReader:
This was the trickier bit. 

First I read the files that the fileGerator generated. Then, to be able to handle data from 236 sensors (bits) only using 70 bytes, I did 236/70 (and rounded up and got) = 30. 
I created smaller arrays of 30 bytes so that two arrays could be compared to each other before throwing the old one (lastSensorData) away. 
That way there were only ever 60 bytes that were occupied at the same time. 
These are the playWithData methods. They compare one byte by byte. 
The playWithDataBackwardsAndPrint() does exactly what it says it does. I have to have this method to be able to tell which sensor triggers the alarm. 

The 1 second sleep is only added for dramatic effect. 
