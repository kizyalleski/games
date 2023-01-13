// Copyright 2022 lakitamj roslinta rhaenysl
#include <stdio.h>
#include "movement_control.c"

const int width = 80;
const int heigth = 25;
const int plr_offset_x = 2;

int display(int x, int y, int plr1, int plr2, int count_plr_1, int count_plr_2);
int mov_control();
int plr_move(int pos_plr, int direct);
int isgoal(const int x, const int d_x);
int isblowrefl(const int x, const int y, const int d_x,
               const int d_y, const int pos_plr_1, const int pos_plr_2);
int isbound(const int y, const int d_y);

int main() {
    int pos_plr_1, pos_plr_2;
    int ball_x = width / 2;
    int ball_y = pos_plr_1 = pos_plr_2 = heigth / 2;
    int count_plr_1 = 0;
    int count_plr_2 = 0;
    int d_x = 1;
    int d_y = 1;
    do {
        switch (mov_control()) {
            case 1:
                pos_plr_1 = plr_move(pos_plr_1, -1);
                if (isgoal(ball_x, d_x)) {
                    ball_x = width / 2;
                    ball_y = heigth / 2;
                    d_x > 0 ? count_plr_1++ : count_plr_2++;
                } else {
                    if (isbound(ball_y, d_y)) d_y *= -1;
                    if (isblowrefl(ball_x, ball_y, d_x, d_y, pos_plr_1, pos_plr_2)) d_x *= -1;
                    ball_x += d_x;
                    ball_y += d_y;
                }
                break;
            case 2:
                pos_plr_1 = plr_move(pos_plr_1, 1);
                if (isgoal(ball_x, d_x)) {
                    ball_x = width / 2;
                    ball_y = heigth / 2;
                    d_x > 0 ? count_plr_1++ : count_plr_2++;
                } else {
                    if (isbound(ball_y, d_y)) d_y *= -1;
                    if (isblowrefl(ball_x, ball_y, d_x, d_y, pos_plr_1, pos_plr_2)) d_x *= -1;
                    ball_x += d_x;
                    ball_y += d_y;
                }
                break;
            case 3:
                pos_plr_2 = plr_move(pos_plr_2, -1);
                if (isgoal(ball_x, d_x)) {
                    ball_x = width / 2;
                    ball_y = heigth / 2;
                    d_x > 0 ? count_plr_1++ : count_plr_2++;
                } else {
                    if (isbound(ball_y, d_y)) d_y *= -1;
                    if (isblowrefl(ball_x, ball_y, d_x, d_y, pos_plr_1, pos_plr_2)) d_x *= -1;
                    ball_x += d_x;
                    ball_y += d_y;
                }
                break;
            case 4:
                pos_plr_2 = plr_move(pos_plr_2, 1);
                if (isgoal(ball_x, d_x)) {
                    ball_x = width / 2;
                    ball_y = heigth / 2;
                    d_x > 0 ? count_plr_1++ : count_plr_2++;
                } else {
                    if (isbound(ball_y, d_y)) d_y *= -1;
                    if (isblowrefl(ball_x, ball_y, d_x, d_y, pos_plr_1, pos_plr_2)) d_x *= -1;
                    ball_x += d_x;
                    ball_y += d_y;
                }
                break;
            case 5:
                if (isgoal(ball_x, d_x)) {
                    ball_x = width / 2;
                    ball_y = heigth / 2;
                    d_x > 0 ? count_plr_1++ : count_plr_2++;
                } else {
                    if (isbound(ball_y, d_y)) d_y *= -1;
                    if (isblowrefl(ball_x, ball_y, d_x, d_y, pos_plr_1, pos_plr_2)) d_x *= -1;
                    ball_x += d_x;
                    ball_y += d_y;
                }
                break;
            case 10:
                continue;
            case 100:
                return 0;
        }
        display(ball_x, ball_y, pos_plr_1, pos_plr_2, count_plr_1, count_plr_2);
        if (count_plr_1 == 21 || count_plr_2 == 21) break;
    } while (1);

    printf("Win player %d\n", count_plr_1 > count_plr_2 ? 1 : 2);
    return 0;
}

int plr_move(int pos_plr, int direct) {
    pos_plr += direct;
    if (pos_plr < 1) pos_plr = 1;
    if (pos_plr > 21) pos_plr = 21;
    return pos_plr;
}

int isgoal(const int x, const int d_x) {
    int x_ball = d_x + x;
    return x_ball == 0 || x_ball == width - 1 ?  1 : 0;
}

int isblowrefl(const int x, const int y, const int d_x,
               const int d_y, const int pos_plr_1, const int pos_plr_2) {
    int x_ball = x + d_x;
    int y_ball = y + d_y;
    if ((x_ball == plr_offset_x && y_ball >= pos_plr_1 && y_ball < pos_plr_1 + 3) ||
        (x_ball == width - 1 - plr_offset_x && y_ball >= pos_plr_2 && y_ball < pos_plr_2 + 3)) {
        return 1;
    }
    return 0;
}

int isbound(const int y, const int d_y) {
    int y_ball = y + d_y;
    return y_ball == 0 || y_ball == heigth - 1 ? 1 : 0;
}

int display(int x, int y, int plr1, int plr2, int count_plr_1, int count_plr_2) {
        printf("\033[0d\033[2J");
        int i = 0, j = 0;
        while (i < heigth) {
                while (j < width) {
                        if (i == 0) {
                                if (j == 0) {
                                        printf("╔");
                                } else if (j == width - 1) {
                                        printf("╗");
                                } else {
                                        printf("═");
                                }
                        } else if (i == heigth - 1) {
                                if (j == 0) {
                                        printf("╚");
                                } else if (j == width - 1) {
                                        printf("╝");
                                } else {
                                        printf("═");
                                }
                        } else if (i == y && j == x) {
                                printf("®");
                        } else if (j == width / 2) {
                            printf("|");
                        } else if (j == plr_offset_x && (i >= plr1  && i <= plr1 + 2 )) {
                                printf("▓");
                        } else if (j == width - plr_offset_x - 1 && (i >= plr2 && i <= plr2 + 2)) {
                                printf("▓");
                        } else {
                            printf(" ");
                        }
                      j++;
                }
                printf("\n");
                i++;
                j = 0;
        }
    printf("                                      %d : %d\n", count_plr_1, count_plr_2);
    return 0;
}
