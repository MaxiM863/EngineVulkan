#pragma once

#include <optional>
#include <random>
#include <string>

#include "IGrid.h"
#include "SeedGenerator.h"

namespace Core
{
/**
 * @brief The base class for all maze generators.
 * @class MazeGenerator
 */
class MazeGenerator
{
protected:
	/**
	 * @brief Instantiates a new maze generator with the given algorithm name.
	 * @param algorithmName The name of the algorithm used by the maze generator.
	 */
	explicit MazeGenerator(const std::string_view algorithmName) noexcept;

	/**
	 * @brief Instantiates a new maze generator by copying the given maze generator.
	 * @param other The maze generator to copy.
	 */
	MazeGenerator(const MazeGenerator& other) noexcept = default;

	/**
	 * @brief Instantiates a new maze generator by moving the given maze generator.
	 * @param other The maze generator to move.
	 */
	MazeGenerator(MazeGenerator&& other) noexcept = default;

public:
	/**
	 * @brief Destroys the maze generator.
	 */
	virtual ~MazeGenerator() noexcept = default;

public:
	/**
	 * @brief Assigns the given maze generator to this maze generator using copy semantics.
	 * @param other The maze generator to copy.
	 * @return A reference to this maze generator.
	 */
	MazeGenerator& operator=(const MazeGenerator& other) noexcept = default;

	/**
	 * @brief Assigns the given maze generator to this maze generator using move semantics.
	 * @param other The maze generator to move.
	 * @return A reference to this maze generator.
	 */
	MazeGenerator& operator=(MazeGenerator&& other) noexcept = default;

public:
	/**
	 * @brief Modifies the given grid to Generate a maze.
	 * @param grid The grid to modify.
	 * @param seed The seed to use for the random number generator. If no seed is provided, a random seed will be
	 * generated.
	 */
	virtual void Generate(IGrid* const grid, const std::optional<uint64_t>& seed) noexcept = 0;

	/**
	 * @brief Gets a const reference to the name of the algorithm used by the maze generator.
	 * @return A const reference to the name of the algorithm used by the maze generator.
	 */
	[[nodiscard]] const std::string& GetAlgorithmName() const noexcept;

	/**
	 * @brief Gets the seed used by the maze generator.
	 * @return The seed used by the maze generator.
	 */
	[[nodiscard]] std::optional<uint64_t> GetSeed() const noexcept;

protected:
	/**
	 * @brief Gets a const reference to the random number generator.
	 * @param seed The seed to use for the random number generator. If no seed is provided, a random seed will be
	 * generated.
	 * @return A const reference to the random number generator.
	 */
	const std::mt19937_64& GetRandomEngine(const std::optional<uint64_t>& seed) noexcept;

private:
	std::string algorithmName;
	SeedGenerator seedGenerator;
};
}