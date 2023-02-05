#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>

using namespace std;

string initPosition = "8/2P4P/1p1B3r/2qn2N1/K6P/2RpbP2/4R1p1/3k4";

#pragma region GRAPHICS
sf::Texture board_tex;
sf::Texture pieces_tex;

sf::RenderWindow window(sf::VideoMode(1000, 1000), "Bamtang Chess");
sf::Sprite board_sp;

//our pieces
const int white = 158;
const int black = 14;

const int king = 10;
const int queen = 177;
const int rook = 345;
const int bishop = 512;
const int knight = 682;
const int pawn = 840;

//how big is a single cell on the board
const int grid_size = 125;

void loadTextures()
{
    //load board
    if (!board_tex.loadFromFile("chess-board.jpg"))
    {
        cout << "Error loading [chess-board.jpg]";
        system("pause");
    }

    //load pieces
    if (!pieces_tex.loadFromFile("chess-pieces.png"))
    {
        cout << "Error loading [chess-pieces.png]";
        system("pause");
    }
}

sf::Sprite getPiece(int piece_type, int piece_color)
{
    sf::Sprite tmp_piece;
    tmp_piece.setTexture(pieces_tex);
    tmp_piece.setTextureRect(sf::IntRect(piece_type, piece_color, 125, 125));
    return tmp_piece;
}

void drawPiece(char c, int x, int y)
{
    int color = isupper(c) ? white : black;
    int type = -1;

    char t = tolower(c);

    switch (t)
    {
    case 'p':
        type = pawn;
        break;
    case 'r':
        type = rook;
        break;
    case 'b':
        type = bishop;
        break;
    case 'n':
        type = knight;
        break;
    case 'q':
        type = queen;
        break;
    case 'k':
        type = king;
        break;
    }

    sf::Sprite myPiece = getPiece(type, color);
    myPiece.setPosition(x, y);
    window.draw(myPiece);

}
#pragma endregion

void populateBoard()
{
    int i = 0;
    int j = 0;

    for (char c : initPosition)
    {
        //check if line break
        if (c == '/')
        {
            i = 0;
            j++;
            continue;
        }
        if (isdigit(c))
        {
            int ia = c - '0';  //this converts c to its actual value, not its ascii code
            i += 1 + (ia - 1);
        }
        if (isalpha(c))
        {
            drawPiece(c, i * grid_size, j * grid_size);
            i++;
        }
    }
}

void drawChessBoard(string initPosition)
{
    //we draw the empty board
    window.draw(board_sp);

    //now we'll process the string with the position of each piece
    populateBoard();
}

int main()
{
    //we'll start this process by loading all the textures we're gonna need
    loadTextures();

    //we'll set the texture for the board
    board_sp.setTexture(board_tex);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //clear window
        window.clear();

        //this'll do the magic
        drawChessBoard(initPosition);

        //show window content
        window.display();
    }

    return 0;
}