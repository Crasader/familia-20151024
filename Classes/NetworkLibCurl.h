//
//  NetworkLibCurl.h
//  Card13
//
//  Created by Hiroki Ariji on 2015/08/23.
//
//

#ifndef __Card13__NetworkLibCurl__
#define __Card13__NetworkLibCurl__

#include <stdio.h>

void Post(const char *command_type);
bool Get(const char *command_type);
std::string Get_data(std::string get_command);

#endif /* defined(__Card13__NetworkLibCurl__) */
