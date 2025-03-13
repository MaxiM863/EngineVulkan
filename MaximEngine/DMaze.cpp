#include "DMaze.h"

#include <stdexcept>

namespace Core
{
SquareGrid::SquareGrid(const std::size_t size)
{
	if (size < 1)
	{
		throw std::invalid_argument("Size must be greater than 0");
	}

	cells.resize(size);

	for (std::size_t x {0}; x < size; ++x)
    {        
        cells[x].resize(size);  

        for(std::size_t y {0}; y < size; ++y) {
        
            cells[x][y].resize(size);
        }      
    }
}

SquareGrid::~SquareGrid() noexcept
{
	DeleteCells();
}

Cell* SquareGrid::operator[](const trio& position) noexcept
{
	const auto isValidPosition {ValidateCellPosition(position)};

	return isValidPosition ? cells[position.x][position.y][position.z] : nullptr;
}

const Cell* const SquareGrid::operator[](const trio& position) const noexcept
{
	const auto isValidPosition {ValidateCellPosition(position)};

	return isValidPosition ? cells[position.x][position.y][position.z] : nullptr;
}

void SquareGrid::Initialize()
{
	InstantiateCells();
	SetCellNeighbors();
}

void SquareGrid::Reset() noexcept
{
	const auto size {cells.size()};

	DeleteCells();

	cells.clear();
	cells.resize(size);

    for (std::size_t x {0}; x < size; ++x)
    {
        for(std::size_t y {0}; y < size; ++y) {
        
            cells[x][y].resize(size);
        }

        cells[x].resize(size);        
    }
    

	Initialize();
}

const trio SquareGrid::GetSize() const noexcept
{
	const auto size {cells.size()};
	const auto xSize {static_cast<int>(size)};
	const auto ySize {static_cast<int>(size)};
    const auto zSize {static_cast<int>(size)};

	return {xSize, ySize, zSize};
}

bool SquareGrid::ValidateCellPosition(const trio& position) const noexcept
{
	const auto [xPosition, yPosition, zPosition] {position};
	const auto size {cells.size()};

	if (xPosition < 0 || xPosition >= size || yPosition < 0 || yPosition >= size || zPosition < 0 || zPosition >= size)
	{
		return false;
	}

	return true;
}

void SquareGrid::InstantiateCells()
{
	const auto size {cells.size()};

	for (std::size_t x {0}; x < size; ++x)
	{
		for (std::size_t y {0}; y < size; ++y)
		{
            for (std::size_t z {0}; z < size; ++z)
            {
                const auto xPosition {static_cast<int>(x)};
                const auto yPosition {static_cast<int>(y)};
                const auto zPosition {static_cast<int>(z)};
                cells[x][y][z] = new Cell {xPosition, yPosition, zPosition};
            }
        }
	}
}

void SquareGrid::SetCellNeighbors() noexcept
{
	const auto size {cells.size()};

	for (std::size_t x {0}; x < size; ++x)
	{
		for (std::size_t y {0}; y < size; ++y)
		{
            for (std::size_t z {0}; z < size; ++z)
            {
                auto* const cell {cells[x][y][z]};

                if (y < size - 1)
                {
                    cell->SetNorth(cells[x][y + 1][z]);
                }

                if (x > 0)
                {
                    cell->SetWest(cells[x - 1][y][z]);
                }

                if (y > 0)
                {
                    cell->SetSouth(cells[x][y - 1][z]);
                }

                if (x < size - 1)
                {
                    cell->SetEast(cells[x + 1][y][z]);
                }

                if (z > 0)
                {
                    cell->SetUp(cells[x][y][z-1]);
                }

                if (z < size - 1)
                {
                    cell->SetDown(cells[x][y][z+1]);
                }
            }
        }
	}
}

void SquareGrid::DeleteCells() noexcept
{
	const auto size {cells.size()};

	for (std::size_t x {0}; x < size; ++x)
	{
		for (std::size_t y {0}; y < size; ++y)
		{
            for (std::size_t z {0}; z < size; ++z)
            {
                delete cells[x][y][z];
            }
        }
	}
}
}