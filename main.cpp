// Created by Yun Yeomin <min050820@gmail.com>
// Licensed under GPLv3

#include <cstdio>
#include <SDL.h>

int main(int argc, char *argv[]) {
    printf("Hello, SDL2!\n");

    SDL_version ver;
    SDL_GetVersion(&ver);
    printf("Version: %d.%d.%d\n", ver.major, ver.minor, ver.patch);
    return 0;
}