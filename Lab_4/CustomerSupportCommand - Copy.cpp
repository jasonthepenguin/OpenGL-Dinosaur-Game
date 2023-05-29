#include "CustomerSupportCommand.h"

CustomerSupportCommand::CustomerSupportCommand() : 
    m_Details("Customer Support"), 
    m_ContactName("William Halling"),
    m_ContactEmail("32233703@student.murdoch.edu.au")
{

    addAvailability("Monday",    "12:00 PM - 11:59 PM");
    addAvailability("Tuesday",   "12:00 PM - 11:59 PM");
    addAvailability("Wednesday", "12.00 PM - 11:59 PM");
    addAvailability("Thursday",  "12:00 PM - 11:59 PM");
    addAvailability("Friday",    "12:00 PM - 11:59 PM");
}



std::string CustomerSupportCommand::getEmail() const { return m_ContactEmail; }
std::string CustomerSupportCommand::getName()  const { return m_ContactName; }


std::vector<CustomerSupportCommand::Availability> CustomerSupportCommand::getAvailability() const 
{
    return m_Availability;
}

void CustomerSupportCommand::setEmail(std::string tempEmail) { m_ContactEmail = tempEmail; }
void CustomerSupportCommand::setName(std::string tempName)   { m_ContactName = tempName;   }



void CustomerSupportCommand::addAvailability(const std::string& day, const std::string& time)
{
    Availability availability;
    availability.m_AvailableDays  = day;
    availability.m_AvailableTimes = time;
    m_Availability.push_back(availability);
}



void CustomerSupportCommand::DisplayCustomerSupportInfo()
{
    ImGui::Begin("Customer Support");
    ImGui::Text(("Details: "       + m_Details).c_str());
    ImGui::Text(("Contact Name: "  + m_ContactName).c_str());
    ImGui::Text(("Contact Email: " + m_ContactEmail).c_str());

    ImGui::Text("Availability:");
    for (const auto& availability : m_Availability) 
    {
        ImGui::Text((availability.m_AvailableDays + ": " + availability.m_AvailableTimes).c_str());
    }

    ImGui::End();
}



