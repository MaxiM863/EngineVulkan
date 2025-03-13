#pragma once

#include <optional>
#include <random>

namespace Core
{
/**
 * @brief Generates a seed and a random engine. If a seed is provided, the seed will be used to Generate the random
 * engine. Otherwise, a random seed will be generated and used to Generate the random engine.
 * @class SeedGenerator
 */
class SeedGenerator
{
public:
	/**
	 * @brief Instantiates a new seed generator with no seed.
	 */
	SeedGenerator() noexcept = default;

	/**
	 * @brief Instantiates a new seed generator by copying the given seed generator.
	 * @param other The seed generator to copy.
	 */
	SeedGenerator(const SeedGenerator& other) noexcept = default;

	/**
	 * @brief Instantiates a new seed generator by moving the given seed generator.
	 * @param other The seed generator to move.
	 */
	SeedGenerator(SeedGenerator&& other) noexcept = default;

	/**
	 * @brief Destroys the seed generator.
	 */
	~SeedGenerator() noexcept = default;

public:
	/**
	 * @brief Assigns the given seed generator to this seed generator using copy semantics.
	 * @param other The seed generator to copy.
	 * @return A reference to this seed generator.
	 */
	SeedGenerator& operator=(const SeedGenerator& other) noexcept = default;

	/**
	 * @brief Assigns the given seed generator to this seed generator using move semantics.
	 * @param other The seed generator to move.
	 * @return A reference to this seed generator.
	 */
	SeedGenerator& operator=(SeedGenerator&& other) noexcept = default;

public:
	/**
	 * @brief Gets the seed used to Generate the random engine.
	 * @return The seed used to Generate the random engine.
	 */
	[[nodiscard]] std::optional<uint64_t> GetSeed() const noexcept;

	/**
	 * @brief Gets a const reference to the random engine.
	 * @param seed The seed to use for the random engine. If no seed is provided, a random seed will be generated.
	 * @return A const reference to the random engine.
	 */
	[[nodiscard]] const std::mt19937_64& GetRandomEngine(const std::optional<uint64_t>& seed) noexcept;

private:
	std::optional<uint64_t> seed;
	std::mt19937_64 randomEngine;
};
}