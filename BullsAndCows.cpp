#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

vector<int> vect;
class checkGuess
{
public:
    int RandGen()
    {
        int dig[4];
        dig[0] = rand() % 9 + 1;
        dig[1] = dig[0];
        dig[2] = dig[0];
        dig[3] = dig[0];
        while (dig[1] == dig[0])
            dig[1] = rand() % 10;
        while (dig[2] == dig[0] || dig[2] == dig[1])
            dig[2] = rand() % 10;
        while (dig[3] == dig[0] || dig[3] == dig[1] || dig[3] == dig[2])
            dig[3] = rand() % 10;
        return dig[0] * 1000 + dig[1] * 100 + dig[2] * 10 + dig[3];
    }

    int BullsCows(int num, int guess)
    {
        int bulls = 0, cows = 0;
        int bDig[4], gDig[4];
        bDig[0] = num % 10;
        gDig[0] = guess % 10;
        bDig[1] = (num / 10) % 10;
        gDig[1] = (guess / 10) % 10;
        bDig[2] = (num / 100) % 10;
        gDig[2] = (guess / 100) % 10;
        bDig[3] = num / 1000;
        gDig[3] = guess / 1000;
        for (int i = 0; i < 4; ++i)
        {
            if (bDig[i] == gDig[i])
                bulls++;
            for (int j = 0; j < 4; ++j)
            {
                if (bDig[i] == gDig[j] && i != j)
                    cows++;
            }
        }
        return bulls * 10 + cows;
    }

    bool checkRep(int num)
    {
        int dig[4];
        dig[0] = num % 10;
        dig[1] = (num / 10) % 10;
        dig[2] = (num / 100) % 10;
        dig[3] = (num / 1000);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (dig[i] == dig[j] && i != j)
                    return 1;
            }
        }
        return 0;
    }

    void genVect()
    {
        for (int i = 1000; i <= 9876; i++)
            if (!checkRep(i))
                vect.push_back(i);
        //	cout << vect.size() << endl;
    }

    void modVect(int bc, int guess)
    {
        for (int i = vect.size() - 1; i >= 0; i--)
        {
            if (BullsCows(guess, vect[i]) != bc)
                vect.erase(vect.begin() + i);
        }
        return;
    }
};

int main()
{
    srand(time(0));
    checkGuess obj1;
    int bc = 0, moves = 0, guess;
    obj1.genVect();
    while (bc != 40)
    {
        guess = vect[0];
        cout << vect.size() << endl;
        cout << "Guess: " << guess << endl;
        cout << "BullsCows(Enter without space):";
        cin >> bc;
        obj1.modVect(bc, guess);
        moves++;
    }
    cout << endl
         << "It took " << moves << " moves!" << endl;
    return 0;
}
