### [NAME] ###

toh - A commandline program for solving classical Tower of Hanoi problem.

### [USAGE] ###

toh [OPTIONS] [FILE]

### [OPTIONS] ###

**-c :** Count CPU time to move certain number of disk. If this option is specified -d
     option must be specified.

**-d DISKNUMBER :** Specify number of disks to move 

**-m :** Move disk from one peg to another peg. If this option is specified -d, -f, -t
     options must be specified.
     -s, -p optional arguments can be specified. -m assumes -c by default.

**-f FROMPEG :** Move DISKNUMBER disks FROMPEG tower. Towers are A, B and C.

**-t TOPEG :** Move DISKNUMBER disks FROMPEG tower to TOPEG tower.
           Towers are A, B and C.

**-s :** This is an optional argument. If specified instructions will be shown to move
     DISKNUMBER disks from FROMPEG tower to TOPEG tower

**-p NUMBER :** Optional argument. If specified percentage of progress will be
		   shown in NUMBER% interval.

**FILE :** Last argument is a file location. If specified outputs will be saved
       in FILE rather than standard output.

### [EXAMPLE] ###

Show time to move 30 disks in a particular CPU:

`$ toh -c -d 30`

Output:

`It took: 0y, 0d, 0h, 0m, 39.848998s`

Move 30 disk from peg A to peg C and report progress in 20% interval:

`$ toh -m -d 30 -f A -t C -p 20`

Output:

```
###### Towers Of Hanoi ######

Tower A: 0123456789ABCDEFGHIJKLMNOPQRST
Tower B: Empty!
Tower C: Empty!

Transferring All Disks From A ===> To C Peg
Progress: 0 %
Progress: 20 %
Progress: 40 %
Progress: 60 %
Progress: 80 %
Progress: 100 %

###### Towers Of Hanoi ######

Tower A: Empty!
Tower B: Empty!
Tower C: 0123456789ABCDEFGHIJKLMNOPQRST

I needed 1073741823 Moves!
It took: 0y, 0d, 0h, 0m, 57.050643s
```

Move 3 disks from peg A to peg B and also show steps:

`$ toh -m -s -d 3 -f A -t C`

Output:

```
###### Towers Of Hanoi ######

Tower A: 012
Tower B: Empty!
Tower C: Empty!

Transferring All Disks From A ===> To C Peg
Move Disk 1: Form A To C
Move Disk 2: Form A To B
Move Disk 1: Form C To B
Move Disk 3: Form A To C
Move Disk 1: Form B To A
Move Disk 2: Form B To C
Move Disk 1: Form A To C

###### Towers Of Hanoi ######

Tower A: Empty!
Tower B: Empty!
Tower C: 012

I needed 7 Moves!
It took: 0y, 0d, 0h, 0m, 0.000249s
```
