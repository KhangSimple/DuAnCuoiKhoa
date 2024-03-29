#include "Gallery.h"

Gallery::Gallery(Painter& painter_)
    : painter(painter_)
{
    loadGamePictures();
}

Gallery::~Gallery()
{
    for (SDL_Texture* texture : pictures)
        SDL_DestroyTexture(texture);
}

void Gallery::loadGamePictures()
{
    pictures.push_back(painter.loadTexture("img/apple.png"));
    pictures.push_back(painter.loadTexture("img/snake_test.png"));
    pictures.push_back(painter.loadTexture("img/snake_test.png"));
    pictures.push_back(painter.loadTexture("img/snake_head1.png"));
}
