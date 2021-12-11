#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H


class ChessPlayer
{
public:
    enum Color { BLACK, RED, NONE };
    ChessPlayer(Color color): _color(color) {}
    ChessPlayer(const ChessPlayer& other): _color(other._color) {}
    inline void operator=(const ChessPlayer& other) { _color = other._color; }
    inline ChessPlayer other() const { return Color(!_color); }
    inline bool operator!=(const short other) const {
        return _color != other;
    }
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
    inline ChessPlayer& operator++() {
        _color = Color(!_color);
        return *this;
    }
    inline void next(){ _color = Color(!_color);}
    inline operator Color(){ return _color; }
private:
    Color _color;
};

#endif // CHESSPLAYER_H
