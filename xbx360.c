#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>


//QUICK SORTING METHOD
void qqsort(int element_list[], int low, int high)
{
int pivot, value1, value2, temp;
if (low < high)
{
pivot = low;
value1 = low;
value2 = high;
while (value1 < value2)
{
while (element_list[value1] <= element_list[pivot] && value1 <= high)
{
value1++;
}
while (element_list[value2] > element_list[pivot] && value2 >= low)
{
value2--;
}
if (value1 < value2)
{
temp = element_list[value1];
element_list[value1] = element_list[value2];
element_list[value2] = temp;
}
}
temp = element_list[value2];
element_list[value2] = element_list[pivot];
element_list[pivot] = temp;
qqsort(element_list, low, value2 - 1);
qqsort(element_list, value2 + 1, high);
}
}

int dice() {
    return rand() % 12 + 1;
}

//Card Number type
typedef struct cNumber {
    int val;
    char name[3];
} cnumber;

//Card Number generator
cnumber generateCN(cnumber cnum) {

    //number value
    cnum.val = rand() % 13;
    //number external name
    char nName[13][3]= {"2","3","4","5","6",
                        "7","8","9","10","J","Q","K","A"
                       };
    strcpy(cnum.name,nName[cnum.val]);
    return cnum;
}

//Card Suit type
typedef struct cSuit {
    int id;
    char name[7];
} csuit;

//Card Suit generator
csuit generateCS(csuit cardsuit) {
    cardsuit.id=rand() % 4;
    char sName[4][7]= {"spades","clubs",
                       "rombos","hearts"
                      };
    strcpy(cardsuit.name,sName[cardsuit.id]);
    return cardsuit;
}

//Card type
typedef struct Cards {
    cnumber number;
    csuit suit;
} card;

//Tile Kind type
typedef struct tKind {
    int unsigned id;
    char name[7];
} tkind;

//Tile Kind generator
tkind generateTK(tkind kind) {
    kind.id=rand() % 3;
    char kName[3][7]= {"suits","honors",
                       "bonus"
                      };
    strcpy(kind.name,kName[kind.id]);
    return kind;
}

//Tile Data type
typedef struct tData {
    int val;
    char name[15];
    char suit[11];
} tdata;

//Tile Data generator
tdata generateTD(tkind kind, tdata tiled) {
    int unsigned pursuit;

    // suits for each kind
    char numSuits[3][11]= {"dots","bamboos","characters"};
    char honSuits[2][11]= {"winds","dragons"};
    char bonSuits[2][11]= {"seasons","flowers"};

    // names for each thing
    char numArray[9][15] = {"1","2","3","4","5","6","7","8","9"};
    char honArray[7][15] = {"e-wind","s-wind","n-wind","w-wind","w-dragon","g-dragon","r-dragon"};
    char bonArray[8][15] = {"winter","spring","autumn","summer","plum","chrysanthemum","bamboo","orchid"};

    if(kind.id==0) {
        tiled.val = rand() % 9;
        pursuit = rand() % 3;
        strcpy(tiled.suit, numSuits[pursuit]);
        strcpy(tiled.name,numArray[tiled.val]);
    }
    else if(kind.id==1) {
        pursuit = rand() % 2;
        if(pursuit==0){
            tiled.val = rand() % 4;
        } // winds
        else{
            tiled.val = rand() % 3 + 4;
        } // dragons
        
        strcpy(tiled.suit, honSuits[pursuit]);
        strcpy(tiled.name, honArray[tiled.val]);
    }
    else {
        pursuit = rand() % 2;
        
        if(pursuit == 0){
            tiled.val = rand() % 4; //seasons
        }
        else{
            tiled.val = rand() % 4 + 4; //flowers
        }
        strcpy(tiled.suit, bonSuits[pursuit]);
        strcpy(tiled.name, bonArray[tiled.val]);
    }

    return tiled;
}

//Tile Suit type
typedef struct tSuit {
    int id;
    char name[8];
} tsuit;

//Tile type
typedef struct Tiles {
    tdata data;
    tkind kind;
} tile;

//Roulette type
typedef struct Roulette {
    int number;
    char namecolor[9];
} roulette;

//Roulette shot generator
roulette rShot(roulette rou) {
    rou.number = rand() % 38;
    char nameColors[38][9] = {"0","1-red","2-black","3-red","4-black","5-red","6-black","7-red","8-black",
                              "9-red","10-black","12-red","11-black","14-red","13-black","16-red","15-black","18-red","17-black","19-red",
                              "20-black","21-red","22-black","23-red","24-black","25-red","26-black","27-red","28-black","30-red","29-black",
                              "32-red","31-black","34-red","33-black","36-red","35-black","0"
                             };
    strcpy(rou.namecolor,nameColors[rou.number]);
    return rou;
}


//Player type
typedef struct Player {
    long gold;
    card deck[4];
    tile mahjong[5];
    //max roulette number of the
    //player's parcel
    int dominance;
    int rwin; //rounds won
    int position; //the table position. 0 is far-right, 3 is far-left. Its max equals the # of playas-1.
    int handscore; //the score of the card-hand for each playa
    int fsp; // has FSP?
} player;

//checkHand function
int unsigned checkHand(player tplaya) {
int dvalues[4],l;
for (l=0;l<4;l++){
dvalues[l] = tplaya.deck[l].number.val;
}
qqsort(dvalues, 0, 3);
int compa1 = strcmp(tplaya.deck[0].suit.name,tplaya.deck[1].suit.name);
int compa2 = strcmp(tplaya.deck[1].suit.name,tplaya.deck[2].suit.name);
int compa3 = strcmp(tplaya.deck[2].suit.name,tplaya.deck[3].suit.name);
    //Same suit?
    if(compa1==0 && compa1 == compa2 && compa2 == compa3){
        //Same suit OK so FLUSH type
        // PREZ FLUSH    
        if (dvalues[0]==9 && dvalues[1]==10 && dvalues[2]==11 && dvalues[3]==12){
            return 900 + (dvalues[0]*5);
        }
        // FOUR FLUSH    
        else if (dvalues[0]==dvalues[1]-1 && dvalues[1]==dvalues[2]-1 && dvalues[2]==dvalues[3]-1){
            return 800 + (dvalues[0]*5);
        }
        // LEPTO FLUSH
        else {
            return 600 + (dvalues[3]*5);
        }
    }
    else{
        // POKER
        if (dvalues[0]==dvalues[1] && dvalues[1]==dvalues[2] && dvalues[2]==dvalues[3]){
            return 700 + (dvalues[0]*5);
        }
        // FOUR RANK
        else if(dvalues[0]==dvalues[1]-1 && dvalues[1]==dvalues[2]-1 && dvalues[2]==dvalues[3]-1){
            return 500 + (dvalues[0]*5);
        }
        // TRIPLET
        else if((dvalues[0]==dvalues[1] && dvalues[1]==dvalues[2]) || (dvalues[1]==dvalues[2] && dvalues[2]==dvalues[3])){
            return 400 + (dvalues[1]*5);    
        }
        // DOUBLETS
        else if(dvalues[0]==dvalues[1] && dvalues[2]==dvalues[3]){
            return 300 + (dvalues[3]*5);
        }
        // PAIRS
        else if(dvalues[0]==dvalues[1] || dvalues[1]==dvalues[2] || dvalues[2]==dvalues[3]){
            if(dvalues[0]==dvalues[1]){
                return 200 + (dvalues[0]*5);
            }
            else if (dvalues[1]==dvalues[2]){
                return 200 + (dvalues[1]*5);
            }
            else{
                return 200 + (dvalues[2]*5);
            }
        }
        // HI-CARD
        else{
            return 100 + (dvalues[3]*5);
        }
    }
}

//windsCheck function
int unsigned windsCheck(player mplaya){
    int j;
     for(j=0;j<5;j++){
         switch (mplaya.mahjong[j].kind.id)
         {
       
         case 1:
               switch (mplaya.mahjong[j].data.val)
               {
               case 0:
                   return 1;
                   break;
               case 1:
                   return 2;
                   break;
               case 2:
                   return 3;
                   break;
               case 3:
                   return 4;
                   break;
               default:
                   return 0;
                   break;
               }
             break;
         default:
            if(j==4){return 0;}
             break;
         }
     }
}

//fspCheck function
int fspCheck(player fplaya){
    int ok,m,wnum,nnum,dnum,snum,fnum; int dlen=5;
    // Conditions:
        //2 or 3 same number tiles, dragons count
        //2 or 3 seasons XOR 2 or 3 flowers
   // int fkid = fplaya.mahjong[0].kind.id;
   // int i = fplaya.mahjong[1].data.val;
    //Process:
        //Check number of non-wind tiles
        for (m=0;m<5;m++){
            if (fplaya.mahjong[m].kind.id==1 && fplaya.mahjong[m].data.val < 4){
                wnum += 1;
            }
        }

        if (wnum>=2){
            //Hath more than 2 winds, therefore exit.
            return 0;
        }
        else{
            dlen -= wnum; // dlen = 4 | 5
        }

        //Check number of normal tiles
          for(m=0;m>5;m++){
                    if(fplaya.mahjong[m].kind.id==0){
                        nnum += 1;
                    }
                }
        switch (dlen)
        {
        case 4:
                if (nnum>=3){
                    //Hath more than or 3 normal tiles, therefore exit.
                    return 0;
                }
                else{
                    dlen -= nnum; // dlen = 2 | 3 | 4
                }
            break;
        
        default:
                if (nnum>3){
                    //Hath more than 3 normal tiles, therefore exit.
                    return 0;
                }
                else{
                    dlen -= nnum; // dlen = 2 | 3 | 4 | 5
                }
            break;
        }
              
        //Check number of dragon tiles
            for (m=0;m<5;m++){
                if (fplaya.mahjong[m].kind.id==1 && fplaya.mahjong[m].data.val >= 4){
                dnum += 1;
                }
            }

            switch (dlen)
            {
            case 5:
                if(dnum == 2 || dnum == 3){
                    dlen -= dnum; // dlen = 2 | 3
                }
                else{
                    return 0;
                }
                break;
            
            case 4:
                if(dnum == 1 || dnum == 2){
                    dlen -= dnum; // dlen = 2 | 3
                }
                else{
                    return 0;
                }

            case 3:
                if(dnum == 0 || dnum == 1){
                    dlen -= dnum; // dlen = 2 | 3
                }
                else{
                    return 0;
                }

            default:
                if(dnum == 0){
                    dlen -= dnum; // dlen = 2
                }
                else{
                    return 0;
                }
                break;
            }

        //Check number of bonus tiles

            for (m=0;m<5;m++){
                if (fplaya.mahjong[m].kind.id==2 && fplaya.mahjong[m].data.val < 4){
                    snum += 1;
                }
                else{
                    fnum += 1;
                }
            }

        //Check if Seasons XOR Flowers
        // If none is 0, then exit.
        if(fnum == 0){
          return 1;  
        }
        else if (snum == 0){
          return 1;
        }
        else{
          return 0;
        }
        
}


//jellyBean function
int jellyBean(int pnum){
    int bean = rand() % 3; int pchoz;
    printf("Player %d, please choose a hand\n",pnum);
    printf("0: Left\n 1: Center\n 2: Right\n");
    scanf("%d",&pchoz);
   if (pchoz == bean){
       printf("Bingo!\n");
       return 1;
   }
   else{
       printf("Oh no! There was nothing in there!\n");
       return 0;
   }
}




int main()
{
    int player_num, round, fdice, dwin, fspwin;
    long player_gold, betaux, ibet; 
    ibet=0; fspwin=0; round=0;
    int win = 0;
    roulette roul;
    srand(time(0));
    printf("This is Deal or No Deal.\n"); Sleep(2.5);
    printf("Select player number (2 to 4):\n");Sleep(2.5);
    scanf("%d",&player_num);
    printf("Select initial player gold:\n");Sleep(2.5);
    scanf("%ld",&player_gold);
    switch (player_num)
    {
    case 2:
    //Pre-Game globals
        printf("Let's go!\n");Sleep(2.5);
        player players2[2];
        int i,j,k;
        for (i=0; i<2; i++){
            //Gold
            players2[i].gold=player_gold;
            players2[i].dominance=18*(i+1);
            players2[i].position=i;
            players2[i].rwin=0;
        }
     //In-Game loopers   
        while (win==0){
            round+=1;
            printf("This is round #%d\n",round);Sleep(2.5);
            for (i=0; i<2; i++){
                
                //Cards
                for (j=0; j<4; j++){
                    players2[i].deck[j].number=generateCN(players2[i].deck[j].number);
                    players2[i].deck[j].suit=generateCS(players2[i].deck[j].suit);
                }
                //Tiles
                 for (k=0; k<5; k++){
                    players2[i].mahjong[k].kind=generateTK(players2[i].mahjong[k].kind);
                    players2[i].mahjong[k].data=generateTD(players2[i].mahjong[k].kind,players2[i].mahjong[k].data);
                }
            }

            //Turn 1: Your cards, hand check & initial bet
            for(i=0; i<2; i++){
            printf("Player %d, these are thine cards:\n",i+1);Sleep(2.5);
                for(j=0;j<4;j++){
                    printf("%d) %s of %s\n",j+1,players2[i].deck[j].number.name,players2[i].deck[j].suit.name);
                    Sleep(2.5);
                }

                players2[i].handscore = checkHand(players2[i]);
                if (players2[i].handscore>=900){
                    printf("Player %d hath a Prez Flush\n",i+1);Sleep(2.5);
                }
                else if(players2[i].handscore>=800){
                    printf("Player %d hath a Four Flush\n",i+1);Sleep(2.5);
                }
                 else if(players2[i].handscore>=700){
                    printf("Player %d hath a Poker\n",i+1);Sleep(2.5);
                }
                else if(players2[i].handscore>=600){
                    printf("Player %d hath a Lepto Flush\n",i+1);Sleep(2.5);
                }
                else if(players2[i].handscore>=500){
                    printf("Player %d hath a Four Rank\n",i+1);Sleep(2.5);
                }
                else if(players2[i].handscore>=400){
                    printf("Player %d hath a Triplet\n",i+1);Sleep(2.5);
                }
                else if(players2[i].handscore>=300){
                    printf("Player %d hath Doublets\n",i+1);Sleep(2.5);
                }
                else if(players2[i].handscore>=200){
                    printf("Player %d hath a Pair\n",i+1);Sleep(2.5);
                }
                else{
                    printf("Player %d hath Hi-Card\n",i+1);Sleep(2.5);
                }
            }

            //Initial bet making
            for(i=0;i<2;i++){
            printf("Player %d, please make thy bets:",i+1);
            scanf("%ld",&betaux);
            ibet += betaux;
            players2[i].gold -= betaux;
            }

            //Deck winner prediction
            if (players2[0].handscore>players2[1].handscore){
                printf("Player 1 would win the deck. Player 2 must find another way.\n");Sleep(2.5);
                dwin=1;
            }
            else if (players2[1].handscore>players2[0].handscore){
                printf("Player 2 would win the deck. Player 1 must find another way.\n");Sleep(2.5);
                dwin=2;
            }
            else{
                printf("It's a draw, both players must find another way.\n");Sleep(2.5);
                dwin=0;
            }
            
            //Turn 2: Your tiles, Winds check
            int windcho; // Binary bool for decision on whether changing seats or not.
            player aux; // Ethereal player used for temporary assignation.
            int windval;

             for(i=0; i<2; i++){
                 printf("Player %d, these are thine tiles:\n",i+1);Sleep(2.5);
                for(j=0;j<5;j++){
                    printf("%d) %s of %s, within the %s category.\n",j+1,players2[i].mahjong[j].data.name,players2[i].mahjong[j].data.suit,players2[i].mahjong[j].kind.name);
                    Sleep(2.5);
                }
             }

             for(i=0; i<2; i++){
                windval = windsCheck(players2[i]);
                
                switch (windval)
                {
                case 1:
                    printf("Player %d hath the East Wind.\n",i+1);
                    //Only two players -> NW & SE act the same, as there's no possibility to shift seats
                    if(players2[i].position==0){
                        printf("Will player %d switch positions? (1=y,0=n)\n",i+1);
                        scanf("%d", &windcho);
                        switch (windcho)
                        {
                        case 1:
                        //This kind of "IF" is only needed in 2P game or switching decissions.
                        //For 3P or 4P shifting decissions there's no need for this as the target playa is scanf-ed
                            if (i==0){
                                printf("Player 1 switched seats.\n");
                                aux = players2[0];
                                players2[0] = players2[1];
                                players2[1] = aux; 
                                if (dwin == 2){dwin=1;}
                            }
                            else{
                                printf("Player 2 switched seats.\n");
                                aux = players2[1];
                                players2[1] = players2[0];
                                players2[0] = aux; 
                                if (dwin == 1){dwin=2;}
                            }
                            break;
                        
                        default:
                            break;
                        }
                    }
                    else{
                        Sleep(2.5);printf("But Player %d can't go left.\n",i+1);
                    }
                    break;
                case 2:
                    printf("Player %d hath the South Wind.\n",i+1);
                    if(players2[i].position==0){
                        printf("Will player %d switch positions? (1=y,0=n)\n",i+1);
                        scanf("%d", &windcho);
                        switch (windcho)
                        {
                        case 1:
                            if (i==0){
                                printf("Player 1 switched seats.\n");
                                aux = players2[0];
                                players2[0] = players2[1];
                                players2[1] = aux; 
                                if (dwin == 2){dwin=1;}
                            }
                            else{
                                printf("Player 2 switched seats.\n");
                                aux = players2[1];
                                players2[1] = players2[0];
                                players2[0] = aux;
                                if (dwin == 1){dwin=2;} 
                            }
                            break;
                        
                        default:
                            break;
                        }
                    }
                    else{
                        Sleep(2.5);printf("But Player %d can't go left.\n",i+1);
                    }
                    break;
                case 3:
                    printf("Player %d hath the North Wind.\n",i+1);
                    if(players2[i].position==1){
                        printf("Will player %d switch positions? (1=y,0=n)\n",i+1);
                        scanf("%d", &windcho);
                        switch (windcho)
                        {
                        case 1:
                            if (i==0){
                                printf("Player 1 switched seats.\n");
                                aux = players2[0];
                                players2[0] = players2[1];
                                players2[1] = aux; 
                                if (dwin == 2){dwin=1;}
                            }
                            else{
                                printf("Player 2 switched seats.\n");
                                aux = players2[1];
                                players2[1] = players2[0];
                                players2[0] = aux; 
                                if (dwin == 1){dwin=2;}
                            }
                            break;
                        
                        default:
                            break;
                        }
                    }
                    else{
                        Sleep(2.5);printf("But Player %d can't go right.\n",i+1);
                    }
                    break;
                case 4:
                    printf("Player %d hath the West Wind.\n",i+1);
                     if(players2[i].position==1){
                        printf("Will player %d switch positions? (1=y,0=n)\n",i+1);
                        scanf("%d", &windcho);
                        switch (windcho)
                        {
                        case 1:
                            if (i==0){
                                printf("Player 1 switched seats.\n");
                                aux = players2[0];
                                players2[0] = players2[1];
                                players2[1] = aux; 
                                if (dwin == 2){dwin=1;}
                            }
                            else{
                                printf("Player 2 switched seats.\n");
                                aux = players2[1];
                                players2[1] = players2[0];
                                players2[0] = aux; 
                                if (dwin == 1){dwin=2;}
                            }
                            break;
                        
                        default:
                            break;
                        }
                    }
                    else{
                        Sleep(2.5);printf("But Player %d can't go right.\n",i+1);
                    }
                    break;
                default:
                    Sleep(2.5);printf("Player %d hath no winds.\n",i+1);
                    break;
                }
             }
            
            //Turn 3: Dice throw
            Sleep(2.5);printf("It's time for a dice throw.\n");
            int diceval = dice();
           
            Sleep(2.5);printf("The dice threw %d\n",diceval);
            
            if (diceval % 2 == 0){
               Sleep(2.5); printf("Dice value is an even number. No roulette.\n");
            }
            else{
               Sleep(2.5); printf("Dice value is an odd number.\n");
               Sleep(2.5); printf("The roulette shall be spinned.\n");
                //Turn 4: Possible roulette throw & consequences
                roul=rShot(roul);
               Sleep(2.5); printf("The roulette threw %s.\n",roul.namecolor);
                if (roul.number==0  || roul.number==37){
                  Sleep(2.5);  printf("Zero. Nothing happens.");
                }
                else if(roul.number % 2 == 1){
                    if (roul.number <= players2[0].dominance){
                       Sleep(2.5); printf("This red number is in Player 1's dominance.\n");
                       Sleep(2.5); printf("Player 1 earneth a tenth of his current gold.\n");
                        players2[0].gold += players2[0].gold * 0.1;
                    }
                    else{
                       Sleep(2.5); printf("This red number is in Player 2's dominance.\n");
                       Sleep(2.5); printf("Player 2 earneth a tenth of his current gold.\n");
                        players2[1].gold += players2[1].gold * 0.1;
                    }
                }
                else{
                    if (roul.number <= players2[0].dominance){
                     Sleep(2.5);   printf("This black number is in Player 1's dominance.\n");
                     Sleep(2.5);   printf("Player 1 loseth to Player 2.\n"); //In more player games, it loses to the bank,
                        //Therefore, his money goes to bbet, a variable name for Bank Bet, and can be earnt
                        //By any other player, anytime.
                        players2[1].gold += players2[0].gold + ibet;
                        win = 2; players2[1].rwin+=1;
                    }
                    else{
                      Sleep(2.5);  printf("This black number is in Player 2's dominance.\n");
                     Sleep(2.5);   printf("Player 2 loseth to Player 1.\n");
                        players2[0].gold += players2[1].gold + ibet;
                        win = 1; players2[0].rwin+=1;
                    }
                }
            }
            
            //Turn 5: Final Summit Play check [if not won]
          Sleep(2.5);  printf("Let's now check your tiles to see if ye can split & perform an FSP...\n");
            if (win==0){
                for (i=0;i<2;i++){
                    players2[i].fsp=fspCheck(players2[i]);
                }

                if(players2[0].fsp==1 && players2[1].fsp==1){
               Sleep(2.5);     printf("'Tis an FSP draw! The dice shall decide who cometh first.\n");
                    fdice = dice();
                    if (fdice % 2 == 0){
                Sleep(2.5);        printf("Player 1 cometh first.\n");
                        //Call the JellyBean function for p1, thenifnot for p2
                        if (jellyBean(1)==1){win=1;players2[0].rwin+=1;fspwin=1;}
                        else{
                   Sleep(2.5);         printf("Ok, Player 2, it's showtime.\n");
                            if (jellyBean(2)==1){win=2;players2[1].rwin+=1;fspwin=1;}
                        }
                    }
                    else{
                   Sleep(2.5);     printf("Player 2 cometh first.\n");
                        //Call the JellyBean function for p2, thenifnot for p1
                        if (jellyBean(2)==1){win=2;players2[1].rwin+=1;fspwin=1;}
                        else{
                     Sleep(2.5);       printf("Ok, Player 1, it's showtime.\n");
                            if (jellyBean(1)==1){win=1;players2[0].rwin+=1;fspwin=1;}
                        }
                    }
                }
                else if (players2[0].fsp==1){
                    //Only player 1 has fsp
                 Sleep(2.5);   printf("Player 1 hath a Final Summit Play.\n");
                    //Call the JellyBean function for p1
                    if (jellyBean(1)==1){win=1;players2[0].rwin+=1;fspwin=1;}
                }
                else if (players2[1].fsp==1){
                    //Only player 2 has fsp
                Sleep(2.5);    printf("Player 2 hath a Final Summit Play.\n");
                    //Call the JellyBean function for p2
                    if (jellyBean(2)==1){win=2;players2[1].rwin+=1;fspwin=1;}
                }
                else{printf("Nobody hath an FSP.\n");}
            }


            //Turn 6: Deck comparison and bet retribution [if not won]
            if (win==0){
             Sleep(2.5);   printf("As nobody'th won the round yet, the deck wilt determine the winner.\n");
                switch (dwin)
                {
                case 1:
                Sleep(2.5);    printf("All bets go to Player 1\n");
                    players2[0].gold += ibet;
                Sleep(2.5);    printf("Player 1 hath %ld gold. Player 2 hath %ld gold.\n",players2[0].gold,players2[1].gold);
                    break;
                case 2:
                  Sleep(2.5);  printf("All bets go to Player 2\n");
                    players2[1].gold += ibet;
                  Sleep(2.5);  printf("Player 2 hath %ld gold. Player 1 hath %ld gold.\n",players2[1].gold,players2[0].gold);
                    break;
                default:
                   Sleep(2.5); printf("'Twas a draw. Bets remain on the table.\n");
                    break;
                }
            }
        }
        //After win.
        //Check winner, give shard
        if (win==1){
          Sleep(2.5);  printf("Player 1 geth a SHARD for winning!\n");
            players2[0].gold+=50;
            //Check rounds won, give 1 xor 2 diamonds
            //1 diamond = 3 or less rounds lost
            if(players2[1].rwin<=3){
             Sleep(2.5);   printf("Player 1 geth a CLEAR DIAMOND for losing less than 4 rounds!\n");
                players2[0].gold+=100;
            }
            //2 diamonds = no rounds lost
            if(players2[1].rwin==0){
              Sleep(2.5);  printf("Player 1 geth a COLORED DIAMOND for losing no rounds!\n");
                players2[0].gold+=400;
            }

            //Check turns, give 1 to 3 ankhs
            //1 ankh = 9 or less turns
            if(round <= 9){
             Sleep(2.5);   printf("Player 1 geth a RUBY ANKH for winning in less than 10 turns!\n");
                players2[0].gold+=200;
            }
            //2 ankhs = 6 or less turns
            if(round <= 6){
              Sleep(2.5);  printf("Player 1 geth a GOLDEN ANKH for winning in less than 7 turns!\n");
                players2[0].gold+=800;
            }
             //3 ankhs = 3 or less turns
              if(round <= 3){
              Sleep(2.5);  printf("Player 1 geth a PLATINUM ANKH for winning in less than 4 turns!\n");
                players2[0].gold+=1600;
            }
             //Rhodium Jewel -> victory through FSP
             if(fspwin == 1){
             Sleep(2.5);   printf("Player 1 geth a RHODIUM JEWEL for winning through an FSP!\n");
                players2[0].gold+=3200;
             }

             //Relic of Perfection -> colored diamond + platinum ankh + rodium jewel
             if(players2[1].rwin==0 && fspwin == 1 && round <=3){
              Sleep(2.5);   printf("Player 1 geth the RELIC OF PERFECTION!!!\n");
                 players2[0].gold*=2;
             }
          Sleep(2.5);  printf("Player 2 is out of the game!\n");
           Sleep(2.5); printf("Player 1's gold is %ld\n",players2[0].gold);
        }
        else{
          Sleep(2.5);  printf("Player 2 gets a SHARD for winning!\n");
            players2[1].gold+=50;
              //Check rounds won, give 1 xor 2 diamonds
            //1 diamond = 3 or less rounds lost
            if(players2[0].rwin<=3){
            Sleep(2.5);   printf("Player 2 geth a CLEAR DIAMOND for losing less than 4 rounds!\n");
                players2[1].gold+=100;
            }
            //2 diamonds = no rounds lost
            if(players2[0].rwin==0){
              Sleep(2.5);  printf("Player 2 geth a COLORED DIAMOND for losing no rounds!\n");
                players2[1].gold+=400;
            }

            //Check turns, give 1 to 3 ankhs
            //1 ankh = 9 or less turns
            if(round <= 9){
              Sleep(2.5);  printf("Player 2 geth a RUBY ANKH for winning in less than 10 turns!\n");
                players2[1].gold+=200;
            }
            //2 ankhs = 6 or less turns
            if(round <= 6){
             Sleep(2.5);   printf("Player 2 geth a GOLDEN ANKH for winning in less than 7 turns!\n");
                players2[1].gold+=800;
            }
             //3 ankhs = 3 or less turns
              if(round <= 3){
              Sleep(2.5);  printf("Player 2 geth a PLATINUM ANKH for winning in less than 4 turns!\n");
                players2[1].gold+=1600;
            }
             //Rhodium Jewel -> victory through FSP
             if(fspwin == 1){
             Sleep(2.5);   printf("Player 2 geth a RHODIUM JEWEL for winning through an FSP!\n");
                players2[1].gold+=3200;
             }

             //Relic of Perfection -> colored diamond + platinum ankh + rodium jewel
             if(players2[1].rwin==0 && fspwin == 1 && round <=3){
              Sleep(2.5);   printf("Player 2 geth the RELIC OF PERFECTION!!!\n");
                 players2[1].gold*=2;
             }
           Sleep(2.5); printf("Player 1 is out of the game!\n");
           Sleep(2.5); printf("Player 2's gold is %ld\n",players2[1].gold);
        }

        break;
    
    default:
        break;
    }
    printf("Thx for playin'!");
 
    return 0;
}
