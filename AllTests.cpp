/**
 * @file Alltests.cpp
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-10-31
 *
 * @copyright Copyright (c) 2024
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "CppUTest/CommandLineTestRunner.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    Macro
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    variables(external)
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	return CommandLineTestRunner::RunAllTests(argc, argv);
	return 0;
}