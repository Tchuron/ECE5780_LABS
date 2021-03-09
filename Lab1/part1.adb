with Ada.Text_IO;  --Context clauses
use  Ada.Text_IO;

with Text_Io;
use  Text_Io;

with Ada.Calendar;
use  Ada.Calendar;

with Ada.Numerics.Float_Random, Ada.Text_IO, Ada.Float_Text_IO;
use Ada.Numerics.Float_Random, Ada.text_IO, Ada.Float_Text_IO;

with Ada.Numerics.Discrete_Random;

----------------------------------------------------------------------------------------------------------------
procedure Part1  is 
----------------------------------------------------------------------------------------------------------------
  -- Local variables
  -- programTime: duration of seconds the program has been running
  -- F1_Start: used as a starting time for F1, F2, and F3 arguments
  -- F1_Curr: used to represent the current time as a duration, for the way F1-F3 report the time
  -- vTime: the time the program starts
  -- F1_Sched: The time planned for F1 to start (always at whole seconds from program start time [vTime])
  -- A_Random_Float: A temporary variable for holding a random number
  -- My_Generator: For generating a randomized delay in F3
  programTime, F1_Start, F1_Curr: Duration;
  vTime, F1_Sched: Time;

  A_Random_Float : Float;
  My_Generator : Generator;
  subtype Random_Int is Integer range 0 .. 25;
   


  package DIO is new Text_Io.Fixed_Io(Duration);  --To print Duration variables you can instantiate the generic 
                                                  --package Text_Io.Fixed_Io with a duration type: 
                                                  --"package DIO is new Text_Io.Fixed_Io(Duration);" 
                                                  --The DIO package will then export, among other things, 
                                                  --the procedure DIO.Put(D:Duration, Fore:Field, Aft:Field) 
                                                  --to print variable D of type Duration. See an example
                                                  --on how to use this below.
                                                  
   
   
   -----------------------------------------------------------------------------
   --Create 3 tasks for Communication among Tasks part (Part 6)
   -----------------------------------------------------------------------------
   --FIFO Buffer for integers 

  function Get_Random_Int return Random_Int is
    package A_Random_Int is new Ada.Numerics.Discrete_Random(Random_Int);
    use A_Random_Int;
    G : A_Random_Int.Generator;
    Result : Random_Int := 0;
  begin
    Reset(G);
    Result := Random(G);
    return Result;
  end Get_Random_Int;
  

   task Int_Buffer is
      -- Buffer size is 11.
      entry Push (New_Int : in Random_Int); 
      entry Pull (Old_Int : out Random_Int);
      entry Done;
   end; 
   
   
   task body Int_Buffer is  
      --Variables for buffer tasks
      A: array(0..9) of Random_Int; -- Array subscripts 0 to 9.
      F: Integer :=0;  -- Front index  Front is the next be filled
      B: Integer :=0;  -- back index back is next to be emptied
      Size: Integer :=0;
      Exiting: Boolean := False;
      begin
      loop         
         select
            when Size < 10 => accept Push (New_Int : in Random_Int) do
               -- add pushed integer to the new front
               A(F) := New_Int;
               -- increment front
               F := F + 1;
               if F > 9 then
                  F := F -10;
               end if;
               -- increment size
               Size := Size + 1; 
            end Push;
            or
             when Size > 0 => accept Pull (Old_Int : out Random_Int) do
              -- access back
              Old_Int := A(B);
               -- increment back
              B := B+1;
              if B > 9 then
                 B := B -10;
              end if;      
              -- decerement size
              Size := Size -1;   
            end Pull;
            or
            accept done do
              Exiting := true;
            end done;
         end select;
         exit when Exiting = true;
      end loop;
   end;
   
     
   task Int_Producer is
     
      entry Done;
   end Int_Producer;
    

   task body Int_Producer is
   
      Exiting: Boolean := False;
      R : Random_Int;
     
   begin
      R := 0;
      loop
         delay Duration(Random(My_Generator));
         
         R :=  Get_Random_Int;
         Int_Buffer.Push(R); --send new random integer to buffer
         Put("Producer: ");
         Put_Line(Integer'Image(R)); --print value of new integer sent to buffer
         select
           accept done do
             Exiting := true;
           end done;
           or
           delay 0.0;
         end select;
         exit when Exiting = true;
      end loop;
   end;
     
     
   task Int_Consumer is
   end;
   
   task body Int_Consumer is
      Total : integer; 
      Buffer_Pull : Random_Int;
   begin
      Total := 0;
      loop
         delay Duration(Random(My_Generator));   -- At irregular intervals

         Int_Buffer.Pull(Buffer_Pull);     -- Pull integer from bottom of buffer
         Put("Consumer: ");
         Put_Line(Integer'Image(Buffer_Pull)); --print value of new integer taken from Buffer
         Total := Total + Buffer_Pull; -- Add new integer to total
         --If total > 99 terminate program

         exit when Total >= 100;
      end loop; 
      Int_Producer.done;
      Int_Buffer.done;
   end;

begin
   
  null; -- wait until tasks are done, then exit
  
  end Part1; 
