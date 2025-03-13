#pragma once

#include <optional>

#include "IGrid.h"
#include "MazeGenerator.h"

namespace Core
{
/**
 * @brief Modifies a grid to Generate a maze using the Wilson's algorithm.
 * @class WilsonsMazeGenerator
 */
class WilsonsMazeGenerator final : public MazeGenerator
{
public:
	/**
	 * @brief Instantiates a new wilson's maze generator.
	 */
	WilsonsMazeGenerator() noexcept;

	/**
	 * @brief Instantiates a new wilson's maze generator by copying the given wilson's maze generator.
	 * @param other The wilson's maze generator to copy.
	 */
	WilsonsMazeGenerator(const WilsonsMazeGenerator& other) noexcept = default;

	/**
	 * @brief Instantiates a new wilson's maze generator by moving the given wilson's maze generator.
	 * @param other The wilson's maze generator to move.
	 */
	WilsonsMazeGenerator(WilsonsMazeGenerator&& other) noexcept = default;

	/**
	 * @brief Destroys the wilson's maze generator.
	 */
	~WilsonsMazeGenerator() noexcept override = default;

public:
	/**
	 * @brief Assigns the given wilson's maze generator to this wilson's maze generator using copy semantics.
	 * @param other The wilson's maze generator to copy.
	 * @return A reference to this wilson's maze generator.
	 */
	WilsonsMazeGenerator& operator=(const WilsonsMazeGenerator& other) noexcept = default;

	/**
	 * @brief Assigns the given wilson's maze generator to this wilson's maze generator using move semantics.
	 * @param other The wilson's maze generator to move.
	 * @return A reference to this wilson's maze generator.
	 */
	WilsonsMazeGenerator& operator=(WilsonsMazeGenerator&& other) noexcept = default;

public:
	void Generate(IGrid* const grid, const std::optional<uint64_t>& seed) noexcept override;
};
}