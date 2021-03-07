with Ada.Text_IO;  --Context clauses
use  Ada.Text_IO;

with Text_Io;
use  Text_Io;

with Ada.Calendar;
use  Ada.Calendar;

with Ada.Numerics.Float_Random, Ada.Text_IO, Ada.Float_Text_IO;
use Ada.Numerics.Float_Random, Ada.text_IO, Ada.Float_Text_IO;
----------------------------------------------------------------------------------------------------------------
procedure Part1  is 
----------------------------------------------------------------------------------------------------------------
  -- Local variables
  -- programTime: duration of seconds the program has been running
  -- F1_Start: used as a starting time for F1, F2, and F3 arguments
  -- F1_Curr: used to represent the current time as a duration, for the way F1-F3 report the time
  -- vTime: the time the program starts
  -- F1_Sched: The time planned for F1 to start (always at whole seconds from program start time [vTime])
  -- A_Random_Number: A temporary variable for holding a random number
  -- My_Generator: For generating a randomized delay in F3
  programTime, F1_Start, F1_Curr: Duration;
  vTime, F1_Sched: Time;

  A_Random_Number : Float;
  My_Generator : Generator;

  package DIO is new Text_Io.Fixed_Io(Duration);  --To print Duration variables you can instantiate the generic 
                                                  --package Text_Io.Fixed_Io with a duration type: 
                                                  --"package DIO is new Text_Io.Fixed_Io(Duration);" 
                                                  --The DIO package will then export, among other things, 
                                                  --the procedure DIO.Put(D:Duration, Fore:Field, Aft:Field) 
                                                  --to print variable D of type Duration. See an example
                                                  --on how to use this below.
   
  task WatchdogF3 is
    entry Init;
    entry Done;
  end;
  task body WatchdogF3 is
  begin
    loop
      select
        accept Init;
        delay 0.5;
        select
          accept Done;
        else
          Put(" F3 missed its deadline! Delaying 1 second. ");
          F1_Sched := F1_Sched + 1.0000; -- increment the start time to prepare for next loop
        end select;
      or
        accept Done;
      end select;
    end loop;
  end;

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

  procedure F2(Currtime: Duration; StartF2: Duration; FinishF2: Duration) is
  begin
    if StartF2 = 0.0 and then FinishF2 = 0.0 then
      Put_Line("");
      Put_Line("F2 has started executing. The time is now:");
      DIO.Put(Currtime);
    else
      Put_Line("");
      Put_Line("F2 has finished executing. The time is now:");
      DIO.Put(Currtime + (FinishF2 - StartF2)); --Needed since time starts at 0 and FinishF2 and StartF2 are not virtual times
    end if;
  end F2;

  procedure F3(Currtime: Duration; StartF3: Duration; FinishF3: Duration) is
  begin
    if StartF3 = 0.0 and then FinishF3 = 0.0 then
      Put_Line("");
      Put_Line("F3 has started executing. The time is now:");
      DIO.Put(Currtime);
      A_Random_Number := Random(My_Generator);
      delay 0.2 + Duration(A_Random_Number/2.0); -- F3 defined to take 0.2 seconds, plus a random delay
    else
      WatchdogF3.Done;
      Put_Line("");
      Put_Line("F3 has finished executing. The time is now:");
      DIO.Put(Currtime + (FinishF3 - StartF3)); --Needed since time starts at 0 and FinishF3 and StartF3 are not virtual times
    end if;
  end F3;

begin
  vTime := Ada.Calendar.Clock; -- vTime gets program start time
  F1_Sched := vTime; -- F1 will first start at the program start
  programTime := 0.0; -- The program duration starts at zero

  --Main loop
  loop

    delay until F1_Sched;

    programTime := Ada.Calendar.Clock - vTime;
    F1_Start := Ada.Calendar.Seconds(Ada.Calendar.Clock); --Get start time of F1 as a duration
    F1(Currtime => programTime, StartF1 => 0.0, FinishF1 => 0.0); --Initialize F1

    delay 0.3; -- F1 defined to take 0.3 seconds to complete

    F1_Curr := Ada.Calendar.Seconds(Ada.Calendar.Clock);
    --programTime is not updated because the correct time is calculated within F1
    --After F1 finishes executing, call the F1 procedure again to obtain the finish time
    F1(Currtime => programTime, StartF1 => F1_Start, FinishF1 => F1_Curr);

    F1_Start := Ada.Calendar.Seconds(Ada.Calendar.Clock); --Get start time of F2, which is now
    programTime := Ada.Calendar.Clock - vTime;
    F2(Currtime => programTime, StartF2 => 0.0, FinishF2 => 0.0); -- release F2

    delay 0.15; -- F2 defined to take 0.15 seconds

    F1_Curr := Ada.Calendar.Seconds(Ada.Calendar.Clock);
    F2(Currtime => programTime, StartF2 => F1_Start, FinishF2 => F1_Curr);
	
    -- delay until 0.5 after F1 started
    delay until (F1_Sched + 0.500);
    programTime := Ada.Calendar.Clock - vTime;
    F1_Start := Ada.Calendar.Seconds(Ada.Calendar.Clock); --Get start time of F3
    WatchdogF3.Init;
    F3(Currtime => programTime, StartF3 => 0.0, FinishF3 => 0.0); -- release F3
    F1_Curr := Ada.Calendar.Seconds(Ada.Calendar.Clock);
    F3(Currtime => programTime, StartF3 => F1_Start, FinishF3 => F1_Curr);

    F1_Sched := F1_Sched + 1.0000; -- increment the start time to prepare for next loop
  end loop; --Main loop
  
  end Part1; 
