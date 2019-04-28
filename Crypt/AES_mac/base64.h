/*******************************************************************************
** @file:     base64
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-1-10
** @version:
*******************************************************************************/

#ifndef BASE64_H
#define BASE64_H
#include <string>
std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
#endif // BASE64_H
