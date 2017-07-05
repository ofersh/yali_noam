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
	Controller();
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


//	void checkValidity(ifstream& file);
	void getPortDetails(string line,string& name,double& x,double& y,int& maxFuel,int& FPH);


	void handle_model_cmd(CommandInfo& cmd);
	void handle_view_cmd(CommandInfo& cmd);
	void handle_ship_cmd(CommandInfo& cmd);


	shared_ptr<View> view;
};

#endif /* CONTROLLER_H_ */
