/*
 * Controller.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "View.h"
#include <string>
#include <stdexcept>
#include <fstream>
#include "../Elements/Ship.h"
#include "../Utilities/CommandInfo.h"


using std::ifstream;
using std::string;




class Controller {
public:
	Controller() = default;
	~Controller() = default;

	void initialize(string fileName);
	void run();




	// nested classes
	class OpenFileException: public std::runtime_error{
	public:
		OpenFileException(const std::string& arg):runtime_error(arg){}
	};
	class InputException: public std::runtime_error{
	public:
		InputException(const std::string& arg):runtime_error(arg){}
	};



	private:


	void checkValidity(ifstream& file);
	void create_port(string portDetails);


	void handle_model_cmd(CommandInfo& cmd);
	void handle_view_cmd(CommandInfo& cmd);
	void handle_ship_cmd(CommandInfo& cmd);




	View view;
};

#endif /* CONTROLLER_H_ */
