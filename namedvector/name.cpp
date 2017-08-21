#include "name.h"

int Name::names_in_memory = 0;

Name* Name::copy(const Name* name)
{
    return new Name(*name);
}
