/*
* Do not edit!!
* Method will allow time to pass between a start hour and stop hour, once stop hour is reached
* the server resets back to the start hour!
* PARAMS
* int StartHour : The start hour, valid input 0-23
* int stopHour : The stop hour, valid input 0-23
* bool firstRun : Tells the script if its the first time it runs to properly set the time, valid input true-false
*/
void cappsTimeLoop(int startHour, int stopHour, bool firstRun)
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute); //gets current date and Timer

	//if its the first run of the script sets the time and date! Else goes through the normal switches
	if (firstRun == true)
	{
		GetGame().GetWorld().SetDate(year, month, day, startHour, minute); //sets time back to start hour
	    GetGame().ChatPlayer("A New day has begun, today is: "+month.ToString()+"/"+day.ToString()+"/"+year.ToString());
	}
	else if (hour >= stopHour)
  	{
	    //Checking if the day is 30 or 31 if yes, increase month by 1 and set day to 1, else increase day by 1
	    if (day >= 30)
	    {
	      //checks if the month is 12, if yes, increase year by 1 and set month to 1, else increase month by 1
	      if (month == 12)
	      {
	        year = year + 1;
	        month = 1;
	      }
	      else
	      {
	        month = month + 1;
	      }
	      day = 1;
	    }
	    else
	    {
	      day = day + 1;
	    }
	    //GetGame().ChatPlayer(1,"Triggering Time Switch"); //for debug purposes
	    GetGame().GetWorld().SetDate(year, month, day, startHour, minute); //sets time back to start hour
	    GetGame().ChatPlayer("A New day has begun, today is: "+month.ToString()+"/"+day.ToString()+"/"+year.ToString());
  	}
}
