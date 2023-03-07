#include <util.hpp>

int Util::getPlayerInt(Player player) {
    switch(player) {
        case Player::none :
            return 0;
        break;

        case Player::yellow : 
            return 1;
        break;

        case Player::red : 
            return 2;
        break;
    }
}

std::string Util::getPlayerString(Player player) {
    switch(player) {
        case Player::none :
            return "none";
        break;

        case Player::yellow : 
            return "yellow";
        break;

        case Player::red : 
            return "red";
        break;
    }
}

int Util::getPieceTypeInt(PieceType pieceype) {
    switch(pieceype) {
        case PieceType::none :
            return 0;
        break;

        case PieceType::yellow :
            return 1;
        break;

        case PieceType::red :
            return 2;
        break;
    }
}

std::string Util::getPieceTypeString(PieceType pieceype) {
    switch(pieceype) {
        case PieceType::none :
            return "none";
        break;

        case PieceType::yellow :
            return "yellow";
        break;

        case PieceType::red :
            return "red";
        break;
    }
}

std::string Util::getPieceTypeSimpleString(PieceType pieceype) {
    switch(pieceype) {
        case PieceType::none :
            return "n";
        break;

        case PieceType::yellow :
            return "y";
        break;

        case PieceType::red :
            return "r";
        break;
    }
}