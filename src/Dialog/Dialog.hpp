#pragma once

#include <string>

namespace Dialog 
{
	// Asks a yes/no question and returns the response
	bool prompt(std::string message, std::string title = "");
	// Simple dialog
	void message(std::string message, std::string title = "");
}