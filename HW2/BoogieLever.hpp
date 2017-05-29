//
//  BoogieLever.hpp
//  hw2
//
//  Created by Noam Stolero on 27/05/2017.
//  Copyright © 2017 Noam Stolero. All rights reserved.
//

#ifndef BoogieLever_hpp
#define BoogieLever_hpp

#include "Clerk.hpp"

class BoogieLever {
public:
	// constructor. initializes the graph
	BoogieLever(int len, const char *files[]);

	// run a command prompt with the user
	void run();

private:
	static const int LOAD=1;
	static const int OUTBOUND=2;
	static const int INBOUND=3;
	static const int BALANCE=4;
	static const int PRINT=5;
	static const int EXIT=6;


	/* only one boogieLever allowed */
	BoogieLever(const BoogieLever&)=default;
	BoogieLever(BoogieLever&&)=default;
	BoogieLever& operator=(const BoogieLever&)=default;
	BoogieLever& operator=(BoogieLever&&)=default;

	// contains the received command
	struct Command{
		int cmdNumber;
		string port,date,fileName;

		void setNewCmd(string buffer);
	};

	void init_graphs(int len, const char *files[]);    //build graph using given files.

	Clerk clerk;
};
#endif /* BoogieLever_hpp */
