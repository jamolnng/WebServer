#include "plugin.h"

using namespace webserver::plugin;

Plugin::Plugin(std::string name) :
	name(name)
{
}

const std::string& Plugin::getName() const
{
	return name;
}