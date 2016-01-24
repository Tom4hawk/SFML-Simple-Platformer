#include "ladowaniezawartosci.h"

LadowanieZawartosci::LadowanieZawartosci(const char *filename)
{
	loadType = -1;
    sf::Image image;
    std::ifstream openfile(filename);
    std::vector <int> tempVector;
 
    std::string line;
 
    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
            std::getline(openfile, line);
 
            if(line.find("Map") != std::string::npos)
            {
                loadType = MAP;
                continue;
            }
            else if (line.find("Texture") != std::string::npos)
            {
                loadType = TEXTURE;
                continue;
            }
 
            std::string tempLine = line.erase(line.find_last_not_of(" ") + 1);
            int space = tempLine.find_first_of(" ");
            if(space == 0)
                tempLine = tempLine.erase(0, space + 1);
            std::stringstream str(tempLine);
 
            switch(loadType)
            {
                case MAP:
                    while(!str.eof())
                    {
                        std::string value;
                        getline(str, value, ' ');
                        if(value.length() > 0)
                            tempVector.push_back(atoi(value.c_str()));
                    }
                    MapVector.push_back(tempVector);
                    tempVector.clear();
                    break;
 
                case TEXTURE:
                    if(tempLine.length() > 0)
                    {
                        if(image.LoadFromFile(tempLine))
                        {
                            textureVector.push_back(image);
                        }
                        else
                        {
                            std::cout << "Nie można zaladować" << line << std::endl;
                        }
                        break;
                    }
            }
        }
    }
}
 
void LadowanieZawartosci::DrawMap(sf::RenderWindow &Window)
{
    sf::Shape rect = sf::Shape::Rectangle(0, 0, BLOCKSIZE, BLOCKSIZE, sf::Color(255, 255, 255, 255));
    sf::Color rectCol;
    sf::Sprite sprite;
    for(int i = 0; i < (int)MapVector.size(); ++i)
    {
        for(int j = 0; j < (int)MapVector[i].size(); ++j)
        {
            if(MapVector[i][j] < 0)
            {
                rectCol = sf::Color(50, 50, 255);
                rect.SetPosition(j * BLOCKSIZE, i * BLOCKSIZE);
                rect.SetColor(rectCol);
                Window.Draw(rect);
            }
            else
            {
                sprite.SetImage(textureVector[MapVector[i][j]]);
                sprite.SetPosition(j * BLOCKSIZE, i * BLOCKSIZE);
                Window.Draw(sprite);
            }
        }
    }
}

