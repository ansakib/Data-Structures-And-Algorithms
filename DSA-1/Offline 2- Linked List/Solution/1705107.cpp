#include<bits/stdc++.h>
using namespace std;

struct Player
{
    int reflex_time;
    int player_no;
    Player* next;
    Player* previous;
};

class CircularLL
{
private:
    Player* first;
    Player* last;
public:
    CircularLL();
    void add_end(int pl_no, int ref_time);
    void add_front(int pl_no, int ref_time);
    void add_after(int pl_no, int ref_time, Player* pill_holder);
    void add_before(int pl_no, int ref_time, Player* pill_holder);
    void delete_plyr(int pl_no);
    Player* getFirst();
    void forward_traverse(Player* pill_holder);
    void reverse_traverse(Player* pill_holder);
};
CircularLL::CircularLL()
{
    first = NULL;
    last = NULL;
}
void CircularLL::add_end(int pl_no, int ref_time)
{
    Player* newPlayer = new Player;
    newPlayer->player_no = pl_no;
    newPlayer->reflex_time = ref_time;

    if(first==NULL && last==NULL)
    {
        first = newPlayer;
        last = newPlayer;
        first->previous = NULL;
        first->next = NULL;
        last->previous = NULL;
        last->next = NULL;
    }
    else
    {
        newPlayer->previous = last;
        last->next = newPlayer;
        last = newPlayer;
        last->next = first;
        first->previous = last;
    }
}

void CircularLL::add_front(int pl_no, int ref_time)
{
    Player* newPlayer = new Player;
    newPlayer->player_no = pl_no;
    newPlayer->reflex_time = ref_time;

    if(first==NULL && last==NULL)
    {
        first = newPlayer;
        last = newPlayer;
        first->previous = NULL;
        first->next = NULL;
        last->previous = NULL;
        last->next = NULL;
    }
    else
    {
        newPlayer->next = first;
        first->previous = newPlayer;
        first = newPlayer;
        first->previous = last;
        last->next = first;
    }
}
void CircularLL::add_after(int pl_no, int ref_time, Player* pill_holder)
{
    if(pill_holder == last)
    {
        add_end(pl_no, ref_time);
    }
    else
    {
        Player* newPlayer = new Player;
        newPlayer->player_no = pl_no;
        newPlayer->reflex_time = ref_time;
        newPlayer->next = pill_holder->next;
        newPlayer->previous = pill_holder;
        pill_holder->next = newPlayer;
        newPlayer->next->previous = newPlayer;
    }
}

void CircularLL::add_before(int pl_no, int ref_time, Player* pill_holder)
{
    if(pill_holder == first)
    {
        add_front(pl_no, ref_time);
    }
    else
    {
        Player* newPlayer = new Player;
        newPlayer->player_no = pl_no;
        newPlayer->reflex_time = ref_time;
        newPlayer->previous = pill_holder->previous;
        newPlayer->previous->next = newPlayer;
        newPlayer->next = pill_holder;
        pill_holder->previous = newPlayer;
    }
}

void CircularLL::delete_plyr(int pl_no)
{
    Player *desired_player = new Player;
    desired_player = first;
    while(true)
    {
        if(desired_player->player_no==pl_no)
        {
            break;
        }
        desired_player = desired_player->next;
        if(desired_player == first)
        {
            return;
        }
    }
    if(desired_player == first)
    {
        first=first->next;
        first->previous = last;
        last->next = first;
    }
    else if(desired_player == last)
    {
        last = last->previous;
        last->next = first;
        first->previous = last;
    }
    else
    {
        desired_player->previous->next = desired_player->next;
        desired_player->next->previous = desired_player->previous;
    }
}

Player* CircularLL::getFirst()
{
    return first;
}
void CircularLL::forward_traverse(Player* pill_holder)
{
    Player* trav = new Player;
    trav = pill_holder;
    while(true)
    {
        cout<<trav->player_no<<", ";
        trav = trav->next;
        if(trav == pill_holder)
            break;
    }
    cout<<endl;
}
void CircularLL::reverse_traverse(Player* pill_holder)
{
    Player* trav = new Player;
    trav = pill_holder;
    while(true)
    {
        cout<<trav->player_no<<", ";
        trav = trav->previous;
        if(trav == pill_holder)
            break;
    }
    cout<<endl;
}

class ppGame
{
private:
    CircularLL* players;
    int players_entered;
    int remaining_players;
    int prev_gameTime;
    bool left_to_right;
    Player* PillowHolder;
    int PillowHolder_usedTime;
public:
    ppGame();
    void add_last(int ref_time);
    void add_midGame(int time, int ref_time);
    void remove_Player(int time);
    void change_direction(int time);
    Player* find_PillowHolder(int time);
    void print_PillowHolder(int time);
    void final_stats(int time);
};
ppGame::ppGame()
{
    players = new CircularLL();
    players_entered = 0;
    remaining_players = 0;
    prev_gameTime = 0;
    left_to_right = true;
    PillowHolder = new Player;
    PillowHolder_usedTime = 0;
}
void ppGame::add_last(int ref_time)
{
    if(remaining_players==1 && players_entered!=1)
    {
        return ;
    }
    players_entered++;
    remaining_players++;
    players->add_end(players_entered, ref_time);
    if(players_entered==1)
    {
        PillowHolder = players->getFirst();
    }
}

void ppGame::add_midGame(int time, int ref_time)
{
    if(remaining_players==1 && players_entered!=1)
    {
        return ;
    }
    players_entered++;
    remaining_players++;
    find_PillowHolder(time);
    if(left_to_right)
    {
        players->add_before(players_entered, ref_time, PillowHolder);
    }
    else
    {
        players->add_after(players_entered, ref_time, PillowHolder);
    }
}

void ppGame::remove_Player(int time)
{
    if(remaining_players==1 && players_entered!=1)
    {
        return ;
    }
    remaining_players--;
    find_PillowHolder(time);
    int current_PillowHolder = PillowHolder->player_no;
    players->delete_plyr(current_PillowHolder);
    if(left_to_right)
    {
        PillowHolder = PillowHolder->next;
        PillowHolder_usedTime = 0;
    }
    else
    {
        PillowHolder = PillowHolder->previous;
        PillowHolder_usedTime = 0;
    }
    cout<<"Player "<<current_PillowHolder<<" has been eliminated at t="<<time<<endl;
}

void ppGame::change_direction(int time)
{
    find_PillowHolder(time);
    left_to_right = !left_to_right;
}

Player* ppGame::find_PillowHolder(int time)
{
    int gameTime = time - prev_gameTime + PillowHolder_usedTime;
    prev_gameTime = time;
    while(true)
    {
        if(PillowHolder->reflex_time<gameTime)
        {
            gameTime = gameTime - PillowHolder->reflex_time;
            if(left_to_right)
                PillowHolder = PillowHolder->next;
            else
                PillowHolder = PillowHolder->previous;
        }
        else
        {
            PillowHolder_usedTime = gameTime;
            return PillowHolder;
        }
    }
}

void ppGame::print_PillowHolder(int time)
{
    cout<<"Player "<<find_PillowHolder(time)->player_no<<" is holding the pillow at t="<<time<<endl;
}
void ppGame::final_stats(int time)
{
    cout<<"Game over : ";
    if(remaining_players==1)
    {
        cout<<"Player "<<PillowHolder->player_no<<" wins!!"<<endl;
    }
    else
    {
        print_PillowHolder(time);
        cout<<"Pillow Passing sequence = Player ";
        if(left_to_right)
            players->forward_traverse(PillowHolder);
        else
            players->reverse_traverse(PillowHolder);
    }
}

int main()
{
    ppGame game;
    int n;
    cout<<"Enter the number  of initial players: ";
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int reflex_time;
        cin>>reflex_time;
        game.add_last(reflex_time);
    }
    while(true)
    {
        int game_time;
        cin>>game_time;
        char choice;
        cin>>choice;
        if(choice == 'M')
        {
            game.remove_Player(game_time);
        }
        else if(choice == 'R')
        {
            game.change_direction(game_time);
        }
        else if(choice == 'I')
        {
            int ref_time;
            cin>>ref_time;
            game.add_midGame(game_time, ref_time);
        }
        else if(choice == 'P')
        {
            game.print_PillowHolder(game_time);
        }
        else if(choice == 'F')
        {
            game.final_stats(game_time);
            break;
        }
    }
}


