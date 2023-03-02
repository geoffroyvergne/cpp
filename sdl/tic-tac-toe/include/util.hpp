#include <iostream>
#include <piece_type.hpp>
#include <player.hpp>

#ifndef UTIL
#define UTIL

class Util {
    public:
        static int getPlayerInt(Player player);
        static std::string getPlayerString(Player player);

        static int getPieceTypeInt(PieceType pieceype);
        static std::string getPieceTypeString(PieceType pieceype);
};

#endif
