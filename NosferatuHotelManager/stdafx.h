// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include <SFML\Graphics.hpp>

//Include classes all files need
#include "DebugLogManager.h"

//Create the debug singleton here
extern DebugLogManager debug;