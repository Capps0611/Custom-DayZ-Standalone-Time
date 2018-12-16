#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\Scripts\\cappsTimeLoop.c"
int startHour = 10;
int stopHour = 16;
void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

    weather.MissionWeather(false);    // false = use weather controller from Weather.c

    weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
    weather.GetRain().Set( 0, 0, 1);
    weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year;
	int month;
	int day;
	int hour;
	int minute;

	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

    if (((month <= 9) && (day < 20)) || ((month >= 10) && (day > 20)))
    {
        month = 9;
        day = 20;

		GetGame().GetWorld().SetDate(year, month, day, hour, minute);
	}
	//sets the time correctly and marks the first run of the script!
	cappsTimeLoop(startHour,stopHour,true);
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
/*
		player.RemoveAllItems();

		EntityAI item = player.GetInventory().CreateInInventory(topsMissionArray.GetRandomElement());
		EntityAI item2 = player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		EntityAI item3 = player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
*/
		EntityAI itemTop;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemTop = player.FindAttachmentBySlotName("Body");

		if ( itemTop )
		{
			itemEnt = itemTop.GetInventory().CreateInInventory("Rag");
			if ( Class.CastTo(itemBs, itemEnt ) )
		itemBs.SetQuantity(4);

			SetRandomHealth(itemEnt);

			itemEnt = itemTop.GetInventory().CreateInInventory("RoadFlare");
			SetRandomHealth(itemEnt);

			itemEnt = itemTop.GetInventory().CreateInInventory("StoneKnife");
			SetRandomHealth(itemEnt);
		}

		rand = Math.RandomFloatInclusive(0.0, 1.0);
		if ( rand < 0.25 )
			itemEnt = player.GetInventory().CreateInInventory("SodaCan_Cola");
		else if ( rand > 0.75 )
			itemEnt = player.GetInventory().CreateInInventory("SodaCan_Spite");
		else
			itemEnt = player.GetInventory().CreateInInventory("SodaCan_Pipsi");

		SetRandomHealth(itemEnt);

		rand = Math.RandomFloatInclusive(0.0, 1.0);
		if ( rand < 0.35 )
			itemEnt = player.GetInventory().CreateInInventory("Apple");
		else if ( rand > 0.65 )
			itemEnt = player.GetInventory().CreateInInventory("Pear");
		else
			itemEnt = player.GetInventory().CreateInInventory("Plum");

		SetRandomHealth(itemEnt);
	}

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
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
