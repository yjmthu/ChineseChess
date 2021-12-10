#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H


class ChessPlayer
{
public:
    enum Color { BLACK, RED };
    ChessPlayer(Color color): _color(color) {}
    inline ChessPlayer other() { return Color(!_color); }
    bool operator==(const ChessPlayer other) {
        return _color == other._color;
    }
private:
    Color _color;
};

#endif // CHESSPLAYER_H
