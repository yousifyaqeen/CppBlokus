#ifndef TileMap_H
#define TileMap_H

class TileMap  sf::Drawable, public sf::Transformable {
private:

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height,int offSetX,int offSetY);



};

#endif
