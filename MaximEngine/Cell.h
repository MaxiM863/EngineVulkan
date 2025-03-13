#pragma once

#include <vector>

namespace Core
{
/**
 * @brief A cell in a maze.
 * @class Cell
 */
class Cell
{
public:
	/**
	 * @brief Instantiates a new cell.
	 * @param xPosition The x position of the cell.
	 * @param yPosition The y position of the cell.
	 */
	Cell(int xPosition, int yPosition, int zPosition) noexcept;

	/**
	 * @brief Instantiates a new cell by copying the given cell.
	 * @param cell The cell to copy.
	 */
	Cell(const Cell& cell) noexcept = default;

	/**
	 * @brief Instantiates a new cell by moving the given cell.
	 * @param cell The cell to move.
	 */
	Cell(Cell&& cell) noexcept = default;

	/**
	 * @brief Destroys the cell.
	 */
	~Cell() noexcept = default;

public:
	/**
	 * @brief Assigns the given cell to this cell using copy semantics.
	 * @param cell The cell to copy.
	 * @return A reference to this cell.
	 */
	Cell& operator=(const Cell& cell) noexcept = default;

	/**
	 * @brief Assigns the given cell to this cell using move semantics.
	 * @param cell The cell to move.
	 * @return A reference to this cell.
	 */
	Cell& operator=(Cell&& cell) noexcept = default;

public:
	/**
	 * @brief Links this cell to the given cell.
	 * @param cell The cell to Link to.
	 * @param isBidirectional Whether or not the Link is bidirectional.
	 */
	void Link(Cell* cell, const bool isBidirectional = true) noexcept;

	/**
	 * @brief Unlinks this cell from the given cell.
	 * @param cell The cell to Unlink from.
	 * @param isBidirectional Whether or not the Link is bidirectional.
	 */
	void Unlink(Cell* cell, const bool isBidirectional = true) noexcept;

	/**
	 * @brief Checks if this cell is linked to the given cell.
	 * @param cell The cell to check.
	 * @return True if this cell is linked to the given cell, false otherwise.
	 */
	[[nodiscard]] bool GetIsLinked(const Cell* const cell) const noexcept;

	/**
	 * @brief Gets the links of this cell.
	 * @return The links of this cell.
	 */
	[[nodiscard]] const std::vector<Cell*>& GetLinks() const noexcept;

	/**
	 * @brief Gets the x position of this cell.
	 * @return The x position of this cell.
	 */
	[[nodiscard]] int GetXPosition() const noexcept;

	/**
	 * @brief Gets the y position of this cell.
	 * @return The y position of this cell.
	 */
	[[nodiscard]] int GetYPosition() const noexcept;


    [[nodiscard]] int GetZPosition() const noexcept;

	/**
	 * @brief Gets the neighbors of this cell.
	 * @details The order of the neighbors is north, west, south, east. If a neighbor does not exist, then it will not
	 * be included in the returned vector.
	 * @return The neighbors of this cell.
	 */
	[[nodiscard]] std::vector<Cell*> GetNeighbors() const noexcept;

	/**
	 * @brief Gets a pointer to the cell to the north of this cell.
	 * @return A pointer to the cell to the north of this cell.
	 */
	[[nodiscard]] Cell* GetNorth() const noexcept;

	/**
	 * @brief Gets a pointer to the cell to the west of this cell.
	 * @return A pointer to the cell to the west of this cell.
	 */
	[[nodiscard]] Cell* GetWest() const noexcept;

	/**
	 * @brief Gets a pointer to the cell to the south of this cell.
	 * @return A pointer to the cell to the south of this cell.
	 */
	[[nodiscard]] Cell* GetSouth() const noexcept;

	/**
	 * @brief Gets a pointer to the cell to the east of this cell.
	 * @return A pointer to the cell to the east of this cell.
	 */
	[[nodiscard]] Cell* GetEast() const noexcept;

    [[nodiscard]] Cell* GetDown() const noexcept;

    [[nodiscard]] Cell* GetUp() const noexcept;

	/**
	 * @brief Sets the cell to the north of this cell.
	 * @param cell A pointer to the cell to the north of this cell.
	 */
	void SetNorth(Cell* cell) noexcept;

	/**
	 * @brief Sets the cell to the west of this cell.
	 * @param cell A pointer to the cell to the west of this cell.
	 */
	void SetWest(Cell* cell) noexcept;

	/**
	 * @brief Sets the cell to the south of this cell.
	 * @param cell A pointer to the cell to the south of this cell.
	 */
	void SetSouth(Cell* cell) noexcept;

	/**
	 * @brief Sets the cell to the east of this cell.
	 * @param cell A pointer to the cell to the east of this cell.
	 */
	void SetEast(Cell* cell) noexcept;

    void SetDown(Cell* cell) noexcept;

    void SetUp(Cell* cell) noexcept;

private:
	int xPosition;
	int yPosition;
    int zPosition;
	Cell* north{nullptr};
	Cell* west{nullptr};
	Cell* south{nullptr};
	Cell* east{nullptr};
    Cell* down{nullptr};
    Cell* up{nullptr};
	std::vector<Cell*> links;
};
}