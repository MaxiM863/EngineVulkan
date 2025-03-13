#include "SeedGenerator.h"

namespace Core
{
std::optional<uint64_t> SeedGenerator::GetSeed() const noexcept
{
	return seed.has_value() ? seed : std::nullopt;
}

const std::mt19937_64& SeedGenerator::GetRandomEngine(const std::optional<uint64_t>& seed) noexcept
{
	if (seed.has_value())
	{
		this->seed = seed;
	}
	else
	{
		std::random_device randomDevice {};
		this->seed = randomDevice();
	}

	randomEngine.seed(this->seed.value());
	return randomEngine;
}
}