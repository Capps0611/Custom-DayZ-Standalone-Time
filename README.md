# Custom DayZ Standalone Time 
###### by Capps

With the release of DayZ Standalone there have been some requests out there to enable server owners to keep the time of day on their server set to certain point. For example some may want their server to always remain in daylight and others might want eternal darkness. So with that, I've gone ahead and written a small server side script to do just that! Lets dive right into it!

# Installation
  1. Download a copy of the **"Scripts"** folder from [GitHub](https://github.com/Capps0611/Custom-DayZ-Standalone-Time/releases/download/v0.0.1/Scripts.zip)
  2. Exact the **"Scripts"** folder into your **MPMissions\dayzOffline.chernarusplus directory**
  3. Open your Init.c file
  4. At the top of the Init.c file add directly above **void main()** 
  ```c
   #include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Scripts\\cappsTimeLoop.c"  
   int startHour = 10;   
   int stopHour = 16; 
 ```
 5. To configure the script you will want to adjust the **startHour** and **stopHour**. To get an idea, **0 is 12:00am and 23 is 11:00pm**
 6. Next inside of the **void main()** at the very bottom, you will want to add
  ```c
  cappsTimeLoop(startHour,stopHour,true);
  ```
 7. Next scoll down to just underneath **override void StartingEquipSetup()** inside of the **class CustomMission: MissionServer:**
 8. You are going to add the following code:
 
 ```c
 override void TickScheduler (float timeSplice)
	{
		GetGame().GetWorld().GetPlayerList(m_Players);
		if( m_Players.Count() == 0 ) return;
		for(int i = 0; i < SCHEDULER_PLAYERS_PER_TICK; i++)
		{
	     if(m_currentPlayer >= m_Players.Count() )
	     {
	        m_currentPlayer = 0;
	     }
	     PlayerBase currentPlayer = PlayerBase.Cast(m_Players.Get(m_currentPlayer));
	     currentPlayer.OnTick();
	     m_currentPlayer++;


	   }
		//Ignore above code that is required to keep food,drink and other survival elements working

		int currentTime = GetGame().GetTime() * 0.001;
		static int newTime = 0;
		int timeDelay = 180;
		if (currentTime >= newTime + timeDelay)
		{
			//GetGame().ChatPlayer(1,"3 minute check on reset!");//for debug pruposes
			cappsTimeLoop(startHour,stopHour,false);
			//GetGame().ChatPlayer(1,"Passed the time switch call");//for debug pruposes
			newTime = currentTime;
		}
	}
```
