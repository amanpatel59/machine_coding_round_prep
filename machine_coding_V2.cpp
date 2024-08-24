#include <bits/stdc++.h>
using namespace std;
bool turn = 1;
vector<vector<string>> chessBoard(8,vector<string>(8,"--"));

class Board{
public:
    static void startNewGame(){
        for(int col = 0 ; col < 8 ; col++){
            chessBoard[6][col] = "BP";
            chessBoard[1][col] = "WP";
        }

        chessBoard[0][0] = chessBoard[0][7] = "WR";
        chessBoard[0][1] = chessBoard[0][6] = "WN";
        chessBoard[0][2] = chessBoard[0][5] = "WB";
        chessBoard[0][3] = "WQ";
        chessBoard[0][4] = "WK";
        chessBoard[7][0] = chessBoard[7][7] = "BR";
        chessBoard[7][1] = chessBoard[7][6] = "BN";
        chessBoard[7][2] = chessBoard[7][5] = "BB";
        chessBoard[7][3] = "BQ";
        chessBoard[7][4] = "BK";
    }

    static void showBoard(){
        for(int row = 0 ; row < 8 ; row++){
            for(int col = 0 ; col < 8 ;col++){
                cout<<" "<<chessBoard[row][col]<<" ";
            }
            cout<<endl;
        }
        cout<<"==============================================="<<endl;
    }

    static string givePiece(string position){
        int col = position[0]-'a';
        int row = (position[1]-'0')-1;
        return chessBoard[row][col];
    }
};


// class Pieces{
// public:
//     virtual void moveValidator(string start , string end) = 0;
// };

class CheckMate{
public:
    static void checkMateDetector(string end){
        char piece = Board::givePiece(end)[1];
        if(piece == 'K'){
            if(turn)cout<<"White Wins !"<<endl;
            else cout<<"Black Wins !"<<endl;
            exit(0);
        }
    }
};

class InvalidMoves{
public:
    static bool checkForInValid(string start , string end){
        if(start == end){
            cout<<"INVALID MOVE"<<endl;
            return 1;
        }
        string startPieceWithColor = Board::givePiece(start);
        string endPieceWithColor = Board::givePiece(end);
        if((turn == 1 and startPieceWithColor[0] == 'B') or (turn == 0 and startPieceWithColor[0] == 'W')){
            cout<<"INVALID MOVE"<<endl;
            return 1;
        }
        if(startPieceWithColor[0] == endPieceWithColor[0]){
            cout<<"INVALID MOVE"<<endl;
            return 1;
        }
        return 0;
    }
};




class Pawn {
public:
    static void movePawn(string start, string end) {
        if (InvalidMoves::checkForInValid(start, end)) return;

        int startCol = start[0] - 'a', startRow = (start[1] - '0') - 1;
        int endCol = end[0] - 'a', endRow = (end[1] - '0') - 1;

        char pawnColor = Board::givePiece(start)[0];

        if (pawnColor == 'W') { 
            if (startCol == endCol && endRow == startRow + 1 && chessBoard[endRow][endCol] == "--") {
                chessBoard[endRow][endCol] = Board::givePiece(start);
                chessBoard[startRow][startCol] = "--";
                turn = !turn;
                Board::showBoard();
                return;
            }
            
            if (startRow == 1 && startCol == endCol && endRow == 3 && chessBoard[endRow][endCol] == "--" && chessBoard[2][endCol] == "--") {
                chessBoard[endRow][endCol] = Board::givePiece(start);
                chessBoard[startRow][startCol] = "--";
                turn = !turn;
                Board::showBoard();
                return;
            }
            
            if (abs(startCol - endCol) == 1 && endRow == startRow + 1 && chessBoard[endRow][endCol] != "--" && Board::givePiece(end)[0] == 'B') {
                chessBoard[endRow][endCol] = Board::givePiece(start);
                chessBoard[startRow][startCol] = "--";
                turn = !turn;
                Board::showBoard();
                return;
            }
        } else { 
            
            if (startCol == endCol && endRow == startRow - 1 && chessBoard[endRow][endCol] == "--") {
                chessBoard[endRow][endCol] = Board::givePiece(start);
                chessBoard[startRow][startCol] = "--";
                turn = !turn;
                Board::showBoard();
                return;
            }
            
            if (startRow == 6 && startCol == endCol && endRow == 4 && chessBoard[endRow][endCol] == "--" && chessBoard[5][endCol] == "--") {
                chessBoard[endRow][endCol] = Board::givePiece(start);
                chessBoard[startRow][startCol] = "--";
                turn = !turn;
                Board::showBoard();
                return;
            }
            
            if (abs(startCol - endCol) == 1 && endRow == startRow - 1 && chessBoard[endRow][endCol] != "--" && Board::givePiece(end)[0] == 'W') {
                chessBoard[endRow][endCol] = Board::givePiece(start);
                chessBoard[startRow][startCol] = "--";
                turn = !turn;
                Board::showBoard();
                return;
            }
        }

        cout << "INVALID MOVE P" << endl;
    }
};
class Knight {
public:
    static void moveKnight(string start, string end) {
        if (InvalidMoves::checkForInValid(start, end)) return;

        int rowChanges[] = {2, 1, -1, -2, -2, -1, 1, 2};
        int colChanges[] = {1, 2, 2, 1, -1, -2, -2, -1};
        int startCol = start[0] - 'a', startRow = (start[1] - '0') - 1;
        int endCol = end[0] - 'a', endRow = (end[1] - '0') - 1;

        // Check all possible knight moves
        for (int i = 0; i < 8; i++) {
            int newRow = startRow + rowChanges[i];
            int newCol = startCol + colChanges[i];
            if (newRow == endRow && newCol == endCol) {
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    // Valid knight move
                    CheckMate::checkMateDetector(end);
                    chessBoard[endRow][endCol] = Board::givePiece(start);
                    chessBoard[startRow][startCol] = "--";
                    turn = !turn;
                    Board::showBoard();
                    return;
                }
            }
        }

        cout << "INVALID MOVE N" << endl;
    }
};


class Bishop {
public:
    static void moveBishop(string start, string end) {
        if (InvalidMoves::checkForInValid(start, end)) return;

        int startCol = start[0] - 'a', startRow = (start[1] - '0') - 1;
        int endCol = end[0] - 'a', endRow = (end[1] - '0') - 1;

        if (abs(startCol - endCol) != abs(startRow - endRow)) {
            cout << "INVALID MOVE B" << endl;
            return;
        }

        int rowChange = (endRow > startRow) ? 1 : -1;
        int colChange = (endCol > startCol) ? 1 : -1;
        int row = startRow, col = startCol;

        while (row != endRow && col != endCol) {
            row += rowChange;
            col += colChange;

            if (row == endRow && col == endCol) {
                if (chessBoard[row][col] == "--" || Board::givePiece(end)[0] != Board::givePiece(start)[0]) {
                    CheckMate::checkMateDetector(end);
                    chessBoard[endRow][endCol] = Board::givePiece(start);
                    chessBoard[startRow][startCol] = "--";
                    turn = !turn;
                    Board::showBoard();
                    return;
                } else {
                    cout << "INVALID MOVE B" << endl;
                    return;
                }
            } else if (chessBoard[row][col] != "--") {
                cout << "INVALID MOVE B" << endl;
                return;
            }
        }
    }
};


class King{
public:
    static void moveKing(string start , string end){
        if(InvalidMoves::checkForInValid(start,end))return;


        int startCol = start[0]-'a' , startRow = (start[1]-'0')-1;
        int endCol = end[0]-'a' , endRow = (end[1]-'0')-1;

        for(int rowChange = -1 ; rowChange <= 1 ; rowChange++){
            for(int colChange = -1 ; colChange <= 1 ; colChange++){
                int newRow = startRow + rowChange , newCol = startCol + colChange;
                if(newRow >= 0 and newRow < 8 and newCol >= 0 and newCol < 8 and newRow == endRow and newCol == endCol){
                    CheckMate::checkMateDetector(end);
                    chessBoard[endRow][endCol] = Board::givePiece(start);
                    chessBoard[startRow][startCol] = "--";
                    turn = !turn;
                    Board::showBoard();
                    return;
                }
            }
        }
        cout<<"INVALID MOVE K"<<endl;
    }
};

class Rook{
public:
    static void moveRook(string start , string end){
        if(InvalidMoves::checkForInValid(start,end))return;

        int startCol = start[0]-'a' , startRow = (start[1]-'0')-1;
        int endCol = end[0]-'a' , endRow = (end[1]-'0')-1;

        if(startCol < 0 or startRow < 0 or endCol >= 8 or endCol >= 8){
            cout<<"INVALID MOVE R"<<endl;
            return;
        }

        if(startRow != endRow and startCol != endCol){
            cout<<"INVALID MOVE R"<<endl;
            return;
        }
        
        int rowStep = (endRow > startRow) ? 1 : -1;
        int colStep = (endCol > startCol) ? 1 : -1;
        // horizontal move ahead
        if(startRow == endRow){
            for (int col = startCol + colStep; col != endCol; col += colStep) {
                if (chessBoard[startRow][col] != "--") {
                    cout << "INVALID MOVE R" << endl;
                    return;
                }
            }
        }


        // vertical Move
        if(startCol == endCol){
            for(int row = startRow+rowStep ; row != endRow ; row+rowStep){
                if (chessBoard[row][startCol] != "--") {
                    cout << "INVALID MOVE R" << endl;
                    return;
                }
            }
        }
        CheckMate::checkMateDetector(end);
        chessBoard[endRow][endCol] = Board::givePiece(start);
        chessBoard[startRow][startCol] = "--";
        turn = !turn;
        Board::showBoard();
    }
};



class Queen {
public:
    static void moveQueen(string start, string end) {
        if (InvalidMoves::checkForInValid(start, end)) return;

        int startCol = start[0] - 'a', startRow = (start[1] - '0') - 1;
        int endCol = end[0] - 'a', endRow = (end[1] - '0') - 1;

        // for rook-like movement (straight lines)
        if (startRow == endRow || startCol == endCol) {
            Rook::moveRook(start, end);
            return;
        }

        // for bishop-like movement (diagonals)
        if (abs(startCol - endCol) == abs(startRow - endRow)) {
            Bishop::moveBishop(start, end);
            return;
        }

        // If neither rook-like nor bishop-like movement is valid
        cout << "INVALID MOVE Q" << endl;
    }
};




class MatchManager{
private:
    string start , end;
public:
    MatchManager(string start , string end) : start(start) , end(end){}

    void setMovement(string start , string end){
        start = start;
        end = end;
        int startCol = start[0]-'a' , startRow = (start[1]-'0')-1;
        int endCol = end[0]-'a' , endRow = (end[1]-'0')-1;

        string pieceWithColor = Board::givePiece(start);
        string endP = Board::givePiece(end);
        char piece = pieceWithColor[1];

        // cout<<"the piece is = "<<piece<<endl;
        // cout<<"start = "<<start<<"  piece is = "<<pieceWithColor<<endl;
        // cout<<"end = "<<end<<" piece is = "<<endP<<endl;
        // cout<<" start row , col "<<startRow<<" , "<<startCol<<endl;
        // cout<<" end row , col "<<endRow<<" , "<<endCol<<endl;

        switch (piece) {
            case 'P': // Pawn
                Pawn::movePawn(start, end);
                break;
            case 'Q': // Queen
                Queen::moveQueen(start, end);
                break;
            case 'R': // Rook
                Rook::moveRook(start, end);
                break;
            case 'B': // Bishop
                Bishop::moveBishop(start, end);
                break;
            case 'N': // Knight
                Knight::moveKnight(start, end);
                break;
            case 'K': // King
                King::moveKing(start, end);
                break;
            default:
                cout << "Unknown piece: " << piece << endl;
                break;
        }
    }
};



// vector<vector<string>> chessBoard(8,vector<string>(8,"--"));

int main(){
    cout<<"Game is starting , at any point write 'end' to end the game"<<endl<<"white starts the game"<<endl<<endl;
    Board::startNewGame();
    Board::showBoard();
    MatchManager* match = new MatchManager("","");

    while(true){
        string start , end;
        cin>>start>>end;
        if(start == end)break;
        match->setMovement(start,end);
    }
    return 0;
}