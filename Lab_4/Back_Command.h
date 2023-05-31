#pragma once


#include "Menu_Command.h"
#include "Menu_Manager.h"


class Back_Command : public Menu_Command
{
	public:
		Back_Command();
		Back_Command(Menu_Manager& menuManager);

		void goBack();
		void executeTask() override;

	private:
		Menu_Manager& m_MenuManager;
};




/****************
 dont really think pause command is doing anything nor will it but if it should tell me.
My thoughts behind the pause menu are as follows

1) if user enters escape key the pause menu displays freezing the current game state with the following buttons

a) Customer Support
- contains a back button inside
- displays customer support details

b) Save Game // in here it should go to another menu which allows three seperate saves to click on, but each save overrides the chosen 1 of threes potential save files writting the new data.

- allows for three seperate save files to be written and if a save file that is selected already contains data it over rides the old data with current data.

- displays a button called save  allowing them to save their progress.

- displays a back button

c) Load Game // this should show the the saved games and allow the palyer to click on one of the saves and have the game then continue from that saved data.

- allows the player to select one of the three save files while dispalying brief data to the user such as score, duration played, time of save. e.g ( first save file : Fred, duration 1 minute, score 10) this is displayed to the user so the user doesnt have to load each file to find their desired save file.

- after clicking on the file the player can click a button called load and it will load the selected file.

- has a back button

d) Resume game
-resumes current game state.


e) Quit Game
- has a new menu that asks are you sure and provides two buttons back or yes.
- has a back button to return to the core pause menu (a - e)

Note in the options it has the following classes / buttoms
Load_Command //creates a load button and loads 1 of three character saves nd contain the functionality mentioned last time load_Command was mentiond
Save_Commnad // creates a save button should enable up to three different saves. nd contain the functionality mentioned last time Save_Commnad  was mentioned
Quit_Command //should close the glfw window and contain the functionality mentioned last time Quit_Command was mentioned
CustomerSupport_Command // create a customer support button and contain the functionality mentioned last time CusotmerSupport_Command was mentioned

Customer Support//calls display customer support and at the bottom of customer support should have a button called back which can be clicked to show the core menu again.

Save // should have a list of 3 saves where the user can select which save e.g save number one should display the character name, score, and save date all before the user clicks save to over ride the save file, same for two and three but with differnet save data e.g save 1 : bob, score 102, save date March 20 2023, save 2 : fred, score 20, save date June 20 2022,  which are buttons and save the data to one of three files e.g saveOne.txt, saveTwo.txt, saveThree.txt,  and click a save button, and also have a back button.

Load // should enable the player to load one of the three saves which are buttons with save files, and have a back button

Resume // reusumes current state of the game

Quit // quits the glfw window
***/