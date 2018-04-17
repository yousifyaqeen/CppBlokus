class TileMap : public sf::Drawable, public sf::Transformable
{

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
private:

  void draw(sf::RenderTarget& target, sf::RenderStates states);

public:
bool load(const std::string& tileset, sf::Vector2u tileSize,  int* tiles, unsigned int width, unsigned int height,int offSetX,int offSetY);

};
