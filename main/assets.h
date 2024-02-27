class Assets
{
public:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
    std::map<std::string, sf::SoundBuffer> m_sounds;

    void addTexture(std::string path)
    {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/sprites/" + path))
        {
            std::cout << path << "not found";
        }
        m_textures[path] = texture;
    }

    void addFont(std::string path)
    {

        sf::Font font;
        if (!font.loadFromFile("assets/" + path))
        {
            std::cout << path << "not found";
        }
        m_fonts[path] = font;
    }
    void addSound(std::string path)
    {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("assets/audio/" + path))
        {
            std::cout << path << "not found";
        }

        m_sounds[path] = buffer;
    }
};