#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;
//enumeration is creating own type:
//eDir - type name
//STOP,LEFT,UPLEFT,DOWNLEFT,RIGHT,UPRIGHT,DOWNRIGHT - values of type eDir
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

/**
    * @desc - ball class
    * @param int x - starting x position of ball
    *        int y - starting y position of ball
    * @return n/a
*/
class cBall
{
private:
    int x,y;
    int originalX, originalY;
    eDir direction;
public:
    /*
    ---------------------------------------------------------
    Constructor
    ---------------------------------------------------------
    */
    /* *
    * @desc - initiate ball
    * @param int posX - starting X position of ball
    *        int posY - starting Y position of ball
    * @return n/a
    */
    cBall(int posX, int posY)
    {
        originalX = posX;
        originalY = posY;
        x = posX; y = posY;
        direction = STOP;
    }

    /*
    ---------------------------------------------------------
    Functions
    ---------------------------------------------------------
    */

    /**
    * @desc - resets ball position and direction
    * @param n/a
    * @return n/a
    */
    void Reset()
    {
        x = originalX; y = originalY;
        direction = STOP;
    }

    /**
    * @desc - change direction of ball
    * @param eDir d - direction for ball to change to
    * @return n/a
    */
    void changeDirection(eDir d)
    {
        direction = d;
    }

    /**
    * @desc - set random direction for ball
    * @param n/a
    * @return n/a
    */
    void randomDirection()
    {
        direction = (eDir)((rand() % 6) + 1);
    }

    /*
    ---------------------------------------------------------
    Getters
    ---------------------------------------------------------
    */

    /*
    *inline functions: when inline function is called, whole code of the func gets inserted at the point of the func call
    *                  - used for small and commonly used functions as the execution time of the function itself is less than the overhead (calling of the function) time
    *                  - for large functions, the overhead of the function call is insignificant compared to the execution time of the func
    *                   Note: overhead = resources required to set up an operation
    */

    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDir getDirection() { return direction; }
    void Move()
    {
        switch(direction)
        {
            case STOP:
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UPLEFT:
                x--; y--;
                break;
            case DOWNLEFT:
                x--; y++;
                break;
            case UPRIGHT:
                x++; y--;
                break;
            case DOWNRIGHT:
                x++; y++;
                break;
            default:
                break;
        }
    }
    /**
    * @desc - overload << operator to print out ball . the '&' means pass by reference but is used the same was as normal
    * @param ostream &o - reference of object o of o stream class 
    *        cBall c - object of cBall class
    * @return ostream& - returns reference of type ostream
    */
    friend ostream &operator<<(ostream &o, cBall c)
    {
        //prints out ball position in terms of x and y cordinates - i.e. "Ball[1,1]"
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return o; //return o so stream can be continued
    }
};

class cPaddle
{
private:
     int x, y;
     int originalX, originalY;
public:
    cPaddle()
    {
        x = y = 0;
    }
    cPaddle(int posX, int posY) : cPaddle()
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    inline void Reset() { x = originalX; y = originalY; }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }

    friend ostream &operator<<(ostream &o, cPaddle c)
    {
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o; //return o so stream can be continued
    }
};

class cGameManager
{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall * ball;
    cPaddle *player1;
    cPaddle *player2;
public:
    //constructor to initialize window, ball, player, score, key press values
    cGameManager(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        up1 = 'w'; up2 = 'i';
        down1 = 's'; down2 = 'k';
        score1 = score2 = 0;
        width = w; height = h;
        ball = new cBall(w/2, h/2);
        player1 = new cPaddle(1, h/2 - 3);
        player2 = new cPaddle(w - 2, h/2 - 3);
    }

    //destructor for freeing up the dynamic memory created by pointers - prevents memory leak
    ~cGameManager()
    {   
        delete ball, player1, player2;
    }

    void ScoreUp(cPaddle * player)
    {
        if(player == player1)
            score1++;
        else if (player == player2)
            score2++;
        
        //reset positions after someone scores
        ball->Reset();
        player1->Reset();
        player2->Reset();
    };

    //draw function for everything related to drawing wall, player, ball
    void Draw()
    {
        system("cls"); //clear command prompt window
        
        //top wall
        for(int i = 0; i < width + 2; i++)
            cout << '\xB2';
        cout << endl;

        //rows
        for (int i = 0; i < height; i++)
        {
            //column in the current row
            for (int j = 0; j < width; j++)
            {
                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player1y = player1->getY();
                int player2x = player2->getX();
                int player2y = player2->getY();

                //left wall
                if(j == 0)
                    cout << '\xB2'; //hexadecimal code for dark shade char from character set: DOS: Western Europe
                                    //Win+R -> charmap -> advanced view -> character set -> DOS: Western Europe

                if(ballx == j && bally == i)
                    cout << 'O'; //ball
                else if(player1x == j && player1y == i)
                    cout << '\xDB'; //player1 - full block char from character set: DOS: Western Europe
                else if(player1x == j && player1y + 1 == i)
                    cout << '\xDB';
                else if(player1x == j && player1y + 2 == i)
                    cout << '\xDB';
                else if(player1x == j && player1y + 3 == i)
                    cout << '\xDB';
                else if(player2x == j && player2y == i)
                    cout << '\xDB'; //player2 - 4 blocks of it
                else if(player2x == j && player2y + 1 == i)
                    cout << '\xDB';
                else if(player2x == j && player2y + 2 == i)
                    cout << '\xDB';
                else if(player2x == j && player2y + 3 == i)
                    cout << '\xDB';
                else
                    cout << " "; //if space not a wall, ball, or player - then print a blank space
                
                //right wall
                if(j == width - 1)
                    cout << '\xB2';  
            }
            cout << endl; //finished row so go to next line
        }

        //bottom wall
        for(int i = 0; i < width + 2; i++)
            cout << '\xB2';
        cout << endl;

        cout << "Score 1: " << score1 << endl <<  "Score 2: " << score2 << endl;
    }

    //input function for checking keyboard input and performing corresponding logic
    void Input()
    {
        ball->Move();
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player1y = player1->getY();
        int player2x = player2->getX();
        int player2y = player2->getY();

        //keyboard interrupt - keyboard hit
        if (_kbhit())
        {
            //get key hit in char form
            char current = _getch();
            if (current == up1)
                if (player1y > 0)
                    player1->moveUp();
            if (current == up2)
                if (player2y > 0)
                    player2->moveUp();
            if (current == down1)
                if (player1y + 4 < height)
                    player1->moveDown();
            if (current == down2)
                if (player2y + 4 < height)
                    player2->moveDown();

            if (ball->getDirection() == STOP)
                ball->randomDirection();  //to start the game (ball goes in rand dir)
            
            if (current == 'q')
                quit = true; //quit game
        }
    }

    //collision detection logic (wall, paddle)
    void Logic()
    {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player1y = player1->getY();
        int player2x = player2->getX();
        int player2y = player2->getY();

        //left paddle
        for (int i = 0; i < 4; i++)
            if(ballx == player1x + 1)
                if (bally == player1y + i)
                ball->changeDirection((eDir)((rand() % 3) + 4));
        //right paddle
        for (int i = 0; i < 4; i++)
            if(ballx == player2x - 1)
                if (bally == player2y + i)
                ball->changeDirection((eDir)((rand() % 3) + 1));

        //bottom wall
        if (bally == height - 1)
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        //top wall
        if (bally == 0)
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        //right wall
        if (ballx == width - 1)
            ScoreUp(player1);
        //left wallq
        if (ballx == 0)
            ScoreUp(player2);
    }
    void Run()
    {
        while(!quit)
        {
            Draw();
            Input();
            Logic();
        }
    }
};

int main()
{
    cGameManager c(40, 20);
    c.Run();
    return 0;
}