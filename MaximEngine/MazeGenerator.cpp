#include "MazeGenerator.h"

namespace Core
{
MazeGenerator::MazeGenerator(const std::string_view algorithmName) noexcept :
	algorithmName {algorithmName}
{
}

const std::string& MazeGenerator::GetAlgorithmName() const noexcept
{
	return algorithmName;
}

std::optional<uint64_t> MazeGenerator::GetSeed() const noexcept
{
	return seedGenerator.GetSeed();
}

const std::mt19937_64& MazeGenerator::GetRandomEngine(const std::optional<uint64_t>& seed) noexcept
{
	return seedGenerator.GetRandomEngine(seed);
}
}