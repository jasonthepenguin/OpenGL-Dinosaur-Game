#pragma once

#include <string>
#include <vector>
#include "imgui.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "IPauseMenuCommand.h"
#include "imgui_impl_opengl3.h"



/***************************************************************************************************************
 * @brief : CustomerSupportCommand
 * @brief : represents a command for displaying customer support details.
 *          It provides functionality for displaying customer support details such as contact name, email, and availability.
 *          It also allows adding availability for different days and times.
 *          This class is derived from PauseMenu_Commands interface for integration with the pause menu system.
 * 
 * 
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class CustomerSupportCommand : public PauseMenu_Commands
{
    private:

            /********************************************************************************************************
             * @brief : Availablility Struct 
             * @brief : customer support for a specific day and time.
             ********************************************************************************************************/
       
        struct Availability 
        {
            std::string m_AvailableDays;  /// The available days 
            std::string m_AvailableTimes; /// The available times
        };

        std::vector<Availability> m_Availability;


    public:
            /**
             * @brief Constructs a new CustomerSupportCommand object with default values.
             */
        CustomerSupportCommand();

        std::string getEmail() const;
        std::string getName() const;
        std::vector<Availability> getAvailability() const;


        void setEmail(std::string tempEmail);
        void setName(std::string tempName);


        void addAvailability(const std::string& day, const std::string& time);


        void DisplayCustomerSupportInfo();

        
        virtual void executeTask() override
        {
            DisplayCustomerSupportInfo();
        }


    protected:
	    std::string m_Details;
	    std::string m_ContactName;
	    std::string m_ContactEmail;
};

