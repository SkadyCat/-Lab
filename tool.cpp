#include "tool.h"
#include <Qt>

Tool* Tool::ins = NULL;
Tool::Tool()
{

    ins = this;


}

Tool* Tool::Instance(){


    return ins;
}
