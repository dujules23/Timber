// include important libraries here
#include <SFML/Graphics.hpp>
#include <iostream>

// make code easier to type with "using namespace" using namespace sf;

using namespace sf;

// this is where our game starts from int main()

int main()
{
  
  // create a video mode object (SFML 3 uses a Vector2u constructor)
  VideoMode vm({1680, 1050});

  // create and open a window for the game
  // use windowed mode for now (debugging)
  RenderWindow window(vm, "Timber!!!");


  // Create a texture to hold a graphic on the GPU Texture
  Texture textureBackground;

  if (!textureBackground.loadFromFile("graphics/background.png"))
{
    // handle the error: abort, use a fallback, etc.
    return EXIT_FAILURE;
}

  // Create a sprite, Attach the texture to the sprite

  Sprite spriteBackground(textureBackground);

  // Set the spriteBackground to cover the screen
  spriteBackground.setPosition({0, 0});

  // Make a tree sprite

  Texture textureTree;
  if (!textureTree.loadFromFile("graphics/tree.png"))
{
    // handle the error: abort, use a fallback, etc.
    return EXIT_FAILURE;
}
  Sprite spriteTree(textureTree);
  spriteTree.setPosition({810, 0});

  while (window.isOpen())
  {
    /* Handle the player's input*/
    // poll event needed for MacOS, otherwise the window will freeze when you click the close button
    while (const auto event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        window.close();
      }
      else if (event->is<sf::Event::KeyPressed>())
      {
        const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
        if (keyEvent && keyEvent->code == Keyboard::Key::Escape)
        {
          window.close();
        }
      }
    }

    /* Update the scene*/

    // Clear everything from the last frame
    window.clear();

    // Draw our game scene here
    window.draw(spriteBackground);

    // show everything we just drew
    window.display();
  }

  

    return 0;
}