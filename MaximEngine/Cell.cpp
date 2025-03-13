#include "Cell.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <ranges>

namespace Core
{
Cell::Cell(int xPosition, int yPosition, int zPosition) noexcept :
	xPosition{xPosition},
	yPosition{yPosition},
    zPosition{zPosition}
{
}

void Cell::Link(Cell* cell, const bool isBidirectional) noexcept
{
	if (GetIsLinked(cell))
	{
		return;
	}

	if (isBidirectional)
	{
		cell->Link(this, false);
	}

	links.push_back(cell);
}

void Cell::Unlink(Cell* cell, const bool isBidirectional) noexcept
{
	if (!GetIsLinked(cell))
	{
		return;
	}

	if (isBidirectional)
	{
		cell->Unlink(this, false);
	}

	links.erase(std::ranges::remove(links, cell).begin(), links.end());
}

bool Cell::GetIsLinked(const Cell* const cell) const noexcept
{
	return std::ranges::find(links, cell) != links.end();
}

const std::vector<Cell*>& Cell::GetLinks() const noexcept
{
	return links;
}

int Cell::GetXPosition() const noexcept
{
	return xPosition;
}

int Cell::GetYPosition() const noexcept
{
	return yPosition;
}

int Cell::GetZPosition() const noexcept
{
	return zPosition;
}

std::vector<Cell*> Cell::GetNeighbors() const noexcept
{
	std::array<Cell*, 6> directions{north, west, south, east, up, down};
	std::vector<Cell*> neighbors{};
	neighbors.reserve(directions.size());

	std::ranges::copy_if(directions,
						 std::back_inserter(neighbors),
						 [](const Cell* const cell)
						 {
							 return cell != nullptr;
						 });

	return neighbors;
}

Cell* Cell::GetNorth() const noexcept
{
	return north;
}

Cell* Cell::GetWest() const noexcept
{
	return west;
}

Cell* Cell::GetSouth() const noexcept
{
	return south;
}

Cell* Cell::GetEast() const noexcept
{
	return east;
}

Cell* Cell::GetUp() const noexcept
{
	return up;
}

Cell* Cell::GetDown() const noexcept
{
	return down;
}

void Cell::SetNorth(Cell* cell) noexcept
{
	north = cell;
}

void Cell::SetWest(Cell* cell) noexcept
{
	west = cell;
}

void Cell::SetSouth(Cell* cell) noexcept
{
	south = cell;
}

void Cell::SetEast(Cell* cell) noexcept
{
	east = cell;
}

void Cell::SetDown(Cell* cell) noexcept
{
	down = cell;
}

void Cell::SetUp(Cell* cell) noexcept
{
	up = cell;
}
}