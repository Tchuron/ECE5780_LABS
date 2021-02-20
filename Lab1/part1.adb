with Ada.Text_IO;
use  Ada.Text_IO;

with Text_Io;
use  Text_Io;

with Ada.Calendar;
use  Ada.Calendar;

procedure Part1  is
   
   programTime, F1_Start, F1_Curr: Duration;
   vTime, F1_Sched: Time;
   
   package DIO is new Text_Io.Fixed_Io(Duration); --To print Duration variables you can instantiate the generic 
						  --package Text_Io.Fixed_Io with a duration type: 
						  --"package DIO is new Text_Io.Fixed_Io(Duration);" 
						  --The DIO package will then export, among other things, 
						  --the procedure DIO.Put(D:Duration, Fore:Field, Aft:Field) 
						  --to print variable D of type Duration. See an example
						  --on how to use this below.
   
   --Declare F1, which prints out a message when it starts and stops executing
   procedure F1(Currtime: Duration; StartF1: Duration; FinishF1: Duration) is 
   begin
      if StartF1 = 0.0 and then FinishF1 = 0.0 then
	 Put_Line(""); --Add a new line
	 Put_Line("F1 has started executing. The time is now:");
	 DIO.Put(Currtime);
      else
	 Put_Line("");
	 Put_Line("F1 has finished executing. The time is now:");
	 DIO.Put(Currtime + (FinishF1 - StartF1)); --Needed since time starts at 0 and FinishF1 and StartF1 are not virtual times
      end if;  
   end F1;
      
begin
   vTime := Ada.Calendar.Clock;
   F1_Sched := vTime;
   programTime := 0.0;
   
   --Main loop
   loop
	 F1_Sched := F1_Sched + 1.0000;

	  delay until F1_Sched;
	 
	  programTime := Ada.Calendar.Clock - vTime;
	 F1_Start := Ada.Calendar.Seconds(Ada.Calendar.Clock); --Get start time of F1
	 F1(Currtime => programTime, StartF1 => 0.0, FinishF1 => 0.0); --Initialize F1

	 --delay until F1_Sched_End;
	 delay 0.3;
  
	 F1_Curr := Ada.Calendar.Seconds(Ada.Calendar.Clock);
	 --After F1 finishes executing, call the F1 procedure again to obtain the finish time
	 F1(Currtime => programTime, StartF1 => F1_Start, FinishF1 => F1_Curr);
	
   end loop; --Main loop
  
  end Part1; 
