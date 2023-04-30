#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "GameObject.h"

namespace dae
{
	
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;
	};
}
#pragma once