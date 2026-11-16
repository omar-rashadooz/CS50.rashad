#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

#define WIDTH 32
#define HEIGHT 22

int snake_x[200], snake_y[200];
int length = 4;
int dir = 1;
int food_x, food_y;
int score = 0, highScore = 0;
int gameOver = 0;

void loadHighScore(){
    FILE *f=fopen(".snake_high","r");
    if(f){ fscanf(f,"%d",&highScore); fclose(f); }
}
void saveHighScore(){
    if(score>highScore){
        FILE *f=fopen(".snake_high","w");
        if(f){ fprintf(f,"%d",score); fclose(f); }
        highScore=score;
    }
}

void placeFood(){
    int ok=0;
    while(!ok){
        food_x = rand() % (WIDTH-2) + 1;
        food_y = rand() % (HEIGHT-2) + 1;
        ok=1;
        for(int i=0;i<length;i++) if(snake_x[i]==food_x && snake_y[i]==food_y) ok=0;
    }
}
void setup(){
    srand(time(0));
    loadHighScore();
    for(int i=0;i<length;i++){ snake_x[i]=WIDTH/2 - i; snake_y[i]=HEIGHT/2; }
    placeFood();
}
void draw(){
    clear();
    // الوان
    attron(COLOR_PAIR(1));
    for(int i=0;i<WIDTH;i++){ mvprintw(0,i,"█"); mvprintw(HEIGHT-1,i,"█"); }
    for(int i=0;i<HEIGHT;i++){ mvprintw(i,0,"█"); mvprintw(i,WIDTH-1,"█"); }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(food_y, food_x, "●");
    attroff(COLOR_PAIR(2) | A_BOLD);

    for(int i=0;i<length;i++){
        if(i==0){ attron(COLOR_PAIR(3) | A_BOLD); mvprintw(snake_y[i], snake_x[i], "◉"); attroff(COLOR_PAIR(3) | A_BOLD); }
        else { attron(COLOR_PAIR(4)); mvprintw(snake_y[i], snake_x[i], "○"); attroff(COLOR_PAIR(4)); }
    }
    attron(COLOR_PAIR(5));
    mvprintw(HEIGHT, 0, " Score: %d | High: %d | Speed: %d | q=quit ", score, highScore, score/50+1);
    mvprintw(HEIGHT+1, 0, " Controls: WASD / Arrows ");
    attroff(COLOR_PAIR(5));
    refresh();
}
void input(){
    int ch=getch();
    if(ch=='w'||ch==KEY_UP) if(dir!=2) dir=0;
    if(ch=='d'||ch==KEY_RIGHT) if(dir!=3) dir=1;
    if(ch=='s'||ch==KEY_DOWN) if(dir!=0) dir=2;
    if(ch=='a'||ch==KEY_LEFT) if(dir!=1) dir=3;
    if(ch=='q') gameOver=1;
}
void logic(){
    int prev_x=snake_x[0], prev_y=snake_y[0], prev2_x, prev2_y;
    if(dir==0) snake_y[0]--;
    if(dir==1) snake_x[0]++;
    if(dir==2) snake_y[0]++;
    if(dir==3) snake_x[0]--;

    if(snake_x[0]<=0||snake_x[0]>=WIDTH-1||snake_y[0]<=0||snake_y[0]>=HEIGHT-1) gameOver=1;
    for(int i=1;i<length;i++) if(snake_x[0]==snake_x[i] && snake_y[0]==snake_y[i]) gameOver=1;

    for(int i=1;i<length;i++){ prev2_x=snake_x[i]; prev2_y=snake_y[i]; snake_x[i]=prev_x; snake_y[i]=prev_y; prev_x=prev2_x; prev_y=prev2_y; }

    if(snake_x[0]==food_x && snake_y[0]==food_y){ length++; score+=10; placeFood(); }
}

int main(){
    initscr(); noecho(); curs_set(0); keypad(stdscr, TRUE); nodelay(stdscr, TRUE); timeout(100);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK); // border
    init_pair(2, COLOR_RED, COLOR_BLACK); // food
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // head
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // body
    init_pair(5, COLOR_WHITE, COLOR_BLUE); // info

    setup();
    while(!gameOver){
        draw(); input(); logic();
        int delay = 130000 - (score*800);
        if(delay<30000) delay=30000;
        usleep(delay);
    }
    endwin();
    saveHighScore();
    printf("\n🐍 GAME OVER 🐍\nScore: %d\nHigh Score: %d\n", score, highScore);
    if(score==highScore && score>0) printf("🔥 NEW HIGH SCORE! جامد!\n");
    return 0;
}