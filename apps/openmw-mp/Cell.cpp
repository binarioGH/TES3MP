//
// Created by koncord on 18.02.17.
//

#include "Cell.hpp"

#include <iostream>
#include "Player.hpp"

using namespace std;

void Cell::addPlayer(Player *player)
{
    auto it = find(player->cells.begin(), player->cells.end(), this);
    if(it == player->cells.end())
        player->cells.push_back(this);
    players.push_back(player);
}

void Cell::removePlayer(Player *player)
{
    for(Iterator it = begin(); it != end(); it++)
    {
        if(*it == player)
        {
            auto it2 = find(player->cells.begin(), player->cells.end(), this);
            if(it2 != player->cells.end())
                player->cells.erase(it2);
            players.erase(it);
            return;
        }

    }

}

Cell::TPlayers Cell::getPlayers()
{
    return players;
}

CellController::CellController()
{

}

CellController::~CellController()
{

}

CellController *CellController::sThis = nullptr;

void CellController::create()
{
    sThis = new CellController;
}

void CellController::destroy()
{
    assert(sThis);
    delete sThis;
    sThis = nullptr;
}

CellController *CellController::get()
{
    return sThis;
}

Cell *CellController::getCellByXY(int x, int y)
{
    auto it = find_if(cells.begin(), cells.end(), [x, y](const Cell *c) {
        return c->cell.mData.mX == x && c->cell.mData.mY == y;
    });
    if(it == cells.end())
        return nullptr;
    return *it;
}

Cell *CellController::getCellByID(std::string cellid)
{
    auto it = find_if(cells.begin(), cells.end(), [cellid](const Cell *c) {
        return c->cell.mName == cellid;
    });
    if(it == cells.end())
        return nullptr;
    return *it;
}

Cell *CellController::addCell(ESM::Cell cellData)
{
    
    LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Loaded cells: %d", cells.size());
    auto it = find_if(cells.begin(), cells.end(), [cellData](const Cell *c) {
        //return c->cell.sRecordId == cellData.sRecordId; // Currently we cannot compare because plugin lists can be loaded in different order
        return c->cell.mData.mX == cellData.mData.mX && c->cell.mData.mY == cellData.mData.mY &&
                c->cell.mCellId.mWorldspace == cellData.mCellId.mWorldspace;
    });
    Cell *cell;
    if(it == cells.end())
    {
        cell = new Cell(cellData);
        cells.push_back(cell);
    }
    else
        cell = *it;
    return cell;


}

void CellController::removeCell(Cell *cell)
{
    if(cell == nullptr)
        return;
    for (auto it = cells.begin(); it != cells.end();)
    {
        if(*it != nullptr && *it == cell)
        {
            delete *it;
            it = cells.erase(it);
        }
        else
            ++it;
    }
}

void CellController::removePlayer(Cell *cell, Player *player)
{

    cell->removePlayer(player);

    if(cell->players.empty())
    {
        auto it = find(cells.begin(), cells.end(), cell);
        delete *it;
        cells.erase(it);
    }
}

void CellController::update(Player *player)
{
    for(auto cell : player->cellStateChanges.cellStates)
    {
        if(cell.type == mwmp::CellState::LOAD)
        {
            Cell *c = addCell(cell.cell);
            c->addPlayer(player);
        }
        else
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Unload cell: %d %d %s", cell.cell.mData.mX, cell.cell.mData.mY, cell.cell.mName.c_str());
            Cell *c;
            if(!cell.cell.isExterior())
                c = getCellByID(cell.cell.mName);
            else
                c = getCellByXY(cell.cell.getGridX(), cell.cell.getGridY());

            if(c != nullptr)
                removePlayer(c, player);
        }
    }
}

Cell::Cell(ESM::Cell cell): cell(cell)
{

}

Cell::Iterator Cell::begin()
{
    return players.begin();
}

Cell::Iterator Cell::end()
{
    return players.end();
}
