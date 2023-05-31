#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "Menu_Command.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



/***************************************************************************************************************
 * @brief : CustomerSupportCommand
 * @brief : represents a command for displaying customer support details.
 *          It provides functionality for displaying customer support details such as contact name, email, and availability.
 *          It also allows adding availability for different days and times.
 *          This class is derived from Menu_Commands interface for integration with the pause menu system.
 * 
 * 
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class CustomerSupport_Command : public Menu_Command
{
    private:

            /********************************************************************************************************
             * @brief : Availability Struct 
             * @brief : customer support for a specific tempDay and tempTime.
             ********************************************************************************************************/
       
        struct Availability 
        {
            std::string m_AvailableDays;  /// The available days 
            std::string m_AvailableTimes; /// The available times
        };

        std::vector<Availability> m_Availability;


    public:

            /*****************************************************************************************************************************
             * @brief : CustomerSupportCommand
             * @brief : Object for the CustomerSupport Command Constructs a new CustomerSupportCommand object with default values.
             *****************************************************************************************************************************/
        
        CustomerSupport_Command();


        ~CustomerSupport_Command() override = default;


            /******************************************************************************************************************************
             * @breif : getEmail() 
             * @brief : Used to get the customers email
             ******************************************************************************************************************************/
        
        std::string getEmail() const;


            /*******************************************************************************************************************************
			 * @brief Constructs a new CustomerSupportCommand object with default values.
			 *******************************************************************************************************************************/

        std::string getName() const;


            /*******************************************************************************************************************************
             * @brief getAvailability()
             * @brief Used to get the availability of customer support, hours and days
             * 
             * @rerturn : m_Availability std::vector<Availability>
             *******************************************************************************************************************************/

        std::vector<Availability> getAvailability() const;


            /*******************************************************************************************************************************
             * @brief  : setEmail() 
             * @brief  : Constructs a new CustomerSupportCommand object with default values.
             * 
             * @param  : tempEmail std::string
             * @return : void
             ******************************************************************************************************************************/

        void setEmail(const std::string& tempEmail);


            /********************************************************************************************************************************
             * @brief  : setName()
             * @brief  : Constructs a new CustomerSupportCommand object with default values.
             * 
             * @param  : tempName std::string 
             * @return : void
             ********************************************************************************************************************************/

        void setName(const std::string& tempName);


            /*********************************************************************************************************************************
             * @brief  : addAvailability()
             * @brief  : Is used to add customer support availability in terms of hours and days 
             * 
             * @param  : tempDay std::string
             * @param  : tempTime std::string
             * 
             * @return : void
             *********************************************************************************************************************************/

        void addAvailability(const std::string& tempDay, const std::string& tempTime);


            /**********************************************************************************************************************************
             * @breif  : DisplayCustomerSupportInfo()
             * @brief  : Is used to display the time and days customer support is available
             * 
             * @return : void
             **********************************************************************************************************************************/

        void displayCustomerSupportInfo() const;


            /***********************************************************************************************************************************
             * @brief : executeTask() 
             * @brief : is used to execute the task of displaying customer support availably
             ***********************************************************************************************************************************/

        virtual void executeTask() override;


    protected:
	    std::string m_Details;
	    std::string m_ContactName;
	    std::string m_ContactEmail;

    private:
        bool m_DisplaySupport = false;
        std::shared_ptr<Back_Command> m_BackButton;
       
};

