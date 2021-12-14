#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <QDebug>

class ChessPlayer
{
public:
    enum Color { BLACK, RED, NONE };
    ChessPlayer(Color color): _color(color) {}
    ChessPlayer(const ChessPlayer& other): _color(other._color) {}
    inline bool operator==(const ChessPlayer& other) const {
        return _color == other._color;
    }
    inline bool operator==(Color color) const {
        return _color == color;
    }
    inline bool operator!=(const ChessPlayer& other) const {
        return _color != other._color;
    }
    inline bool operator!=(Color color) const {
        return _color != color;
    }
    inline void next(){ _color = Color(!_color); }
    inline operator Color(){ return _color; }
    inline ChessPlayer& operator=(ChessPlayer other) { return this->_color = other._color, *this; }
private:
    Color _color;
};

#endif // CHESSPLAYER_H
