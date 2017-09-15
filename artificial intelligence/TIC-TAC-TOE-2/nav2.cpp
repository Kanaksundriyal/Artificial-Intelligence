#include<bits/stdc++.h>
using namespace std;
int arr[3][3];
int arr1[3][3];
bool player = true;
bool draw = true;
vector< int > pl;
vector< int > ai;
/*
backend representation  of the matrix
player- 5
computer- 3
blank- -1
*/
pair<int , int> getindex(int n)
{   switch(n){
    case 8:
       return make_pair(0,0);
    case 3:
       return make_pair(0,1);
    case 4:
       return make_pair(0,2);
    case 1:
       return make_pair(1,0);
    case 5:
       return make_pair(1,1);
    case 9:
       return make_pair(1,2);
    case 6:
       return make_pair(2,0);
    case 7:
       return make_pair(2,1);
    case 2:
       return make_pair(2,2);
    default:
        return make_pair(-1,-1);
    }
}
//initialises the matrix with 2
void initialise()
{
    arr[0][0]=8;
    arr[0][1]=3;
    arr[0][2]=4;
    arr[1][0]=1;
    arr[1][1]=5;
    arr[1][2]=9;
    arr[2][0]=6;
    arr[2][1]=7;
    arr[2][2]=2;
    for(int i=0;i<3;++i)
    for(int j=0;j<3;++j)
    arr1[i][j]=-1;
}
//prints the matrix
void print_arr()
{
	for(int i=0;i<3;i++)
	{
    for(int j=0;j<3;j++)
		{
        if(arr1[i][j] == -1) {
            cout<<"   "<<"|";
        } else if(arr1[i][j] == 3) {
            cout<<" X "<<"|";
        } else {
            cout<<" O "<<"|";
        }
		}
		cout<<endl;
	}
	cout<<endl;
}

//checks if the user/player has won
bool hasPlayerWon()
{
	for(int i=0;i<pl.size();++i)
    {
    for(int j=i+1;j<pl.size();++j)
    {
    for(int k=j+1;k<pl.size();++k)
        {
        if(pl[i]+pl[j]+pl[k]==15)
            return true;
        }
    }
    }
	return false;
}

void go(pair<int, int> move)
{   int x = (player)?(5):(3);
	if(arr1[move.first][move.second]==-1)
	{
	    arr1[move.first][move.second] = x;
    print_arr();
    if(player)
    {
        pl.push_back((arr[move.first][move.second]));
    }
    else
    {
        ai.push_back(arr[move.first][move.second]);
    }
	player = !player;
    }
}

pair<int , int> make2() {
    //returns center block
	if(arr1[1][1] == -1)	return make_pair(1,1);
	vector<pair<int, int> > cd;
    if(arr1[0][1]== -1)	cd.push_back(make_pair(0,1));
	if(arr1[1][0]== -1) cd.push_back(make_pair(1,0));
	if(arr1[1][2]== -1) cd.push_back(make_pair(1,2));
	if(arr1[2][1]== -1) cd.push_back(make_pair(2,1));
	if(cd.size() == 0) {
		if(arr1[0][0] == -1) cd.push_back(make_pair(0,0));
		if(arr1[0][2] == -1) cd.push_back(make_pair(0,2));
		if(arr1[2][0] == -1) cd.push_back(make_pair(2,0));
		if(arr1[2][2] == -1) cd.push_back(make_pair(2,2));
	}
	srand(time(NULL));
	int pos = rand() % cd.size();
	return cd[pos];
}
pair<int , int> user() {
	int i,j;
	cout<<"Input- ";
	cin>>i;
	--i;
    return make_pair(i/3,i%3);
}

int poss_win(bool p) {
	int x;
	if(p)
	{
    for(int i=0;i<pl.size();++i)
    {
        for(int j=i+1;j<pl.size();++j)
        {
            if((15-(pl[i]+pl[j]) > 0) && (15-(pl[i]+pl[j]) < 9))
                {
                pair<int , int> d=getindex(15-(pl[i]+pl[j]));
                if(arr1[d.first][d.second] == -1)
                return 15-(pl[i]+pl[j]);
                }
        }
    }
	}
	else
    {
    for(int i=0;i<ai.size();++i)
        {
        for(int j=i+1;j<ai.size();++j)
        {
            if( 15-(ai[i]+ai[j]) > 0 && 15-(ai[i]+ai[j]) <= 9)
                { pair<int , int> d=getindex(15-(ai[i]+ai[j]));
                if(arr1[d.first][d.second]==-1)
                    return 15-(ai[i]+ai[j]);

                }
        }
        }

    }
	return -1;
}
int main()
{
	int moves = 9;
    initialise();
	while(moves--) {
		if(player) {
			go(user());
			if(hasPlayerWon()==true)
			{
				cout<<"Player Won"<<endl;
				draw=false;
				break;
			}
		} else {
		    int a=poss_win(player);
			if(a == -1) {
            int opponent=poss_win(!player);
				if(opponent != -1) {
             pair<int , int> opo=getindex(opponent);
					go(opo);
				} else {
					go(make2());
				}
			} else {
             pair<int , int> aa=getindex(a);
                go(aa);
				draw = false;
				cout<<"The computer wins."<<endl;
				break;
			}
		}
	}
	if(draw) cout<<"It's a draw"<<endl;
	return 0;
}
