#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;


// Adding all the possible 4 digit numbers without any repitition 
// of digits to a vector and those which do not start with zero
// Returns vector with all the numbers
vector<int> initial()
{
    int num;
    vector<int> allNums;
    for(int i1=1;i1<10;i1++){
        for(int i2=0;i2<10;i2++){
            if(i2!=i1){
                for(int i3=0;i3<10;i3++){
                    if(i3!=i2 && i3!=i1){
                        for(int i4=0;i4<10;i4++){
                            if(i4!=i1 && i4!= i2 && i4!=i3)
                            {
                                num = i1*1000+i2*100+i3*10+i4;
                                allNums.push_back(num);
                            }}}}}}}
    return allNums;
}


// Counts bulls and cows
// Called in 'refineVect' function
// Returns bulls*10 + cows
int count_both(int num, int random)
{
    int bulls=0,cows=0;
    int ndig[4];
    ndig[0] =  num/1000;
    ndig[1] = (num/100)%10;
    ndig[2] = (num/10)%10;
    ndig[3] = (num)%10;
    int rdig[4];
    rdig[0] =  random/1000;
    rdig[1] = (random/100)%10;
    rdig[2] = (random/10)%10;
    rdig[3] = (random)%10;
    for(int i=0;i<4;i++)
    {
        if(ndig[i]==rdig[i])
            bulls++;
        for(int j=0;j<4;j++)
            if(ndig[i]==rdig[j] && i!=j)
                cows++;
    }
    return bulls*10+cows;
}


// Deletes all the numbers which do not match the requirements
// Returns vector
vector<int> refineVect(int bulls,int cows,vector<int> vect,int random)
{
    int k,k_cows,k_bulls,sizee = vect.size();
    int arr[sizee]={0};
    for(int i=0;i<sizee;i++)
    {   
        k = count_both(vect[i],random);
        k_cows=k%10;
        k_bulls=k/10;
        if(k_cows!=cows || k_bulls!=bulls)
            arr[i]=1;
    }
    for(int j=sizee-1 ;j>=0; j--)
    {   
        if(arr[j]==1)
            vect.erase(vect.begin()+j);
    }
    return vect;
}


int main()
{       
    int k=1, bulls, cows, randomNum;
    // Initializing possibleNums vector
    vector<int> possibleNums;
    possibleNums = initial();
    srand(time(0));
    while(true)
    {
        cout << "ATTEMPT NO.: " << k << endl;
        // Randomly choose a position among the vector
        int randomPos = rand()%possibleNums.size();
        // Guess the number at randomly chosen position
        randomNum = possibleNums[randomPos];
        cout << "Possibilities: " << possibleNums.size() <<endl;
        cout << "My Guess: " << randomNum << endl;
        cout<<"Bulls: ";
        cin >> bulls;
        if(bulls==4) break;
        cout << "Cows: ";
        cin >> cows;
        cout << endl;
        // Delete the ruled out numbers from the vector
        possibleNums = refineVect(bulls,cows,possibleNums,randomNum);
        k++;
    }
    cout << endl << "Oh! So the Number was " << randomNum << "." << endl;
    cout << "WELL, THAT WAS EASY. WE HAWT!";
}