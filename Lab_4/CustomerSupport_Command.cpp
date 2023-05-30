#include "CustomerSupport_Command.h"
#include <iostream>
#include "imgui.h"


CustomerSupport_Command::CustomerSupport_Command()
	: m_Details("Customer Support"),
	m_ContactName("William Halling"),
	m_ContactEmail("32233703@student.murdoch.edu.au")
{
	addAvailability("Monday", "12:00 PM - 11:59 PM");
	addAvailability("Tuesday", "12:00 PM - 11:59 PM");
	addAvailability("Wednesday", "12.00 PM - 11:59 PM");
	addAvailability("Thursday", "12:00 PM - 11:59 PM");
	addAvailability("Friday", "12:00 PM - 11:59 PM");
}


std::string CustomerSupport_Command::getEmail() const
{
	return m_ContactEmail;
}


std::string CustomerSupport_Command::getName() const
{
	return m_ContactName;
}


std::vector<CustomerSupport_Command::Availability> CustomerSupport_Command::getAvailability() const
{
	return m_Availability;
}


void CustomerSupport_Command::setEmail(const std::string& tempEmail)
{
	m_ContactEmail = tempEmail;
}


void CustomerSupport_Command::setName(const std::string& tempName)
{
	m_ContactName = tempName;
}


void CustomerSupport_Command::addAvailability(const std::string& day, const std::string& time)
{
	Availability availability;
	availability.m_AvailableDays  = day;
	availability.m_AvailableTimes = time;
	m_Availability.push_back(availability);
}


void CustomerSupport_Command::displayCustomerSupportInfo() const
{
	ImGui::Begin("Customer Support");
	ImGui::Text(("Details: " + m_Details).c_str());
	ImGui::Text(("Contact Name: " + m_ContactName).c_str());
	ImGui::Text(("Contact Email: " + m_ContactEmail).c_str());
	ImGui::Text("Availability:");


	for (const auto& availability : m_Availability)
	{
		ImGui::Text((availability.m_AvailableDays + ": " + availability.m_AvailableTimes).c_str());
	}

	ImGui::End();
}


void CustomerSupport_Command::executeTask()
{
	if (ImGui::Button("Customer Support"))
	{
		displayCustomerSupportInfo();
	}
}
