#pragma once

#include "Cell.h"

namespace Core
{
/**
 * @brief An interface for a grid of cells.
 * @class IGrid
 */

struct trio {

    int x;
    int y;
    int z;
};


class IGrid
{
public:
	IGrid() noexcept = default;
	IGrid(const IGrid& other) noexcept = default;
	IGrid(IGrid&& other) noexcept = default;

	/**
	 * @brief Destroys the grid.
	 */
	virtual ~IGrid() noexcept = default;

public:
	IGrid& operator=(const IGrid& other) noexcept = default;
	IGrid& operator=(IGrid&& other) noexcept = default;

public:
	/**
	 * @brief Gets a pointer to the cell at the given (x, y) position.
	 * @param position The (x, y) position of the cell.
	 * @return A pointer to the cell at the given (x, y) position.
	 */
	virtual Cell* operator[](const trio& position) noexcept = 0;

	/**
	 * @brief Gets a const pointer to the const cell at the given (x, y) position.
	 * @param position The (x, y) position of the cell.
	 * @return A const pointer to the const cell at the given (x, y) position.
	 */
	virtual const Cell* const operator[](const trio& position) const noexcept = 0;

public:
	/**
	 * @brief Initializes the grid.
	 * @details This method must be called before using the grid.
	 */
	virtual void Initialize() = 0;

	/**
	 * @brief Gets the x and y sizes of the grid.
	 * @return The x and y sizes of the grid.
	 */
	[[nodiscard]] virtual const trio GetSize() const noexcept = 0;

	/**
	 * @brief Resets the grid.
	 */
	virtual void Reset() noexcept = 0;
};
}