#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int arr[3][3];
bool player = true;
bool draw = true;

/*
backend representation  of the matrix
player-5
computer-3
blank-2
*/



//initialises the matrix with 2
void initialise()
{
 for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            arr[i][j]=2;
        }
    }
}

//prints the matrix
void print_arr()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(arr[i][j] == 2) {
				cout<<"   "<<"|";
			} else if(arr[i][j] == 3) {
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
	int x=125;
	//check for rows and columns
	for(int i=0;i<3;i++)
	{
		if(arr[i][0]*arr[i][1]*arr[i][2]==x)
		{
		    return true;
		}

		if(arr[0][i]*arr[1][i]*arr[2][i]==x)
		{return true;
		}
	}

	//check for main diogonal
	if(arr[0][0] * arr[1][1] * arr[2][2] == x)
	{return true;
	}

	//check for other diogonal
	if(arr[0][2] * arr[1][1] * arr[2][0] == x)
	{return  true;
	}
	return false;
}

void go(pair<int, int> move)
{
	int x = (player)?(5):(3);

	if(arr[move.first][move.second]==2)
	{arr[move.first][move.second] = x;
    print_arr();
	player = !player;

	}
	else{
        cout<<"invalid move";


	}
}

pair<int, int> make2() {


	//returns center block
	if(arr[1][1] == 2)	return make_pair(1,1);
	vector<pair<int, int> > cd;



	if(arr[0][1]== 2)	cd.push_back(make_pair(0,1));
	if(arr[1][0]== 2) cd.push_back(make_pair(1,0));
	if(arr[1][2]== 2) cd.push_back(make_pair(1,2));
	if(arr[2][1]== 2) cd.push_back(make_pair(2,1));
	if(cd.size() == 0) {
		if(arr[0][0] == 2) cd.push_back(make_pair(0,0));
		if(arr[0][2] == 2) cd.push_back(make_pair(0,2));
		if(arr[2][0] == 2) cd.push_back(make_pair(2,0));
		if(arr[2][2] == 2) cd.push_back(make_pair(2,2));
	}
	srand(time(NULL));
	int pos = rand() % cd.size();
	return cd[pos];
}
pair<int, int> user() {
	int i,j;
	cout<<"Input- ";
	cin>>i;
	--i;
	return make_pair(i/3,i%3);
}

pair<int, int> poss_win(bool p) {
	int x;
	if(p)
		x=50;
	else
		x=18;


	//checks for row and column
	for(int i=0;i<3;i++)
	{
		if(arr[i][0]*arr[i][1]*arr[i][2]==x)
		{
			if(arr[i][0] == 2) return make_pair(i,0);
			else if(arr[i][1] == 2) return make_pair(i,1);
			else return make_pair(i,2);
		}

		if(arr[0][i]*arr[1][i]*arr[2][i]==x)
		{
			if(arr[0][i] == 2) return make_pair(0,i);
			else if(arr[1][i] == 2) return make_pair(1,i);
			else return make_pair(2,i);
		}
	}

	//checks for main diogonal
	if(arr[0][0] * arr[1][1] * arr[2][2] == x)
	{
		if(arr[0][0] == 2) return make_pair(0,0);
		else if(arr[1][1] == 2) return make_pair(1,1);
		else return make_pair(2,2);
	}

	//checks for alternate diogonal
	if(arr[0][2] * arr[1][1] * arr[2][0] == x)
	{
		if(arr[0][2] == 2) return make_pair(0,2);
		else if(arr[1][1] == 2) return make_pair(1,1);
		else return make_pair(2,0);
	}
	return make_pair(-1,-1);
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
		    pair<int ,int> ai=poss_win(player);
			if(ai == make_pair(-1,-1)) {

            pair<int , int> opponent=poss_win(!player);
				if(opponent != make_pair(-1,-1)) {
					go(opponent);
				} else {
					go(make2());
				}
			} else {

			    go(ai);
				draw = false;
				cout<<"The computer wins."<<endl;
				break;
			}
		}
	}
	if(draw) cout<<"It's a draw"<<endl;

	return 0;
}
