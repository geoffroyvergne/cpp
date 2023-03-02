#include <util.hpp>

int Util::getPlayerInt(Player player) {
    switch(player) {
        case Player::none :
            return 0;
        break;

        case Player::circle : 
            return 1;
        break;

        case Player::cross : 
            return 2;
        break;
    }
}

std::string Util::getPlayerString(Player player) {
    /*switch(player) {
        case Player::none :
            return "none";
        break;
       
        case Player::circle : 
            return "yellow";
        break;

        case Player::cross : 
            return "red";
        break;         
    }*/

    return "";
}

int Util::getPieceTypeInt(PieceType pieceype) {
    switch(pieceype) {
        case PieceType::none :
            return 0;
        break;       

        case PieceType::black_circle :
            return 1;
        break;

        case PieceType::black_cross :
            return 2;
        break;

        case PieceType::red_circle :
            return 3;
        break;

        case PieceType::red_cross :
            return 4;
        break;
    }
}

std::string Util::getPieceTypeString(PieceType pieceype) {
    /*switch(pieceype) {
         case PieceType::none :
            return "none";
        break;       

        case PieceType::black_circle :
            return "black circle";
        break;

        case PieceType::black_cross :
            return "black cross";
        break;

        case PieceType::red_circle :
            return "red circle";
        break;

        case PieceType::red_cross :
            return "red cross";
        break;
    }*/

    return "";
}
