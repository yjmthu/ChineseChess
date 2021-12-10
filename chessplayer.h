#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H


class ChessPlayer
{
public:
    enum Color { BLACK, RED };
    ChessPlayer(Color color): _color(color) {}
    inline ChessPlayer other() { return Color(!_color); }
    inline bool operator!=(const short other) {
        return _color != other;
    }
    inline ChessPlayer& operator++(){
        _color = Color(!_color);
        return *this;
    }
    inline void next(){ _color = Color(!_color);};
private:
    Color _color;
};

#endif // CHESSPLAYER_H
